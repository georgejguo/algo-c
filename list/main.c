#include <stdio.h>
#include "list.h"

void data_destroy(void *data)
{
	free(data);
}

int main()
{
	int i;
	int ret;
	void *data;
	list *list;
	list_elmt *element;

	/* create a null list */
	list = (struct list_ *)malloc(sizeof(struct list_));
	if (!list)
		return -1;
	list_init(list, data_destroy);

	/* add element to list */
	element = list_head(list);
	for (i = 0; i < 5; i++) {
		data = (void *)malloc(sizeof(int));
		if (!data) {
			return -1;
		}

		*(int *)data = i;
		ret = list_ins_next(list, element, data);
		if (ret == 0) {
			if (!element)
				element = list_head(list);
			else
				element = list_next(element);
		} else {
			printf("err:%d ret=%d\n", __LINE__, ret);
			return ret;
		}
	}

	/* print all elements' data */
	element = list_head(list);
	for (i = 0; i < list_size(list); i++) {
		printf("%d\n", *(int *)element->data);
		element = element->next;
	}

	/* destroy list */
	list_destroy(list);
	free(list);

	return 0;
}
