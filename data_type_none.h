#ifndef DATA_TYPE_NONE_H
#define DATA_TYPE_NONE_H
#include "data_node.h"
#include <string.h>

typedef unsigned long long int none_t ;

creation_arg_t data_type_none_get_none_args(void) ;
data_ops_t data_type_none_get_data_type_none_ops(void) ;

const none_t CONST_NONE ;

/* data manipulaton functons */
void * data_type_none_get_bytes(struct node * node) ;

size_t data_type_none_get_length(struct node * node) ;

bool data_type_none_get_string(struct node * node, char * buf, size_t buflen) ;

char * data_type_none_get_string_bytes(void) ;

size_t data_type_none_get_string_length(void) ;

bool data_type_none_set(struct node * node, void * data, size_t size) ;

void data_type_none_free(void * data) ;

int data_type_none_compare(void * first, void * second) ;

bool data_type_none_swap(void * first, void * second) ;

#endif /* DATA_TYPE_NONE_H */
