#ifndef CLIST_H
#define CLIST_H
#include <stdlib.h>

/* Define a structure for circular list elements. */
struct clist_elmt {
	void *data;
	struct clist_elmt *next;
};

/* Define a structure for circular lists. */
struct clist {
	int size;
	int (*match) (const void *key1, const void *key2);
	void (*destroy) (void *data);
	struct clist_elmt *head;
};

/* --------------------------- Public Interface --------------------------- */
void clist_init(struct clist *list, void (*destroy) (void *data));
void clist_destroy(struct clist *list);
int clist_ins_next(struct clist *list, struct clist_elmt *element,
		   const void *data);
int clist_rem_next(struct clist *list, struct clist_elmt *element, void **data);
#define clist_size(list) ((list)->size)
#define clist_head(list) ((list)->head)
#define clist_data(element) ((element)->data)
#define clist_next(element) ((element)->next)

#endif
