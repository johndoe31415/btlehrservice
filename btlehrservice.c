/*
 *	btlehrservice - Bluetooth-Low-Energy heart rate service
 *	Copyright (C) 2019-2019 Johannes Bauer
 *
 *	This file is part of btlehrservice.
 *
 *	btlehrservice is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; this program is ONLY licensed under
 *	version 3 of the License, later versions are explicitly excluded.
 *
 *	btlehrservice is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with btlehrservice; if not, write to the Free Software
 *	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	Johannes Bauer <JohannesBauer@gmx.de>
 */

#include <assert.h>
#include <glib.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "gattlib.h"

enum messagetype_t {
	TRY_CONNECT,
	NOTIFICATION,
};

struct message_t {
	enum messagetype_t msgtype;
	unsigned int data_length;
	uint8_t data[8];
};

const uuid_t heartrate_uuid = CREATE_UUID16(0x2A37);

static GMainLoop *m_main_loop;

static void notification_handler(const uuid_t* uuid, const uint8_t* data, size_t data_length, void* user_data) {
	int *msg_fd = (int*)user_data;
	printf("Notification Handler %p: ", user_data);
	for (int i = 0; i < data_length; i++) {
		printf("%02x ", data[i]);
	}
	printf("\n");
	struct message_t msg = {
		.msgtype = NOTIFICATION,
		.data_length = data_length,
	};
	if (msg.data_length > sizeof(msg.data)) {
		msg.data_length = sizeof(msg.data);
	}
	memcpy(msg.data, data, msg.data_length);
	if (write(*msg_fd, &msg, sizeof(msg)) != sizeof(msg)) {
		exit(EXIT_FAILURE);
	}
}

static void disconnect_handler(void *x) {
	g_main_loop_quit(m_main_loop);
}

static void on_user_abort(int arg) {
	g_main_loop_quit(m_main_loop);
}


void btle_connect(const char *address, int result_fd) {
	gatt_connection_t* connection;

	while (true) {
		struct message_t msg = {
			.msgtype = TRY_CONNECT,
		};
		if (write(result_fd, &msg, sizeof(msg)) != sizeof(msg)) {
			exit(EXIT_FAILURE);
		}
		connection = gattlib_connect(NULL, address, GATTLIB_CONNECTION_OPTIONS_LEGACY_DEFAULT);
		if (connection == NULL) {
			sleep(1);
		} else {
			break;
		}
	}

	fprintf(stderr, "Connected: %p\n", connection);

	gattlib_register_notification(connection, notification_handler, &result_fd);
	gattlib_register_on_disconnect(connection, disconnect_handler, connection);

	int ret = gattlib_notification_start(connection, &heartrate_uuid);
	if (ret) {
		fprintf(stderr, "Failed to start notification.\n");
		exit(EXIT_FAILURE);
	}

	// Catch CTRL-C
	signal(SIGINT, on_user_abort);

	m_main_loop = g_main_loop_new(NULL, 0);
	g_main_loop_run(m_main_loop);


//		gattlib_register_on_disconnect(connection, NULL, NULL);
//		gattlib_register_notification(connection, NULL, NULL);
	gattlib_notification_stop(connection, &heartrate_uuid);
	gattlib_disconnect(connection);

	// In case we quit the main loop, clean the connection
	g_main_loop_unref(m_main_loop);

	close(result_fd);
	exit(EXIT_SUCCESS);
}

int main(void) {
	while (true) {
		int pipefd[2];
		if (pipe(pipefd) == -1) {
			perror("pipe");
			exit(EXIT_FAILURE);
		}

		int pipe_read_fd = pipefd[0];
		int pipe_write_fd = pipefd[1];

		fprintf(stderr, "fork()\n");
		pid_t pid = fork();
		if (pid == -1) {
			perror("fork");
			exit(EXIT_FAILURE);
		}

		if (pid > 0) {
			/* Parent process */
			close(pipe_write_fd);
			while (true) {
				fd_set read_set;
				FD_ZERO(&read_set);
				FD_SET(pipe_read_fd, &read_set);
				struct timeval timeout = {
					.tv_sec = 20,
				};
				int sresult = select(pipe_read_fd + 1, &read_set, NULL, NULL, &timeout);
				if (sresult == 0) {
					/* Select timed out. Not received a message within the
					 * timeout. Sever the connection to client. */
					fprintf(stderr, "Client timeout.\n");
					break;
				}
				struct message_t msg;
				if (read(pipe_read_fd, &msg, sizeof(msg)) != sizeof(msg)) {
					fprintf(stderr, "Client short read.\n");
					break;
				}
				fprintf(stderr, "MSG: %d\n", msg.msgtype);
			}
			close(pipe_read_fd);
			kill(pid, SIGHUP);
		} else {
			/* Child process */
			close(pipe_read_fd);
			btle_connect("20:C3:8F:FF:0A:7E", pipe_write_fd);
			exit(EXIT_SUCCESS);
		}

		/* Clean up child process */
		int status;
		sleep(1);
		kill(pid, SIGKILL);
		waitpid(pid, &status, 0);
	}
	return 0;
}
