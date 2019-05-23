#ifndef DATA_TYPE_TEXT_H
#define DATA_TYPE_TEXT_H

#include "data_node.h"

const data_ops_t data_type_text_ops ;

/* data_type generic interface */

void * data_type_text_get_bytes(struct node * node) ;

size_t data_type_text_get_length(struct node * node) ;

bool data_type_text_get_string(struct node * node, char * buf, size_t buflen) ;

bool data_type_text_set_data(struct node * node, void * data, size_t size) ;

void data_type_text_free_data(void * data) ;

int data_type_text_compare(void * first, void * second) ;

/* data_type_text specific interface */

bool data_type_text_concatenate(struct node * append_to_me, struct node * append_me) ;

#endif /* DATA_TYPE_TEXT_H */
