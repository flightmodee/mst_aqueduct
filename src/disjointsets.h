#ifndef __DISJOINTSETS__
#define __DISJOINTSETS__

#include <stddef.h>

typedef struct node_s{

	int rank;
	struct node_s *father;

}	node_t;

node_t *make_set();

void set_union(node_t *x, node_t *y);

void set_link(node_t *x, node_t *y);

node_t *find_set(node_t *node);

#endif
