#ifndef QUEUE_H
#define QUEUE_H
#include <stdlib.h>
#include "../list/list.h"

 /* Implement queues as linked lists. */
typedef slist queue;

 /* --------------------------- Public Interface --------------------------- */
#define queue_init list_init
#define queue_destroy list_destroy
int queue_enqueue(queue * queue, const void *data);
int queue_dequeue(queue * queue, void **data);
#define queue_peek(queue) ((queue)->head == NULL ? NULL : (queue)->head->data)
#define queue_size list_size

#endif
