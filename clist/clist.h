#ifndef CLIST_H
#define CLIST_H
#include <stdlib.h>

/* Define a structure for circular list elements. */
typedef struct clist_elmt_ {
	void *data;
	struct clist_elmt_ *next;
} clist_elmt;

/* Define a structure for circular lists. */
typedef struct clist_ {
	int size;
	int (*match) (const void *key1, const void *key2);
	void (*destroy) (void *data);
	clist_elmt *head;
} clist;

/* --------------------------- Public Interface --------------------------- */
void clist_init(clist *list, void (*destroy)(void *data));
void clist_destroy(clist *list);
int clist_ins_next(clist *list, clist_elmt *element, const void *data);
int clist_rem_next(clist *list, clist_elmt *element, void **data);
#define clist_size(list) ((list)->size)
#define clist_head(list) ((list)->head)
#define clist_data(element) ((element)->data)
#define clist_next(element) ((element)->next)

#endif
