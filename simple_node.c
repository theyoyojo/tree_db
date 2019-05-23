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

	new->create_child = simple_node_create ;

	new->data_ops = (data_ops_t){
		.get_bytes = LAMBDA(void *, (struct node * node){return (void *)new->data ;} ),
		.get_length = LAMBDA(size_t, (struct node * node){return sizeof(int);} ),
		.get_string = LAMBDA(bool, (struct node * node, char * buf, size_t buflen)
				{ return snprintf(buf, buflen, "%d", new->data) > 0 ;}),
		.set_data = LAMBDA(bool, (struct node * node, void * data, size_t size)
				{ if (!data) return false ;
				*(int*)new->data = *(int*)data ; return true ;}),
		.free_data = free,
		.compare_data = LAMBDA(int,(void * first, void * second)
				{ return *(int *)first - *(int *)second ; }),
	} ;

	new->parent = NULL ;

	return  new ;
}

int simple_node_get_data(struct node * parent) {
	return *(int*)parent->data ;
}
void simple_node_set_data(struct node * parent, int data) {
	*(int*)parent->data = data ;
}
