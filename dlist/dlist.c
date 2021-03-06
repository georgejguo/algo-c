#include <stdlib.h>
#include <string.h>
#include "dlist.h"

void dlist_init(struct dlist *list, void (*destroy) (void *data))
{
	/* Initialize the list. */
	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;
}

/* Destroys the doubly-linked list specified by 'list'. No other operations are
 * permitted after calling dlist_destroy unless dlist_init is called again. The
 * dlist_destroy operation removes all elements from a doubly-linked list and 
 * calls the function passed as destroy to dlist_init once for each element as 
 * it is removed, provided destroy was not set to NULL.
 */
void dlist_destroy(struct dlist *list)
{
	void *data;

	/* Remove each element. */
	while (dlist_size(list) > 0) {
		if (dlist_remove(list, dlist_tail(list), (void **)&data) == 0
		    && list->destroy != NULL)
			list->destroy(data);
	}
	memset(list, 0, sizeof(struct dlist));
}

/* Inserts an element just after 'element' in the linked list specified by list. 
 * If element is NULL, the new element is inserted at the head of the list. The
 * new element contains a pointer to data, so the memory referenced by data 
 * should remain valid as long as the element remains in the list. It is the 
 * responsibility of the caller to manage the storage associated with data.
 */
int dlist_ins_next(struct dlist *list, struct dlist_elmt *element,
		   const void *data)
{
	struct dlist_elmt *new_element;
	/* Do not allow a NULL element unless the list is empty. */
	if (element == NULL && dlist_size(list) != 0)
		return -1;
	/* Allocate storage for the element. */
	if ((new_element =
	     (struct dlist_elmt *)malloc(sizeof(struct dlist_elmt))) == NULL)
		return -1;
	/* Insert the new element into the list. */
	new_element->data = (void *)data;

	if (dlist_size(list) == 0) {
		/* Handle insertion when the list is empty. */
		list->head = new_element;
		list->head->prev = NULL;
		list->head->next = NULL;
		list->tail = new_element;

	} else {
		/* Handle insertion when the list is not empty. */
		new_element->next = element->next;
		new_element->prev = element;
		if (element->next == NULL)
			list->tail = new_element;
		else
			element->next->prev = new_element;
		element->next = new_element;
	}

	list->size++;
	return 0;
}

int dlist_ins_prev(struct dlist *list, struct dlist_elmt *element,
		   const void *data)
{
	struct dlist_elmt *new_element;
	/* Do not allow a NULL element unless the list is empty. */
	if (element == NULL && dlist_size(list) != 0)
		return -1;
	/* Allocate storage to be managed by the abstract datatype. */
	if ((new_element =
	     (struct dlist_elmt *)malloc(sizeof(struct dlist_elmt))) == NULL)
		return -1;
	/* Insert the new element into the list. */
	new_element->data = (void *)data;
	if (dlist_size(list) == 0) {
		/* Handle insertion when the list is empty. */
		list->head = new_element;
		list->head->prev = NULL;
		list->head->next = NULL;
		list->tail = new_element;

	} else {
		/* Handle insertion when the list is not empty. */
		new_element->next = element;
		new_element->prev = element->prev;
		if (element->prev == NULL)
			list->head = new_element;
		else
			element->prev->next = new_element;
		element->prev = new_element;
	}

	list->size++;
	return 0;
}

int dlist_remove(struct dlist *list, struct dlist_elmt *element, void **data)
{
	/* Do not allow a NULL element or removal from an empty list. */
	if (element == NULL || dlist_size(list) == 0)
		return -1;
	/* Remove the element from the list. */
	*data = element->data;
	if (element == list->head) {
		/* Handle removal from the head of the list. */
		list->head = element->next;
		if (list->head == NULL)
			list->tail = NULL;
		else
			element->next->prev = NULL;
	} else {
		/* Handle removal from other than the head of the list. */
		element->prev->next = element->next;
		if (element->next == NULL)
			list->tail = element->prev;
		else
			element->next->prev = element->prev;

	}

	free(element);
	list->size--;
	return 0;
}
