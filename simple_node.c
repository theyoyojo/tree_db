#include "simple_node.h"
#include <stdlib.h>

#define DEFAULT_SIMPLE_NODE_CHILD_CAPACITY 100

/*
 *
struct node {
	void 		*data ;
	void		*meta_data ;
	struct node 	**children ;
	size_t 		children_count ;
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
		if ((*node)->children) free((*node)->children) ;
		if ((*node)->data) free((*node)->data) ;
		if ((*node)->meta_data) free((*node)->meta_data) ;

		free(*node) ;
		*node = NULL ;
	}
}

bool push_child(struct node * parent, struct node * child) {
	bool success_code = true ;
	struct node ** temp ;

	VALIDATE_NODE("simple_node:push_child") ;
	/* case: no child passed to function */
	if (!child) {
		success_code = false ;
	}
	/* case: parent has no children yet */
	else if (!parent->children) {
		parent->children_capacity = DEFAULT_SIMPLE_NODE_CHILD_CAPACITY ;
		parent->children = (struct node **)malloc(
			sizeof(struct node *) * parent->children_capacity) ;
		if (!parent->children) success_code = false ;
		parent->children_count = 0 ;
	}
	else {
		if (parent->children_count >= parent->children_capacity) {
			parent->children_capacity *= 2 ;
			temp = (struct node **)realloc(parent->children,
				sizeof(struct node *) * parent->children_capacity) ;
			if (!temp) {
				success_code = false ;
			}
			else {
				parent->children = temp ;
			}
		}
	}

	if(success_code) {
		parent->children[parent->children_count++] = child ;
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

	new->children = NULL ;
	new->children_count = 0 ;

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
