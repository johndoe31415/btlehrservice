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
#include "containment.h"
#include "uuids.h"

static GMainLoop *m_main_loop;

static void notification_handler(const uuid_t* uuid, const uint8_t* data, size_t data_length, void* user_data) {
	int *msg_fd = (int*)user_data;
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

static void disconnect_handler(void *ctx) {
	g_main_loop_quit(m_main_loop);
}

static void on_user_abort(int arg) {
	g_main_loop_quit(m_main_loop);
}

static void btle_connect(const struct connection_params_t *connection_params, int comm_fd) {
	const uuid_t heartrate_uuid = CREATE_UUID16(BT_CHARID_HeartRateMeasurement);
	gatt_connection_t* connection;

	while (true) {
		struct message_t msg = {
			.msgtype = ATTEMPT_CONNECTION,
		};
		if (write(comm_fd, &msg, sizeof(msg)) != sizeof(msg)) {
			exit(EXIT_FAILURE);
		}
		if (!connection_params->random_btle_address) {
			connection = gattlib_connect(NULL, connection_params->destination_address, GATTLIB_CONNECTION_OPTIONS_LEGACY_DEFAULT);
		} else {
			connection = gattlib_connect(NULL, connection_params->destination_address, GATTLIB_CONNECTION_OPTIONS_LEGACY_BDADDR_LE_RANDOM | GATTLIB_CONNECTION_OPTIONS_LEGACY_BT_SEC_LOW);
		}
		if (connection == NULL) {
			sleep(connection_params->connect_failed_retry_secs ? connection_params->connect_failed_retry_secs : 1);
		} else {
			break;
		}
	}

	gattlib_register_notification(connection, notification_handler, &comm_fd);
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

	gattlib_notification_stop(connection, &heartrate_uuid);
	gattlib_disconnect(connection);

	// In case we quit the main loop, clean the connection
	g_main_loop_unref(m_main_loop);

	close(comm_fd);
	exit(EXIT_SUCCESS);
}

static void sigchld_handler(int signal) {
	int status;
	while (waitpid(-1, &status, WNOHANG) > 0);
}

static bool install_sigchld_handler(void) {
	struct sigaction action = {
		.sa_handler = sigchld_handler,
		.sa_flags = SA_RESTART,
	};
	if (sigaction(SIGCHLD, &action, NULL)) {
		perror("sigaction");
		return false;
	}

	return true;
}

bool contained_connect(const struct connection_params_t *connection_params, containment_callback_fnc_t callback, void *callback_ctx) {
	int pipefd[2];
	if (pipe(pipefd) == -1) {
		perror("pipe");
		return false;
	}

	int pipe_read_fd = pipefd[0];
	int pipe_write_fd = pipefd[1];

	/* Install SIGCHLD handler */
	if (!install_sigchld_handler()) {
		close(pipe_read_fd);
		close(pipe_write_fd);
		return false;
	}

	pid_t pid = fork();
	if (pid == -1) {
		perror("fork");
		return false;
	}

	if (pid > 0) {
		/* Parent process */
		close(pipe_write_fd);
		while (true) {
			fd_set read_set;
			FD_ZERO(&read_set);
			FD_SET(pipe_read_fd, &read_set);
			struct timeval timeout = {
				.tv_sec = connection_params->child_process_timeout_secs ? connection_params->child_process_timeout_secs : 20,
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
			callback(&msg, callback_ctx);
		}
		close(pipe_read_fd);
		kill(pid, SIGHUP);
	} else {
		/* Child process */
		close(pipe_read_fd);

		/* Make the containment silent (lots of DBus messages spamming the
		 * console otherwise) */
		if (connection_params->verbose < 2) {
			close(STDOUT_FILENO);
			close(STDERR_FILENO);
		}

		btle_connect(connection_params, pipe_write_fd);
		exit(EXIT_SUCCESS);
	}

	return true;
}
