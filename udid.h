#ifndef UDID_H
#define UDID_H

#include <stdbool.h>
#include <stdio.h>

#ifdef __GNUC__
typedef 	__int128 		int128_t ;
typedef 	unsigned __int128 	uint128_t ;

typedef union udid_t {
	uint128_t 	value ;
	unsigned char 	bytes[16] ;
} udid_t ;
#else
#error "GNU C required but not used"
#endif 


inline udid_t udid_get_null_constant(void) {
	return (udid_t)(uint128_t)0 ;
}

/* calculate the udid of some data */
udid_t udid_calculate(void * bytes, size_t length) ;

/* return true only if first and second are equal */
bool udid_compare(udid_t first, udid_t second) ;

/* print the hex value of udid in a nice table */
void udid_print_table(udid_t udid, FILE * file) ;

/* print the value of udid in decimal form */
void udid_print_value(udid_t udid, FILE * file) ;


#endif /* UDID_H */
