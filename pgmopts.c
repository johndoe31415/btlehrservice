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
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "pgmopts.h"
#include "argparse.h"

static struct pgmopts_t pgmopts_rw = {
	.socket_permissions = -1,
};
const struct pgmopts_t *pgmopts = &pgmopts_rw;

static bool argument_callback(enum argparse_option_t option, const char *value, argparse_errmsg_callback_t errmsg_callback) {
	switch (option) {
		case ARG_USER:
			pgmopts_rw.socket_username = value;
			break;

		case ARG_CHOWN:
			pgmopts_rw.socket_permissions = strtol(value, NULL, 8);
			break;

		case ARG_RANDOM_BTLE_ADDRESS:
			pgmopts_rw.random_btle_address = true;
			break;

		case ARG_DESTINATION_ADDRESS:
			strncpy(pgmopts_rw.dest_mac_address, value, sizeof(pgmopts_rw.dest_mac_address) - 1);
			break;

		case ARG_UNIX_SOCKET:
			pgmopts_rw.socket = value;
			break;
	}
	return true;
}

static bool is_valid_mac(const char *mac_address) {
	if (strlen(pgmopts_rw.dest_mac_address) != 17) {
		return false;
	}
	for (unsigned int i = 0; i < 17; i++) {
		char c = mac_address[i];
		if ((i % 3) == 2) {
			/* Expect colon */
			if (c != ':') {
				return false;
			}
		} else {
			/* Expect hex digit */
			if (!(((c >= '0') && (c <= '9'))
					|| ((c >= 'a') && (c <= 'f'))
					|| ((c >= 'A') && (c <= 'F')))) {
				return false;
			}
		}
	}
	return true;
}

static void str_upper(char *str) {
	int len = strlen(str);
	for (unsigned int i = 0; i < len; i++) {
		char c = str[i];
		if ((c >= 'a') && (c <= 'z')) {
			str[i] = c - 'a' + 'A';
		}
	}
}

static bool plausibilization_callback(argparse_errmsg_option_callback_t errmsg_callback) {
	if (!is_valid_mac(pgmopts_rw.dest_mac_address)) {
		errmsg_callback(ARG_DESTINATION_ADDRESS, "not a valid MAC address: %s", pgmopts_rw.socket);
		return false;
	} else {
		/* gattlib is very particular about the case of the MAC address; it
		 * needs to be uppercase or it won't connect (see
		 * https://github.com/labapart/gattlib/issues/49) */
		str_upper(pgmopts_rw.dest_mac_address);
	}
	return true;
}

void parse_cmdline_options(int argc, char **argv) {
	argparse_parse_or_quit(argc, argv, argument_callback, plausibilization_callback);
}
