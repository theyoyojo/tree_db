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

/* these are the operations of must expect to be able to perform on
 * a nodes data
 */
typedef struct node_data_ops {
	void 		*(*get_bytes)(struct node *) ;
	size_t		(*get_length)(struct node *) ;
	bool		(*get_string)(struct node *, char * buf, size_t buflen) ;
	bool		(*set_data)(struct node *, void * data) ;
	void		(*free_data)(void *) ;
	int 		(*compare_data)(void * first, void * second) ;
} data_ops_t ;

/* this is the core building block of the database
 *
 * creation functions will be specified for each node specializaiton,
 * but they all must know how to and reproduce. The used to need to
 * know how to kill themselves, but the do not anymore.
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

/* free a node and all associated memory */
void node_kill(struct node ** node) ;

/* return true if a node has more than zero children */
bool node_has_children(struct node * node) ;

/* return true if a node has a parent node (vs created by client call to create()) */
bool node_has_parent(struct node * node) ;

/* a data structure validity check that returns true when the node's internal count
 * of all child nodes is corroberated by behavior observed by the linked list structure
 * used to contain the child nodes
 */
bool node_verify_child_count(struct node * parent) ;

/* a data structure validity check that reutrns true when our three seperate counts
 * of the number of child nodes are equivelent, the two calculated by iteration
 * and the the internal count of the parent node
 */
bool node_verify_sibling_integrity(struct node * parent) ;

/* create a node and insert it into the child list of the parent
 * return true unless something went wrong
 */
bool node_create_child(struct node * parent, void * args) ;

/* insert a node into the child list of the parent
 * return true unless something went wrong
 */
bool node_push_child(struct node * parent, struct node * child) ;

/* remove a child node from a list and return it to the caller along
 * with responsibility for the eventual deallocation of its memory
 */
struct node * node_pop_child_by_index(struct node * parent, size_t index) ;

/* access the child list of a parent node as one would an array
 * and return a pointer to the requested node, or NULL if something went wrong
 */
struct node * node_get_child_by_index(struct node * parent, size_t child_index) ;

/* return the length of the parent's child node list */
size_t node_get_child_count(struct node * parent) ;

/* iterate through a parent's child node list, killing all after a certain index
 * until either all children have been killed or the body count limit has been
 * reached. If preserve children is true, the memory associated with the killed
 * children will not be free'd. This is useful if one wished to move a child node
 * to a different parent.
 * FIXME: this is only index based but I should have support for kill_child_by_udid as well
 */
bool node_kill_child(struct node * parent, size_t child_index, size_t body_count_limit, bool preserve_memory) ;

/* free all data associated with a parent's child node list and set all pointers to
 * that list to NULL
 */
bool node_kill_all_children(struct node * parent) ;

/* display the hex addresses of a node, it's brother, and it's sister */
void node_print_linkage(struct node * node, FILE * file) ;

/* call print_linkage() on all children of a node */
void node_print_child_linkage(struct node * node, FILE * file) ;

#endif /* NODE_H */
