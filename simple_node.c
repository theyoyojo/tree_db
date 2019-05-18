#include "simple_node.h"
#include <stdlib.h>

#define DEFAULT_SIMPLE_NODE_CHILD_CAPACITY 100

/*
 *
struct node {
	void 		*data ;
	void		*meta_data ;
	struct node 	**children ;
	size_t 		child_count ;
	size_t		children_capacity ;
	void		(*kill_self)(struct node **) ;
	struct node     *(*create_child)(void * args) ;
	bool 		(*push_child)(struct node *, struct node *) ;
} ;
 *
 */

void kill_self(struct node ** node) {
	if (node && *node) {
		node_kill_all_children(*node) ;
		if ((*node)->data) free((*node)->data) ;
		if ((*node)->meta_data) free((*node)->meta_data) ;

		free(*node) ;
		*node = NULL ;
	}
}

bool push_child(struct node * parent, struct node * child) {
	bool success_code = true ;
	struct node * temp ;

	VALIDATE_NODE("simple_node:push_child") ;
	/* case: no child passed to function */
	if (!child) {
		success_code = false ;
	}

	/* case: parent has no children yet */
	if (success_code && !parent->first_child) {
		parent->first_child = parent->last_child = child ;
		child->brother = child->sister = parent->first_child ;
	}
	/* case: parent already has one or more children */
	else if (success_code) {
		/* the linking of the list */
		parent->last_child->brother = child ;
		child->sister = parent->last_child ;
		child->brother = parent->first_child ;
		parent->first_child->sister = child ;
		
		/* newly linked, now inserted */
		temp = parent->last_child ;
		parent->last_child = child ;
	}

	if(success_code) {
		++parent->child_count ;
	}

	return success_code ;
}

struct node * simple_node_create(void * args) {

	(void)args ;

	struct node * new = (struct node *)malloc(sizeof(struct node)) ;
	if (!new) return NULL ;

	new->data = (void *)malloc(sizeof(int)) ;
	if (!new->data) { free(new) ; return NULL ; } ;
	*(int *)(new->data) = 0 ;

	new->meta_data = (void *)malloc(sizeof(int)) ;
	if (!new->data) { free(new) ; free(new->meta_data) ; return NULL ; } ;
	*(int *)(new->meta_data) = 0 ;

	new->first_child = new->last_child =
		new->brother = new->sister = NULL ;
	new->child_count = 0 ;

	new->kill_self = kill_self ;
	new->create_child = simple_node_create ;
	new->push_child = push_child ;

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

int simple_node_get_metadata(struct node * parent) {
	return *(int*)parent->meta_data ;
}
void simple_node_set_metadata(struct node * parent, int data) {
	*(int*)parent->meta_data = data ;
}
