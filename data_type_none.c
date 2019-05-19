#include "data_type_none.h"

const creation_arg_t NONE_ARGS = (creation_arg_t){
	.metadata.data = 0,
	.data = 0,
} ;

const none_t CONST_NONE = 0 ;


const char data_type_none_string[] = "[NONE]" ;

const none_t data_type_none_bytes = 0 ;

const size_t data_type_none_length = sizeof(none_t) ;

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
	.get_bytes = 	data_type_none_get_bytes,
	.get_length = 	data_type_none_get_length,
	.get_string = 	data_type_none_get_string,
	.set_data = 	data_type_none_set_data,
	.free_data = 	data_type_none_free_data,
	.compare_data = data_type_none_compare,
} ;

char * data_type_none_get_string_ptr(void) {
	return (char *)data_type_none_string ;
}

size_t data_type_none_get_string_length(void) {
	return sizeof(data_type_none_string) ;
}

/* this function should always return true */
bool data_type_none_compare(void * first, void * second) {
	return *(none_t *)first == *(none_t *)second ;
}
