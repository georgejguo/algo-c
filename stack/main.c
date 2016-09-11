#include <stdio.h>
#include "stack.h"

void data_destroy(void *data)
{
	free(data);
}

int main()
{
	int i;
	int ret;
	int size;
	void *data;
	stack *stack;

	/* create a null stack */
	stack = (slist *)malloc(sizeof(slist));
	if (!stack)
		return -1;
	stack_init(stack, data_destroy);

	/* push data to stack */
	for (i = 0; i < 5; i++) {
		data = (void *)malloc(sizeof(int));
		if (!data) {
			return -1;
		}

		*(int *)data = i;
		ret = stack_push(stack, data);
		if (ret) {
			printf("err:%d ret=%d\n", __LINE__, ret);
			goto destroy_stack;
		}
	}

	/* stack pop data */
	size = stack_size(stack);
	for (i = 0; i < size; i++) {
		printf("stack peek data = %d\n", *(int *)stack_peek(stack));
		stack_pop(stack, &data);
		printf("stack pop data = %d\n", *(int *)data);
		data_destroy(data);
	}

destroy_stack:
	/* destroy stack */
	stack_destroy(stack);
	free(stack);

	return 0;
}
