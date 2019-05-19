#include "simple_node.h"
#include <stdlib.h>
#include <lil_test.h>

/*
 *
struct node {
	void 		*data ;
	void		*metadata ;
	struct node 	*first_child;
	struct node 	*last_child;
	size_t 		child_count ;
	size_t		children_capacity ;
	void		(*kill_self)(struct node **) ;
	struct node     *(*create_child)(void * args) ;
} ;
 *
 */

void simple_node_kill_self(struct node ** node) {
	node_kill(node) ;
}

struct node * simple_node_create(void * args) {

	(void)args ;

	struct node * new = (struct node *)malloc(sizeof(struct node)) ;
	if (!new) return NULL ;

	new->data = (void *)malloc(sizeof(int)) ;
	if (!new->data) { free(new) ; return NULL ; } ;
	*(int *)(new->data) = 0 ;

	new->metadata.data = 0 ;

	new->first_child = new->last_child =
		new->brother = new->sister = NULL ;
	new->child_count = 0 ;

	new->kill_self = simple_node_kill_self ;
	new->create_child = simple_node_create ;

	new->ops = (data_ops_t){
		.get_bytes = LAMBDA(void *, (struct node * node){return (void *)new->data ;} ),
		.get_length = LAMBDA(size_t, (struct node * node){return sizeof(int);} ),
		.get_string = LAMBDA(bool, (struct node * node, char * buf, size_t buflen)
				{ return snprintf(buf, buflen, "%d", new->data) > 0 ;}),
		.set_data = LAMBDA(bool, (struct node * node, void * data)
				{ if (!data) return false ;
				*(int*)new->data = *(int*)data ; return true ;}),
		.free_data = free,
	} ;

	new->parent = NULL ;

	return  new ;
}

void simple_node_destroy(struct node ** node) {
	(*node)->kill_self(node) ;
}

int simple_node_get_data(struct node * parent) {
	return *(int*)parent->data ;
}
void simple_node_set_data(struct node * parent, int data) {
	*(int*)parent->data = data ;
}
