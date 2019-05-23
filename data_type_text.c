#include "data_type_text.h"

const data_ops_t data_type_text_ops = (data_ops_t) {
	.get_bytes = 	data_type_text_get_bytes,
	.get_length = 	data_type_text_get_length,
	.get_string = 	data_type_text_get_string,
	.set_data = 	data_type_text_set_data,
	.free_data = 	data_type_text_free_data,
	.compare_data = data_type_text_compare,
} ;

/* data_type generic interface */

void * data_type_text_get_bytes(struct node * node) {
	return node->data ;
}

size_t data_type_text_get_length(struct node * node) {
	// TODO size is determined by metadata
}

bool data_type_text_get_string(struct node * node, char * buf, size_t buflen) {
	// TODO stub
	return false ;
}

bool data_type_text_set_data(struct node * node, void * data, size_t size) {
	// TODO stub
	return false ;
}

void data_type_text_free_data(void * data) {
	// TODO stub
	return ;
}

int data_type_text_compare(void * first, void * second) {
	// TODO stub
	return 0 ;
}

/* data_type_text specific interface */

bool data_type_text_concatenate(struct node * append_to_me, struct node * append_me) {
	// TODO stub
	return false ;
}
