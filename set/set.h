#ifndef SET_H
#define SET_H
#include <stdlib.h>
#include "../list/list.h"

 /* Implement sets as linked lists. */
typedef slist set;

 /* --------------------------- Public Interface --------------------------- */
void set_init(set *set, int (*match)(const void *key1, const void *key2),
	      void (*destroy)(void *data));
#define set_destroy list_destroy
int set_insert(set *set, const void *data);
int set_remove(set *set, void **data);
int set_union(set *setu, const set *set1, const set *set2);
int set_intersection(set *seti, const set *set1, const set *set2);
int set_difference(set *setd, const set *set1, const set *set2);
int set_is_member(const set *set, const void *data);
int set_is_subset(const set *set1, const set *set2);
int set_is_equal(const set *set1, const set *set2);
#define set_size(set) ((set)->size)

#endif
