#ifndef DATA_NODE_H
#define DATA_NODE_H

#include "node.h"

typedef struct creation_arg {
	metadata_t 	metadata ;
	void 		*data ;	
} creation_arg_t ;

struct node * data_node_create(void * args) ;

void data_node_kill(struct node ** node) ;

void data_node_print_type(struct node ** node) ;

#endif /* DATA_NODE_H */
