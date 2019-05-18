#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdbool.h>

/* Don't do anything on an invalid node that could be risky */
#define VALIDATE_NODE(msg) ({ \
		if (!parent->data || !parent->meta_data) { \
			fprintf(stderr,"Invalid node: %s\n",msg) ; \
			return false ; \
		} \
	}) ; \


struct node ;

/* Creation functions will be specified for each node specializaiton,
 * but they all must know how to kill themselves and reproduce
 */
struct node {
	void 		*data ;
	void		*meta_data ;

	struct node 	*first_child ;
	struct node 	*last_child ;
	struct node     *brother ;
	struct node     *sister ;
	size_t 		children_count ;

	void		(*kill_self)(struct node **) ;
	struct node     *(*create_child)(void * args) ;
	bool 		(*push_child)(struct node *, struct node *) ;
} ;

//void node_child_list_remove(struct node ** pHead,

inline bool node_kill_child(struct node * parent, size_t child_index, size_t body_count_limit) {
	size_t counter = 0, body_count = 0 ;
	struct node ** pHead ;
	struct node temp ;
	bool success_code = true ;


	if (body_count < 1) return success_code ;

	VALIDATE_NODE("kill_child") ;

	if (parent->children_count < 1) return success_code ;

	pHead = &parent->first_child ;

	while(body_count < body_count_limit && *pHead) {
		if (counter >= child_index) {
			temp = (*pHead)->next ;
			free (*pHead) ;
			*pHead = temp ;
		}
		++counter
		pHead = (*pHead)->next ;
	}

	if (success_code) {
		parent->children_count -= body_count ;
	}

	return success_code ;
}

/* had to include a function like this */
inline bool node_kill_all_children(struct node * parent) {
	return node_kill_child(parent, 0, parent->children_count) ;
}

inline bool node_create_child(struct node * parent, void * args) {
	bool success_code = true ;
	struct node * child ;

	VALIDATE_NODE("create_child") ;

	child = parent->create_child(args) ;	
	if(!child) {
		success_code = false ;
	}
	else {
		success_code = parent->push_child(parent, child) ;
	}

	return success_code ;
}

#endif /* NODE_H */
