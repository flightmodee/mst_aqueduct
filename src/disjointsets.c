#include "disjointsets.h"
#include <stdio.h>
#include <stdlib.h>

node_t *make_set(){

	node_t *node;
	if ((node = (node_t*)malloc(sizeof(node_t))) == NULL){
		perror("The memory allocation failed. Exit.\n");
		return(NULL);
	}
	node->father = node;
	node->rank = 0;

	return (node);
}

void set_link(node_t *x, node_t *y){

	if (x->rank > y->rank)
		y->father = x;
	else 
		x->father = y;

	if (x->rank == y->rank)
		y->rank++;
}

node_t *find_set(node_t *node){

	if (node->father != node)
		node->father = find_set(node->father);

	return(node->father);
}

void set_union(node_t *x, node_t *y){
	set_link(find_set(x), find_set(y));
}
