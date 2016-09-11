#include <stdlib.h>
#include "stack.h"

int stack_push(stack * stack, const void *data)
{
	/* Push the data onto the stack. */
	return list_ins_next(stack, NULL, data);	// NULL
}

int stack_pop(stack * stack, void **data)
{
	/* Pop the data off the stack. */
	return list_rem_next(stack, NULL, data);	// NULL
}
