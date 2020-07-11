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

#ifndef __LLIST_H__
#define __LLIST_H__

#include <stdbool.h>
#include <pthread.h>

struct llist_t;

struct llist_element_t {
	void *payload;
	struct llist_t *list;
	struct llist_element_t *next, *prev;
	bool free_payload_with_list;
};

struct llist_t {
	pthread_mutex_t mutex;
	struct llist_element_t *head;
	struct llist_element_t *tail;
	unsigned int elements;
};

typedef void (*ll_element_callback_t)(struct llist_element_t *element, void *ctx);

#define LINKEDLIST_INITIALIZER			{													\
												.mutex = PTHREAD_MUTEX_INITIALIZER,			\
												.head = NULL,								\
												.elements = 0,								\
										}

/*************** AUTO GENERATED SECTION FOLLOWS ***************/
void llist_remove_element_nolock(struct llist_element_t *element);
void llist_remove_element(struct llist_element_t *element);
void llist_traverse(struct llist_t *list, ll_element_callback_t callback, void *ctx);
struct llist_element_t *llist_append(struct llist_t *list, void *new_payload, bool free_with_list);
void* llist_pop(struct llist_t *list);
struct llist_element_t *llist_append_alloc(struct llist_t *list, void *new_payload, unsigned int payload_size);
void llist_free(struct llist_t *list);
/***************  AUTO GENERATED SECTION ENDS   ***************/

#endif
