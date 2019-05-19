#include "data_node.h"
#include "data_type_none.h"
#include "udid.h"

void data_node_kill(struct node ** node) {
	node_kill(node) ;
}

struct node * data_node_create(void * args) {
	creation_arg_t * creation_args = (creation_arg_t *)args ;

	struct node * new = (struct node *)malloc(sizeof(struct node)) ;
	if (!new) return NULL ;

	*new  = (struct node){
		.udid =		udid_get_null_constant(),
		.data = 	creation_args->data,
		.metadata = 	creation_args->metadata,
		// This should be changed to do lookup based on metadata
		.ops = 		data_type_none_ops,
		.first_child = 	NULL,
		.last_child = 	NULL,
		.brother = 	NULL,
		.sister = 	NULL,
		.parent	=	NULL,
		.child_count =  0,
		.kill_self =    data_node_kill,
		.create_child = data_node_create,
	} ;

	return new ;
}

void data_node_print_type(struct node ** node) {
	(void)node ;
	// TODO 	
}
