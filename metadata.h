#ifndef METADATA_H
#define METADATA_H

#include <stdbool.h>

/* this is where the type system is defined */

typedef union metadata {
	char 		info[8] ;
	long long	data ;
} metadata_t ;

bool metadata_is_same(metadata_t first, metadata_t second) ;

/* TODO
 * what will go in this section?
 * casting?
 * type ID or constants?
 */

typedef enum data_type {
	DATA_TYPE_NONE,
	DATA_TYPE_TEXT,
	DATA_TYPE_NUMBER,
	DATA_TYPE_TIME,
	DATA_TYPE_REFERENCE
} data_type_t ;

void metadata_set_data_type(metadata_t * metadata, data_type_t data_type) ;

data_type_t metadata_get_data_type(metadata_t metadata) ;

/* the first byte of the metadata will store a data type specified by enum data_type
 * 
 * for text: the next four bytes will store the size of the character array
 */

#endif /* METADATA_H */
