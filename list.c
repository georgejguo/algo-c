#include <stdlib.h>
#include <string.h>
#include "list.h"

void list_init(List *list, void (*destroy) (void *data))
{
	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;
}

void list_destroy(List *list)
{
	void *data;

	/* remove each element */
	while (list_size(list) > 0) {
		if (list_rem_next(list, NULL, (void **)&data) == 0
		    && list->destroy != NULL)
			list->destroy(data);
	}

	memset(list, 0, sizeof(List));
}

/* Inserts an element just after 'element' in the linked list specified by list.
 * If element is NULL, the new element is inserted at the head of the list.
 */
int list_ins_next(List *list, ListElmt *element, const void *data)
{
	ListElmt *new_element;

	if ((new_element = (ListElmt *) malloc(sizeof(ListElmt))) == NULL)
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
int list_rem_next(List *list, ListElmt *element, void **data)
{
	ListElmt *old_element;

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
