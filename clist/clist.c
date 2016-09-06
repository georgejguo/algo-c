#include <stdlib.h>
#include <string.h>
#include "clist.h"

void clist_init(clist * list, void (*destroy) (void *data))
{
	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
}

void clist_destroy(clist * list)
{
	void *data;

	/* Remove each element. */
	while (clist_size(list) > 0) {
		if (clist_rem_next(list, list->head, (void **)&data) == 0
		    && list->destroy != NULL) {
			/* Call a user-defined function to free dynamically
			 * allocated data. */
			list->destroy(data);
		}
	}

	memset(list, 0, sizeof(clist));
}

int clist_ins_next(clist * list, clist_elmt * element, const void *data)
{
	clist_elmt *new_element;

	if ((new_element = (clist_elmt *) malloc(sizeof(clist_elmt))) == NULL)
		return -1;

	new_element->data = (void *)data;
	if (clist_size(list) == 0) {
		/* Handle insertion when the list is empty. */
		new_element->next = new_element;
		list->head = new_element;

	} else {
		/* Handle insertion when the list is not empty. */
		new_element->next = element->next;
		element->next = new_element;
	}

	list->size++;
	return 0;

}

int clist_rem_next(clist * list, clist_elmt * element, void **data)
{
	clist_elmt *old_element;

	/* Do not allow removal from an empty list. */
	if (clist_size(list) == 0)
		return -1;

	/* Remove the element from the list. */
	*data = element->next->data;
	if (element->next == element) {
		/* Handle removing the last element. */
		old_element = element->next;
		list->head = NULL;

	} else {
		/* Handle removing other than the last element. */
		old_element = element->next;
		element->next = element->next->next;
		if (old_element == clist_head(list))
			list->head = old_element->next;
	}

	free(old_element);
	list->size--;

	return 0;
}
