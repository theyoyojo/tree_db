#include "udid.h"
#include "node.h"

#include <time.h>
#include <stdlib.h>

#define SRAND_CONSTANT 0xdeadbeefU /* why not? */

/* udid: unique data id */
static bool first_udid = true ;

udid_t udid_calculate(struct node * node) {
	udid_t new ;
	int key ;
	
	if (first_udid) {
		srand(SRAND_CONSTANT) ;
		first_udid = false ;
	}

	key = rand() ;

	(void)node ;
	//MurmurHash3_x64_128(node->data_ops.
	
	new = 0 ;	
	return new ;
}

int udid_compare(udid_t first, udid_t second) {
	// TODO
	(void)first, (void)second ;
	return true ;
}
