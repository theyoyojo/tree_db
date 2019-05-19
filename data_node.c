#include "data_node.h"


struct node * data_node_create(void * args) {
	creation_arg_t * creation_args = (creation_arg_t *)args ;

	struct node * new = (struct node *)malloc(sizeof(struct node)) ;
	if (!new) return NULL ;

	*new  = (struct node){
		.data = 	creation_args->data,
		.metadata = 	creation_args->metadata,
		.first_child = 	NULL,
		.last_child = 	NULL,
		.brother = 	NULL,
		.sister = 	NULL,
		.child_count =  0,
		.free_data =	free,
		.create_child = data_node_create,
	} ;

	return new ;
}

