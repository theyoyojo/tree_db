#include "node.h"

/* had to include a function like this */
bool node_kill_all_children(struct node * parent) {
	return node_kill_child(parent, 0, parent->child_count, false) ;
}

bool node_kill_child(struct node * parent, size_t child_index, size_t body_count_limit, bool preserve_memory) {
	size_t counter = 0, body_count = 0 ;
	struct node * temp, * child;
	bool success_code = true ;

	/* printf("begin node_kill_child(parent=%p, child_index=%lu, body_count_limit=%lu)\n", */
	/* 		parent, child_index, body_count_limit) ; */

	if (body_count_limit < 1) return success_code ;
	VALIDATE_NODE("kill_child") ;

	child = parent->first_child ;	

	/* child_count == 0 <==> first_child == last_child == NULL */
	while (parent->child_count > 0
	&& body_count < body_count_limit
	&& counter < parent->child_count + body_count) {
		/* printf("at loop top\n") ; */
		if (parent->child_count == 1) {
			/* no need to preserve the integrity of the list linkage if it
			 * about to be destroyed. This will cost the parent the life
			 * of their firstborn child.
			 */
			if (counter >= child_index) {
				if (!preserve_memory) {
					node_kill(&parent->first_child) ;
				}
				else {
					/* the child becomes an orphan but we don't kill it */
					parent->first_child->parent = NULL ;
				}
				parent->first_child = parent->last_child = NULL ;
				parent->child_count = 0 ;
				++body_count ;
			}
		}
		else if (parent->child_count > 1) {
			if (counter >= child_index) {
				/* printf("pre swapping siblings (b_count=%lu)\n", body_count) ; */
				/* node_print_child_linkage(parent, stdout) ; */

				child->brother->sister = child->sister ;
				child->sister->brother = child->brother ;

				/* printf("post swapped\n") ; */
				/* node_print_child_linkage(parent, stdout) ; */

				/* case: this operation requires us to modify first_child */
				if  (counter == body_count) {
					/* first_child-hood moves in the brother direction */
					parent->first_child = child->brother ;
				}
				/* case: this operation requires us to modify last_child */
				if (counter == parent->child_count - 1) {
					/* last_child-hood moves in the sister direction */
					parent->last_child = child->sister ;
				}
				temp = child->brother ;
				if (!preserve_memory) {
					node_kill(&child) ;
				}
				else {
					/* the child becomes an orphan but we don't kill it */
					child->parent = NULL ;
				}
				--parent->child_count ;
				++body_count ;
				child = temp ;
			}
			/* the final increment of this value is not necessary unless
			 * we have more than one child
			 */
			else if (parent->child_count > 1) {
				child = child->brother ;
				/* printf("at loop bottom:\n") ; */
				/* node_print_child_linkage(parent, stdout) ; */
			}
			++counter ;
			/* printf("[%lu] next child: %p\n", counter, child) ; */
			/* printf("\tfirst child: %p\n", parent->first_child) ; */
		}
	}

	/* printf("killed %lu %s\n", body_count, body_count == 1 ? "child" : "children") ; */
	return success_code ;
}

bool node_push_child(struct node * parent, struct node * child) {
	bool success_code = true ;
	struct node * temp ;

	VALIDATE_NODE("push_child") ;
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
		child->parent = parent ;
	}

	if(success_code) {
		++parent->child_count ;
	}

	return success_code ;
}


void node_print_linkage(struct node * node, FILE * file) {
	if (!node) return ;
	fprintf(file,
		"===[NODE INFO]===\n"
		"\t node:\t\t%p\n"
		"\t brother:\t%p\n"
		"\t sister:\t%p\n",
	node, node->brother, node->sister) ;
}

void node_print_child_linkage(struct node * node, FILE * file) {
	size_t counter ;
	struct node * child ;
	if (!node || !node_has_children(node)) return ;
	
	child = node->first_child ;
	for (counter = 0; counter < node_get_child_count(node); ++counter) {
		node_print_linkage(child, file) ;
		child = child->brother ;
	}
}

bool node_has_children(struct node * node) {
	return !!node->first_child ;
}

bool node_has_parent(struct node * node) {
	return node->parent != NULL ;
}

void node_kill(struct node ** node) {
	if (node && *node) {
		node_kill_all_children(*node) ;
		if ((*node)->data) (*node)->data_ops.free((*node)->data) ;
		free(*node) ;
		*node = NULL ;
	}
}

struct node * node_get_child_by_index(struct node * parent, size_t child_index) {
	struct node * child ;
	size_t counter ;

	if (!parent || child_index >= parent->child_count) return NULL ;

	if (child_index < node_get_child_count(parent) / 2) {
		child = parent->first_child ;
		for (counter = 0; counter != child_index; child = child->brother, ++counter) ;
	}
	else {
		child = parent->last_child ;
		for (counter = parent->child_count - 1;
			counter != child_index; child = child->sister, --counter) ;
	}

	return child ;
}

size_t node_get_child_count(struct node * parent) {
	return parent->child_count ;
}

bool node_verify_child_count(struct node * parent) {
	bool success_code = true ;
	/* case: no children
	 * 	verify that child_count == NULL ==> first_child == last_child = NULL
	 * 	(but really it should be <==>)
	 */
	if (parent->child_count == 0) {
		success_code = parent->first_child == NULL && parent->last_child == NULL ;
	}
	else {
		struct node * child = parent->first_child->brother ;
		size_t counter ;

		for (counter = 1; counter < node_get_child_count(parent); ++counter) {
			if (child == parent->first_child) success_code = false ;
			child = child->brother ;
		}
	}
	
	return success_code ;
}

bool node_verify_sibling_integrity(struct node * parent) {
	size_t brothers, sisters ;
	struct node * child ;
	bool success_code = true ;

	brothers = sisters = 0 ;

	if (node_get_child_count(parent)) {
		child = parent->first_child ;
		do {
			++brothers ;
			child = child->brother ;
		}
		while (child != parent->first_child) ;

		child = parent->first_child ;
		do {
			++sisters ;
			child = child->sister ;
		}
		while (child != parent->first_child) ;
	}

	success_code = brothers == parent->child_count && sisters == parent->child_count ;

	return success_code ;
}

bool node_create_child(struct node * parent, void * args) {
	bool success_code = true ;
	struct node * child ;

	VALIDATE_NODE("create_child") ;

	child = parent->create_child(args) ;	
	if(!child) {
		success_code = false ;
	}
	else {
		success_code = node_push_child(parent, child) ;
	}

	return success_code ;
}


struct node * node_pop_child_by_index(struct node * parent, size_t index) {
	struct node * child ;

	child = node_get_child_by_index(parent, index) ;
	/* the following call is the reason the option to preserve child memory on a kill was added */
	if (child) {
		node_kill_child(parent, index, 1, true) ;
	}

	return child ;
}
