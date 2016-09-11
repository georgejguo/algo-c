#ifndef STACK_H
#define STACK_H
#include <stdlib.h>
#include "../list/list.h"

 /* Implement stacks as linked lists. */
typedef slist stack;

 /* --------------------------- Public Interface --------------------------- */
#define stack_init list_init
#define stack_destroy list_destroy
int stack_push(stack * stack, const void *data);
int stack_pop(stack * stack, void **data);
#define stack_peek(stack) ((stack)->head == NULL ? NULL : (stack)->head->data)
#define stack_size list_size

#endif
