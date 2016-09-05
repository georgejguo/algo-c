#ifndef DLIST_H
#define DLIST_H

#include <stdlib.h>

/* Define a structure for doubly-linked list elements. */
typedef struct dlist_elmt_ {
	void *data;
	struct dlist_elmt_ *prev;
	struct dlist_elmt_ *next;
} dlist_elmt;

/* Define a structure for doubly-linked lists. */
typedef struct dlist_ {
	int size;
	int (*match)(const void *key1, const void *key2);
	void (*destroy)(void *data);
	dlist_elmt *head;
	dlist_elmt *tail;
} dlist;

/* --------------------------- Public Interface --------------------------- */
void dlist_init(dlist *list, void (*destroy)(void *data));
void dlist_destroy(dlist *list);
int dlist_ins_next(dlist *list, dlist_elmt *element, const void *data);
int dlist_ins_prev(dlist *list, dlist_elmt *element, const void *data);
int dlist_remove(dlist *list, dlist_elmt *element, void **data);
#define dlist_size(list) ((list)->size)
#define dlist_head(list) ((list)->head)
#define dlist_tail(list) ((list)->tail)
#define dlist_is_head(element) ((element)->prev == NULL ? 1 : 0)
#define dlist_is_tail(element) ((element)->next == NULL ? 1 : 0)
#define dlist_data(element) ((element)->data)
#define dlist_next(element) ((element)->next)
#define dlist_prev(element) ((element)->prev)

#endif
