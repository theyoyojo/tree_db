#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "udid.h"

/* Don't do anything on an invalid node that could be risky */
#define VALIDATE_NODE(msg) ({ \
		if (!parent->data) { \
			fprintf(stderr,"Invalid node: %s\n",msg) ; \
			return false ; \
		} \
	}) ; \


struct node ;

typedef union metadata {
	char 		info[8] ;
	long long	data ;
} metadata_t ;

typedef struct node_data_ops {
	void 		*(*get_bytes)(struct node *) ;
	size_t		(*get_length)(struct node *) ;
	bool		(*get_string)(struct node *, char * buf, size_t buflen) ;
	bool		(*set_data)(struct node *, void * data) ;
	void		(*free_data)(void *) ;
	int 		(*compare_data)(void * first, void * second) ;
} data_ops_t ;

/* Creation functions will be specified for each node specializaiton,
 * but they all must know how to kill themselves and reproduce
 */
struct node {
	udid_t 		udid ;
	void 		*data ;
	metadata_t 	metadata ;
	data_ops_t	data_ops ;

	struct node 	*first_child ;
	struct node 	*last_child ;
	struct node     *brother ;
	struct node     *sister ;
	struct node	*parent ;
	size_t 		child_count ;

	struct node     *(*create_child)(void * args) ;
} ;

void node_kill(struct node ** node) ;

bool node_has_children(struct node * node) ;
bool node_has_parent(struct node * node) ;

bool node_verify_child_count(struct node * parent) ;
bool node_verify_sibling_integrity(struct node * parent) ;

bool node_create_child(struct node * parent, void * args) ;
bool node_push_child(struct node * parent, struct node * child) ;

struct node * node_get_child_by_index(struct node * parent, size_t child_index) ;
size_t node_get_child_count(struct node * parent) ;

bool node_kill_child(struct node * parent, size_t child_index, size_t body_count_limit) ;
bool node_kill_all_children(struct node * parent) ;

void node_print_child_linkage(struct node * node, FILE * file) ;
void node_print_linkage(struct node * node, FILE * file) ;

#endif /* NODE_H */
