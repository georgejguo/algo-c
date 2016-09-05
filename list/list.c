#include <stdlib.h>
#include <string.h>
#include "list.h"

void list_init(list * list, void (*destroy) (void *data))
{
	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;
}

void list_destroy(list * list)
{
	void *data;

	/* remove each element */
	while (list_size(list) > 0) {
		if (list_rem_next(list, NULL, (void **)&data) == 0
		    && list->destroy != NULL)
			list->destroy(data);
	}

	memset(list, 0, sizeof(list));
}

/* Inserts an element just after 'element' in the linked list specified by list.
 * If element is NULL, the new element is inserted at the head of the list.
 */
int list_ins_next(list * list, list_elmt * element, const void *data)
{
	list_elmt *new_element;

	if ((new_element = (list_elmt *) malloc(sizeof(list_elmt))) == NULL)
		return -1;
	new_element->data = (void *)data;

	if (element == NULL) {
		if (list_size(list) == 0)
			list->tail = new_element;
		new_element->next = list->head;	// new_element->next
		list->head = new_element;
	} else {
		if (element->next == NULL)
			list->tail = new_element;
		new_element->next = element->next;	// new_element->next
		element->next = new_element;
	}

	list->size++;
	return 0;
}

/* Removes the element just after 'element' from the linked list specified by
 * list. If element is NULL, the element at the head of the list is removed.
 */
int list_rem_next(list * list, list_elmt * element, void **data)
{
	list_elmt *old_element;

	if (list_size(list) == 0)
		return -1;

	if (element == NULL) {
		*data = list->head->data;	// data
		old_element = list->head;	// old_element
		list->head = list->head->next;
		if (list_size(list) == 1)
			list->tail = NULL;
	} else {
		if (element->next == NULL)
			return -1;
		*data = element->next->data;	// data
		old_element = element->next;	// old_element
		element->next = element->next->next;
		if (element->next == NULL)
			list->tail = element;
	}

	free(old_element);
	list->size--;
	return 0;
}
