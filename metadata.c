#include "metadata.h"

bool metadata_is_same(metadata_t first, metadata_t second) {
	return first.data == second.data ;
}

void metadata_set_data_type(metadata_t * metadata, data_type_t data_type) {
	if (metadata) {
		metadata->info[0] = (char)data_type ;
	}
}

data_type_t metadata_get_data_type(metadata_t metadata) {
	return (data_type_t)metadata.info[0] ;
}
