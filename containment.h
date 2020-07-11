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

#include <stdint.h>
#include <stdbool.h>

enum messagetype_t {
	ATTEMPT_CONNECTION = 1,
	NOTIFICATION,
};

struct message_t {
	enum messagetype_t msgtype;
	unsigned int data_length;
	uint8_t data[8];
};

struct connection_params_t {
	int verbose;
	bool random_btle_address;
	const char *destination_address;
	unsigned int connect_failed_retry_secs;
	unsigned int child_process_timeout_secs;
};

typedef void (*containment_callback_fnc_t)(const struct message_t *msg, void *ctx);

#ifndef __CONTAINMENT_H__
#define __CONTAINMENT_H__

/*************** AUTO GENERATED SECTION FOLLOWS ***************/
bool contained_connect(const struct connection_params_t *connection, containment_callback_fnc_t callback, void *callback_ctx);
/***************  AUTO GENERATED SECTION ENDS   ***************/

#endif
