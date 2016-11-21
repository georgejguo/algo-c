#include <stdlib.h>
#include "queue.h"

int queue_enqueue(queue * queue, const void *data)
{
	/* Enqueue the data. */
	return list_ins_next(queue, list_tail(queue), data);
}

int queue_dequeue(queue * queue, void **data)
{
	/* Dequeue the data. */
	return list_rem_next(queue, NULL, data);
}
