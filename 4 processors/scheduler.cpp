#include <iostream>
#include "custom_types/ts.h"
#include "custom_types/state.h"




// Global FP (priority ordering given by indices, index 1 == highest priority)
bool prefer(const state& s, uint_fast8_t i, uint_fast8_t k) {
    if(s.c[i]==0 && s.c[k]==0) return (i < k); 		// no active job from i or k -- use default ordering
    if(s.c[i]==0 || s.c[k]==0) return s.c[i] > 0; 	// only 1 active -- prefer that one
    return (i < k); 								// FP rule (no ties are possible)
}



void sortTasksByPriorities(const state& s, uint_fast8_t* perm) {
    
    for (uint_fast8_t i = 0; i < s.n; i++) perm[i] = i;
    
    for (uint_fast8_t i = 0; i < s.n; i++)
        for (uint_fast8_t k = i+1; k < s.n; k++)
            if (!prefer(s, perm[i], perm[k]))
                swap(perm[i], perm[k]);
}
