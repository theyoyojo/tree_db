#ifndef DID_H
#define DID_H

#include <stdbool.h>

#ifdef __GNUC__
typedef unsigned __int128 udid_t ;
#else
#error "GNU C required but not used"
#endif 

inline udid_t udid_get_null_constant(void) {
	return 0 ;
}

udid_t 	udid_generate	() ;

/* works like strcmp */
int	udid_compare	(udid_t first, udid_t second) ;


#endif /* DID_H */
