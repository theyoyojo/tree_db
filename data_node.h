#ifndef DATA_NODE_H
#define DATA_NODE_H

#include "node.h"

typedef struct creation_arg {
	metadata_t 	metadata ;
	void 		*data ;	
} creation_arg_t ;

struct node * data_node_create(void * args) ;

struct node * data_node_create_none(void) ;

void data_node_print_type(struct node * node) ;

#endif /* DATA_NODE_H */
