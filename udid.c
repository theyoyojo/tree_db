#include "udid.h"

#include <time.h>
#include <stdlib.h>

#include "MurmurHash3.h"

#define SEED_CONSTANT 0xdeadbeefU /* why not? */

/* udid: unique data id */

udid_t 	udid_calculate(void * bytes, size_t length){
	udid_t new ;

	MurmurHash3_x64_128(bytes, (int)length, SEED_CONSTANT, (void *)&new) ;
	
	return new ;
}

bool udid_compare(udid_t first, udid_t second) {
	return first.value == second.value ;
}

void udid_print_table(udid_t udid, FILE * file) {
	for (int i = 0; i < 16; ++i) {
		if (i % 4 == 0) fprintf(file, "%x:\t", i) ;
		fprintf(file,"%02hhx ", udid.bytes[i]) ;
		if (i % 4 == 3) fprintf(file, "\n") ;
	}
}

void udid_print_value(udid_t udid, FILE * file) {
	fprintf(file, "%llu + %llu * 2^8 \n", *(unsigned long long int *)&udid.bytes,
	 *(unsigned long long int *)&(udid.bytes[8])) ;
}
