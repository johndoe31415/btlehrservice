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
#include <pthread.h>
#include "containment.h"
#include "pgmopts.h"

struct server_ctx_t {
	pthread_t btle_thread;
	struct connection_params_t connection;
	bool running;
};

static void containment_callback(const struct message_t *msg, void *vctx) {
	struct server_ctx_t *server_ctx = (struct server_ctx_t*)vctx;
	fprintf(stderr, "containment callback: %d\n", msg->msgtype);
}

static void* btle_thread_fnc(void *vctx) {
	struct server_ctx_t *server_ctx = (struct server_ctx_t*)vctx;
	while (server_ctx->running) {
		contained_connect(&server_ctx->connection, containment_callback, server_ctx);
	}
	return NULL;
}

int main(int argc, char **argv) {
	parse_cmdline_options(argc, argv);

	struct server_ctx_t server_ctx = {
		.running = true,
		.connection = {
			.destination_address = pgmopts->dest_mac_address,
		},
	};

	if (pthread_create(&server_ctx.btle_thread, NULL, btle_thread_fnc, &server_ctx)) {
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}

	while (true) {
		sleep(1);
	}

	return 0;
}
