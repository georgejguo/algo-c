#include <stdio.h>
#include "clist.h"

void data_destroy(void *data)
{
	free(data);
}

int main()
{
	int i;
	int ret;
	void *data;
	struct clist *list;
	struct clist_elmt *element;

	/* create a null list */
	list = (struct clist *)malloc(sizeof(struct clist));
	if (!list)
		return -1;
	clist_init(list, data_destroy);

	/* add element to list */
	element = clist_head(list);
	for (i = 0; i < 5; i++) {
		data = (void *)malloc(sizeof(int));
		if (!data)
			return -1;

		*(int *)data = i;
		ret = clist_ins_next(list, element, data);
		if (ret == 0) {
			if (!element)
				element = clist_head(list);
			else
				element = clist_next(element);
		} else {
			printf("err:%d ret=%d\n", __LINE__, ret);
			return ret;
		}
	}

	/* print all elements' data */
	element = clist_head(list);
	for (i = 0; i < clist_size(list); i++) {
		printf("%d\n", *(int *)element->data);
		element = element->next;
	}

	/* destroy list */
	clist_destroy(list);
	free(list);

	return 0;
}
