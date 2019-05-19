#include "data_node.h"
#include <string.h>

typedef unsigned long long int none_t ;

/* constants */
const creation_arg_t NONE_ARGS ;
const data_ops_t data_type_none_ops ;

const none_t CONST_NONE ;

/* data manipulaton functons */
void * data_type_none_get_bytes(struct node * node) ;

size_t data_type_none_get_length(struct node * node) ;

bool data_type_none_get_string(struct node * node, char * buf, size_t buflen) ;

char * data_type_none_get_string_ptr(void) ;
size_t data_type_none_get_string_length(void) ;

bool data_type_none_set_data(struct node * node, void * data) ;

void data_type_none_free_data(void * data) ;

bool data_type_none_compare(void * first, void * second) ;
