#include <stdio.h>
#include "dlist.h"

void data_destroy(void *data)
{
	free(data);
}

int main()
{
	int i;
	int ret;
	void *data;
	struct dlist *list;
	struct dlist_elmt *element;

	/* create a null list */
	list = (struct dlist *)malloc(sizeof(struct dlist));
	if (!list)
		return -1;
	dlist_init(list, data_destroy);

	/* add element to list */
	element = dlist_head(list);
	for (i = 0; i < 5; i++) {
		data = (void *)malloc(sizeof(int));
		if (!data) {
			while (i > 0) {
				if (dlist_remove(list, element, (void **)&data)
				    == 0 && list->destroy != NULL)
					list->destroy(data);
				element = dlist_prev(element);
				i--;
			}
			break;
		}

		*(int *)data = i;
		ret = dlist_ins_next(list, element, data);
		if (ret == 0) {
			if (!element)
				element = dlist_head(list);
			else
				element = dlist_next(element);
		} else {
			printf("err:%d ret=%d\n", __LINE__, ret);
			return ret;
		}
	}

	/* print all elements' data */
	element = dlist_head(list);
	for (i = 0; i < dlist_size(list); i++) {
		printf("%d\n", *(int *)element->data);
		element = element->next;
	}

	/* destroy list */
	dlist_destroy(list);
	free(list);

	return 0;
}
