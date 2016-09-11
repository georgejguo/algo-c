#ifndef DLIST_H
#define DLIST_H

#include <stdlib.h>

/* Define a structure for doubly-linked list elements. */
struct dlist_elmt {
	void *data;
	struct dlist_elmt *prev;
	struct dlist_elmt *next;
};

/* Define a structure for doubly-linked lists. */
struct dlist {
	int size;
	int (*match) (const void *key1, const void *key2);
	void (*destroy) (void *data);
	struct dlist_elmt *head;
	struct dlist_elmt *tail;
};

/* --------------------------- Public Interface --------------------------- */
void dlist_init(struct dlist *list, void (*destroy) (void *data));
void dlist_destroy(struct dlist *list);
int dlist_ins_next(struct dlist *list, struct dlist_elmt *element,
		   const void *data);
int dlist_ins_prev(struct dlist *list, struct dlist_elmt *element,
		   const void *data);
int dlist_remove(struct dlist *list, struct dlist_elmt *element, void **data);
#define dlist_size(list) ((list)->size)
#define dlist_head(list) ((list)->head)
#define dlist_tail(list) ((list)->tail)
#define dlist_is_head(element) ((element)->prev == NULL ? 1 : 0)
#define dlist_is_tail(element) ((element)->next == NULL ? 1 : 0)
#define dlist_data(element) ((element)->data)
#define dlist_next(element) ((element)->next)
#define dlist_prev(element) ((element)->prev)

#endif
