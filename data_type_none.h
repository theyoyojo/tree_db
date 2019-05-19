#include "data_node.h"
#include <string.h>

const char data_type_none_string[] = "[NONE]" ;

const unsigned long long int data_type_none_bytes = 0 ;

const size_t data_type_none_length = sizeof(unsigned long long int) ;

void * data_type_none_get_bytes(struct node * node) {
	(void)node ;
	return (void *)&data_type_none_length ;
}

size_t data_type_none_get_length(struct node * node) {
	(void)node ;
	return data_type_none_length ;
}

bool data_type_none_get_string(struct node * node, char * buf, size_t buflen) {
	(void)node ;
	strncpy(buf, data_type_none_string, buflen) ;
	return strcmp(buf, data_type_none_string) == 0 ;
}

bool data_type_none_set_data(struct node * node, void * data) {
	/* this data type is immutable */
	(void)node, (void)data ;
	return false ;
}

void data_type_none_free_data(void * data) {
	/* there is nothing to free for this type */
	(void)data ;
	return ;
}

const data_ops_t data_type_none_ops = (data_ops_t) {
	.get_bytes = data_type_none_get_bytes,
	.get_length = data_type_none_get_length,
	.get_string = data_type_none_get_string,
	.set_data = data_type_none_set_data,
	.free_data = data_type_none_free_data,
} ;

