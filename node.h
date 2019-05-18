#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

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
	size_t 		child_count ;

	void		(*kill_self)(struct node **) ;
	struct node     *(*create_child)(void * args) ;
	bool 		(*push_child)(struct node *, struct node *) ;
} ;

inline void node_print_linkage(struct node * node, FILE * file) {
	if (!node) return ;
	fprintf(file,
		"===[NODE INFO]===\n"
		"\t node:\t\t%p\n"
		"\t brother:\t%p\n"
		"\t sister:\t%p\n",
	node, node->brother, node->sister) ;
}

inline bool node_has_children(struct node * node) {
	return !!node->first_child ;
}

inline void node_print_child_linkage(struct node * node, FILE * file) {
	size_t counter ;
	struct node * child ;
	if (!node || !node_has_children(node)) return ;
	
	child = node->first_child ;
	for (counter = 0; counter < node->child_count; ++counter) {
		node_print_linkage(child, file) ;
		child = child->brother ;
	}
}

inline bool node_kill_child(struct node * parent, size_t child_index, size_t body_count_limit) {
	size_t counter = 0, body_count = 0 ;
	struct node ** pHead ;
	struct node * temp ;
	bool success_code = true ;

	printf("begin node_kill_child(parent=%p, child_index=%lu, body_count_limit=%lu)\n",
			parent, child_index, body_count_limit) ;

	if (body_count_limit < 1) return success_code ;
	VALIDATE_NODE("kill_child") ;
	if (parent->child_count < 1) success_code = false ;

	printf("pre loop\n") ;
	pHead = &parent->first_child ;
	while (*pHead
	&& body_count < body_count_limit
	&& counter < parent->child_count) {
		printf("kill loop #%lu\n", counter) ;
		if (counter >= child_index) {
			printf("killing a child\n") ;
			temp = (*pHead)->brother ;
			printf("freeing %p (temp = %p)\n", *pHead, temp) ;
			free (*pHead) ;
			*pHead = temp ;
			node_print_linkage(*pHead, stdout);
			temp->brother->sister = temp ;
			node_print_linkage(*pHead, stdout);
			++body_count ;
		}
		++counter ;
		pHead = &(*pHead)->brother ;
	}

	if (success_code) {
		parent->child_count -= body_count ;
	}

	return success_code ;
}

/* had to include a function like this */
inline bool node_kill_all_children(struct node * parent) {
	return node_kill_child(parent, 0, parent->child_count) ;
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
