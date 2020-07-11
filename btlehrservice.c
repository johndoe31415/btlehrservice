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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <linux/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <pwd.h>
#include <pthread.h>
#include "containment.h"
#include "pgmopts.h"
#include "llist.h"

struct connected_client_t {
	int client_sd;
	FILE *f;
	struct server_ctx_t *server_ctx;
	struct llist_element_t *client_list_element;
};

struct heartrate_state_t {
	bool connected;
	bool have_value;
	double timestamp;
	uint8_t last_heartrate;
};

struct server_ctx_t {
	pthread_t btle_thread;
	struct connection_params_t connection;
	bool running;
	struct llist_t clients;
	struct heartrate_state_t hrm;
};

static void send_message_to_client(struct llist_element_t *element, void *ctx) {
	struct connected_client_t *client = (struct connected_client_t*)element->payload;
	char *message = (char*)ctx;
	fprintf(client->f, "%s\n", message);
	fflush(client->f);
}

static double now(void) {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec + (1e-6 * tv.tv_usec);
}

static void containment_callback(const struct message_t *msg, void *vctx) {
	struct server_ctx_t *server_ctx = (struct server_ctx_t*)vctx;
	if (msg->msgtype == ATTEMPT_CONNECTION) {
		server_ctx->hrm.connected = false;
		server_ctx->hrm.have_value = false;
		server_ctx->hrm.timestamp = 0;
		server_ctx->hrm.last_heartrate = 0;
	} else if ((msg->msgtype == NOTIFICATION) && (msg->data_length == 2)) {
		server_ctx->hrm.connected = true;
		server_ctx->hrm.have_value = (msg->data[1] != 0);
		if (server_ctx->hrm.have_value) {
			server_ctx->hrm.timestamp = now();
			server_ctx->hrm.last_heartrate = msg->data[1];
		}
	}

	char client_message[128];
	if (!server_ctx->hrm.connected) {
		snprintf(client_message, sizeof(client_message), "{ \"connected\": false }");
	} else {
		snprintf(client_message, sizeof(client_message), "{ \"connected\": true, \"have_value\": %s, \"ts\": %f, \"last_value\": %u }", server_ctx->hrm.have_value ? "true" : "false", server_ctx->hrm.timestamp, server_ctx->hrm.last_heartrate);
	}
	llist_traverse(&server_ctx->clients, send_message_to_client, client_message);
}

static void* client_thread_fnc(void *vctx) {
	struct connected_client_t *ctx = (struct connected_client_t*)vctx;
	while (ctx->server_ctx->running) {
		uint8_t buffer[128];
		ssize_t read_bytes = read(ctx->client_sd, buffer, sizeof(buffer));
		if (read_bytes == 0) {
			/* Client disconnected */
			break;
		}
	}
	fclose(ctx->f);
	llist_remove_element(ctx->client_list_element);
	return NULL;
}

static void* btle_thread_fnc(void *vctx) {
	struct server_ctx_t *server_ctx = (struct server_ctx_t*)vctx;
	while (server_ctx->running) {
		contained_connect(&server_ctx->connection, containment_callback, server_ctx);
	}
	return NULL;
}

static bool change_socket_user(const char *filename, const char *username) {
	if (username == NULL) {
		return true;
	}

	struct passwd *user = getpwnam(username);
	if (!user) {
		perror("getpwnam");
		return false;
	}

	if (chown(filename, user->pw_uid, user->pw_gid)) {
		perror("chown");
		return false;
	}
	return true;
}

static bool change_socket_permissions(const char *filename, int permissions) {
	if (permissions == -1) {
		return true;
	}

	if (chmod(filename, permissions)) {
		perror("chmod");
		return false;
	}

	return true;
}

static bool server_listening_loop(struct server_ctx_t *server_ctx) {
	int sd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sd == -1) {
		perror("socket");
		return false;
	}

	unlink(pgmopts->socket);
	struct sockaddr_un sockaddr = {
		.sun_family = AF_UNIX,
	};
	strncpy(sockaddr.sun_path, pgmopts->socket, sizeof(sockaddr.sun_path) - 1);
	if (bind(sd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) == -1) {
		perror("bind");
		close(sd);
		return false;
	}

	if (listen(sd, 5) == -1) {
		perror("listen");
		close(sd);
		return false;
	}

	if (!change_socket_user(pgmopts->socket, pgmopts->socket_username)) {
		fprintf(stderr, "Chaning user of socket %s to user %s failed.", pgmopts->socket, pgmopts->socket_username);
		return false;
	}
	if (!change_socket_permissions(pgmopts->socket, pgmopts->socket_permissions)) {
		fprintf(stderr, "Chaning permissions of socket %s to 0o%o failed.", pgmopts->socket, pgmopts->socket_permissions);
		return false;
	}

	while (server_ctx->running) {
		struct sockaddr_un peer = { 0 };
		socklen_t socklen = sizeof(peer);
		int client_sd = accept(sd, (struct sockaddr*)&peer, &socklen);
		if (client_sd == -1) {
			perror("accept");
			close(sd);
			return false;
		}

		/* We now have a new client that's connected */
		struct connected_client_t *client = calloc(sizeof(*client), 1);
		if (!client) {
			perror("calloc");
			close(client_sd);
			close(sd);
			return false;
		}

		client->client_sd = client_sd;
		client->server_ctx = server_ctx;
		client->f = fdopen(client->client_sd, "w");
		client->client_list_element = llist_append(&server_ctx->clients, client, true);

		pthread_t client_thread;
		pthread_attr_t attrs;
		pthread_attr_init(&attrs);
		pthread_attr_setdetachstate(&attrs, PTHREAD_CREATE_DETACHED);
		if (pthread_create(&client_thread, &attrs, client_thread_fnc, client)) {
			perror("pthread_create");
			pthread_attr_destroy(&attrs);
			close(client_sd);
			close(sd);
			return false;
		}
		pthread_attr_destroy(&attrs);
	}


	return true;
}

int main(int argc, char **argv) {
	parse_cmdline_options(argc, argv);

	struct server_ctx_t server_ctx = {
		.running = true,
		.connection = {
			.random_btle_address = pgmopts->random_btle_address,
			.destination_address = pgmopts->dest_mac_address,
		},
		.clients = LINKEDLIST_INITIALIZER,
	};

	if (pthread_create(&server_ctx.btle_thread, NULL, btle_thread_fnc, &server_ctx)) {
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}

	server_listening_loop(&server_ctx);

	return 0;
}
