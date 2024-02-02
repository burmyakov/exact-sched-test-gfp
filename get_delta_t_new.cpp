#include <iostream>
#include <climits>
#include "custom_types/ts.h"
#include "custom_types/state.h"
#include <cinttypes>




uint8_t get_dt_to_next_release(const state& s, const uint8_t N, const uint8_t m){
    
    uint8_t dtToNextRelease = max((uint8_t)1, (uint8_t)(s.p[0]));
    
    for (uint8_t i = 1; i < m; i++) {
        dtToNextRelease = min(max((uint8_t)1, (uint8_t)(s.p[i])), dtToNextRelease);
        if (dtToNextRelease == 1) return dtToNextRelease;
    }
    
    // !!!! To refine the conditions below !!!!
    // The condition below follows from the critical release instant for tau_i
    // If tau_i, with i > m, releases a job at time $t$, then
    // a processor is available for tau_i at time $t-1$
    for (uint8_t i = m; i < N-1; i++) {
        if ((!s.processorAvailableForTau_i[i]) && (s.p[i] == 0)) continue;
        else {
            dtToNextRelease = min(max((uint8_t)1, (uint8_t)(s.p[i])), dtToNextRelease);
            if (dtToNextRelease == 1) return dtToNextRelease;
        }
    }

    // To improve !!!!
    // The condition below follows from Davis and Burns 2011:
    // if tau_k releases its job at time $t$,
    // then at time $t-1$ there should be less than $m$ pending jobs
    if (s.pendJobsNum < m)
        dtToNextRelease = min(max((uint8_t)1, (uint8_t)(s.p[N-1])), dtToNextRelease);
    
    return dtToNextRelease;
}



uint8_t get_dt_to_next_completion(const state& s, const uint8_t m, const uint8_t *perm){

    uint8_t dtToNextCompletion = 255;
    for (uint8_t i = 0; i < m; i++) // what to do with m ????
        if (s.c[perm[i]] > 0)
            dtToNextCompletion = min(dtToNextCompletion, (uint8_t)(s.c[perm[i]]));
        else break; // To recheck if I should break here !!
    
    return dtToNextCompletion;
}




uint8_t deltaT(const state& s, const uint8_t N, const uint8_t m, const uint8_t *perm) {
    
    uint8_t dtToNextRelease = get_dt_to_next_release(s, N, m);
    //unsigned short dtToNextCompletion = get_dt_to_next_completion(s, m, perm);
    //return min(dtToNextRelease, dtToNextCompletion);*/
    
    if (dtToNextRelease == 1) return dtToNextRelease;
    //if (dtToNextCompletion == 1) return dtToNextCompletion;
    else {
        uint8_t dtToNextCompletion = get_dt_to_next_completion(s, m, perm);
        //unsigned short dtToNextRelease = get_dt_to_next_release(s, N, m);
        return min(dtToNextRelease, dtToNextCompletion);
    }
}
