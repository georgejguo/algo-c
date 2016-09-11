#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

/* Define a structure for linked list elements. */
struct list_elmt {
	void *data;
	struct list_elmt *next;
};

/* Define a structure for linked lists. */
typedef struct list {
	int size;
	int (*match) (const void *key1, const void *key2);
	void (*destroy) (void *data);
	struct list_elmt *head;
	struct list_elmt *tail;

} slist;

/* --------------------------- Public Interface --------------------------- */
void list_init(struct list *list, void (*destroy) (void *data));
void list_destroy(struct list *list);
int list_ins_next(struct list *list, struct list_elmt *element,
		  const void *data);
int list_rem_next(struct list *list, struct list_elmt *element, void **data);
#define list_size(list) ((list)->size)
#define list_head(list) ((list)->head)
#define list_tail(list) ((list)->tail)
#define list_is_head(list, element) ((element) == (list)->head ? 1 : 0)
#define list_is_tail(element) ((element)->next == NULL ? 1 : 0)
#define list_data(element) ((element)->data)
#define list_next(element) ((element)->next)

#endif
