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

#include <stdlib.h>
#include <string.h>
#include "llist.h"

static void llist_lock(struct llist_t *list) {
	pthread_mutex_lock(&list->mutex);
}

static void llist_unlock(struct llist_t *list) {
	pthread_mutex_unlock(&list->mutex);
}

static void llist_free_element(struct llist_element_t *element) {
	if (element->free_payload_with_list) {
		free(element->payload);
	}
	free(element);
}

/* This function should be used when removing list elements during traversal */
void llist_remove_element_nolock(struct llist_element_t *element) {
	struct llist_t *list = element->list;
	list->elements--;
	if (element->next) {
		element->next->prev = element->prev;
	}
	if (element->prev) {
		element->prev->next = element->next;
	}
	if (list->head == element) {
		list->head = element->next;
	}
	llist_free_element(element);
}

void llist_remove_element(struct llist_element_t *element) {
	struct llist_t *list = element->list;
	llist_lock(list);
	llist_remove_element_nolock(element);
	llist_unlock(list);
}

void llist_traverse(struct llist_t *list, ll_element_callback_t callback, void *ctx) {
	llist_lock(list);
	struct llist_element_t *cur = list->head;
	while (cur) {
		struct llist_element_t *next = cur->next;
		callback(cur, ctx);
		cur = next;
	}
	llist_unlock(list);
}

struct llist_element_t *llist_append(struct llist_t *list, void *new_payload, bool free_with_list) {
	struct llist_element_t *element = malloc(sizeof(*element));
	if (!element) {
		return NULL;
	}

	element->list = list;
	element->payload = new_payload;
	element->prev = NULL;
	element->free_payload_with_list = free_with_list;

	llist_lock(list);
	if (list->head) {
		list->head->prev = element;
	}
	element->next = list->head;
	list->head = element;
	list->elements++;
	llist_unlock(list);

	return element;
}

struct llist_element_t *llist_append_alloc(struct llist_t *list, void *new_payload, unsigned int payload_size) {
	void *payload_copy = malloc(payload_size);
	if (!payload_copy) {
		return NULL;
	}
	memcpy(payload_copy, new_payload, payload_size);

	struct llist_element_t *result = llist_append(list, payload_copy, true);
	if (!result) {
		free(payload_copy);
		return NULL;
	}

	return result;
}

void llist_free(struct llist_t *list) {
	llist_lock(list);
	struct llist_element_t *cur = list->head;
	while (cur) {
		struct llist_element_t *next = cur->next;
		llist_free_element(cur);
		cur = next;
	}
	llist_unlock(list);
}

#ifdef __TEST_LLIST__
/* gcc -D__TEST_LLIST__ -O3 -std=c11 -Wall -Wmissing-prototypes -Wstrict-prototypes -Werror=implicit-function-declaration -Werror=format -Wshadow -pthread -ggdb3 -fsanitize=address -fsanitize=undefined -fsanitize=leak -fno-omit-frame-pointer -D_FORTITY_SOURCE=2  -o llist llist.c
 */
#include <stdio.h>
#include <assert.h>

static void ll_printstr_callback(struct llist_element_t *element, void *ctx) {
	printf("Element: \"%s\"\n", (const char*)element->payload);
}

static void ll_remove_callback(struct llist_element_t *element, void *ctx) {
	llist_remove_element_nolock(element);
}

static void llist_validate(struct llist_t *list) {
	if (list->elements == 0) {
		assert(list->head == NULL);
	} else {
		assert(list->head != NULL);
		assert(list->head->prev == NULL);
		struct llist_element_t *cur = list->head;
		unsigned int counted_elements = 0;
		while (cur) {
			counted_elements++;
			if (cur->prev) {
				assert(cur->prev->next == cur);
			}
			if (cur->next) {
				assert(cur->next->prev == cur);
			}
			cur = cur->next;
		}
		assert(counted_elements == list->elements);
	}
}

static void llist_dump(struct llist_t *list) {
	fprintf(stderr, "List %d elements head %p:\n", list->elements, list->head);
	struct llist_element_t *cur = list->head;
	while (cur) {
		fprintf(stderr, "[%16p] <- %p -> [%16p]\n", cur->prev, cur, cur->next);
		cur = cur->next;
	}
	fprintf(stderr, "\n");
	llist_validate(list);
}


int main(void) {
	struct llist_t list = LINKEDLIST_INITIALIZER;
	llist_dump(&list);
	struct llist_element_t *eins = llist_append_alloc(&list, "Eins", 5);
	llist_dump(&list);
	struct llist_element_t *zwei = llist_append_alloc(&list, "Zwei", 5);
	llist_dump(&list);
	struct llist_element_t *drei = llist_append_alloc(&list, "Drei", 5);
	llist_dump(&list);
	llist_append_alloc(&list, "Moep", 5);
	llist_dump(&list);

	llist_remove_element(drei);
	llist_dump(&list);

	llist_remove_element(eins);
	llist_dump(&list);

	llist_remove_element(zwei);
	llist_dump(&list);

	llist_traverse(&list, ll_printstr_callback, NULL);

	llist_traverse(&list, ll_remove_callback, NULL);
	llist_dump(&list);

	llist_free(&list);
	return 0;
}
#endif
