#include "data_node.h"
#include "data_type_none.h"
#include "udid.h"

struct node * data_node_create(void * args) {
	creation_arg_t * creation_args = (creation_arg_t *)args ;

	struct node * new = (struct node *)malloc(sizeof(struct node)) ;
	if (!new) return NULL ;

	*new  = (struct node){
		.udid =		udid_get_null_constant(),
		.data = 	creation_args->data,
		.metadata = 	creation_args->metadata,
		// This should be changed to do lookup based on metadata
		.data_ops = 	data_type_none_ops,
		.first_child = 	NULL,
		.last_child = 	NULL,
		.brother = 	NULL,
		.sister = 	NULL,
		.parent	=	NULL,
		.child_count =  0,
		.create_child = data_node_create,
	} ;

	new->udid = udid_calculate(new->data_ops.get_bytes(new),
			new->data_ops.get_length(new)) ;

	return new ;
}

struct node * data_node_create_none(void) {
	return data_node_create((void *)&NONE_ARGS) ;
}

#define SMALL_BUFLEN 64
void data_node_print_type(struct node * node) {
	(void)node ;
	char buf[SMALL_BUFLEN] ;
	node->data_ops.get_string(node, buf, sizeof(buf)) ;
	printf("%s\n", buf) ;
}

