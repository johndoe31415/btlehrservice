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

#include "pgmopts.h"
#include "argparse.h"

static struct pgmopts_t pgmopts_rw = {
	0
};
const struct pgmopts_t *pgmopts = &pgmopts_rw;

static bool argument_callback(enum argparse_option_t option, const char *value, argparse_errmsg_callback_t errmsg_callback) {
	switch (option) {
		case ARG_DESTINATION_ADDRESS:
			pgmopts_rw.dest_mac_address = value;
			break;

		case ARG_UNIX_SOCKET:
			pgmopts_rw.socket = value;
			break;
	}
	return true;
}

static bool plausibilization_callback(argparse_errmsg_option_callback_t errmsg_callback) {
	return true;
}

void parse_cmdline_options(int argc, char **argv) {
	argparse_parse_or_quit(argc, argv, argument_callback, plausibilization_callback);
}
