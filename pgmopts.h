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

#ifndef __PGMOPTS_H__
#define __PGMOPTS_H__

struct pgmopts_t {
	const char *socket_username;
	int socket_permissions;
	bool random_btle_address;
	char dest_mac_address[32];
	const char *socket;
};

extern const struct pgmopts_t *pgmopts;

/*************** AUTO GENERATED SECTION FOLLOWS ***************/
void parse_cmdline_options(int argc, char **argv);
/***************  AUTO GENERATED SECTION ENDS   ***************/

#endif
