#ifndef DATA_NODE_H
#define DATA_NODE_H

#include "node.h"

/*
struct node {
	void 		*data ;
	void		*metadata ;

	struct node 	*first_child ;
	struct node 	*last_child ;
	struct node     *brother ;
	struct node     *sister ;
	size_t 		child_count ;

	void		(*free_data)(void *) ;
	struct node     *(*create_child)(void * args) ;
} ;
 */


typedef struct creation_arg {
	metadata_t 	metadata ;
	void 		*data ;	
} creation_arg_t ;

struct node * data_node_create(void * args) ;

void data_node_destroy(struct node ** node) ;

#endif /* DATA_NODE_H */
