#ifndef SIMPLE_NODE_H
#define SIMPLE_NODE_H

#include "node.h"

struct node * simple_node_create(void * args) ;

void simple_node_destroy(struct node ** node) ;

int simple_node_get_int(struct node * parent) ;
void simple_node_set_int(struct node * parent, int data) ;

#endif /* SIMPLE_NODE_H */
