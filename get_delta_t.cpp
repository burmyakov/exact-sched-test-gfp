#include <iostream>
#include <climits>
#include "custom_types/ts.h"
#include "custom_types/state.h"




unsigned short get_dt_to_next_release(const state& s, const unsigned short int N, const unsigned short m){
    
    int dtToNextRelease = max(1, (int)(s.t[0]));
    
    for (unsigned short i = 1; i < m; i++) {
        dtToNextRelease = min(max(1, (int)(s.t[i])), dtToNextRelease);
        if (dtToNextRelease == 1) return dtToNextRelease;
    }
    
    // !!!! To refine the conditions below !!!!
    // The condition below follows from the critical release instant for tau_i
    // If tau_i, with i > m, releases a job at time $t$, then
    // a processor is available for tau_i at time $t-1$
    for (unsigned short i = m; i < N-1; i++) {
        //if ((s.processorAvailableForTau_i[i]) || (s.releaseAtEarliest[i])) {
        if ((!s.processorAvailableForTau_i[i]) && (s.t[i] == 0)) continue;
        else {
            dtToNextRelease = min(max(1, (int)(s.t[i])), dtToNextRelease);
            if (dtToNextRelease == 1) return dtToNextRelease;
        }
    }

    // To improve !!!!
    // The condition below follows from Davis and Burns 2011:
    // if tau_k releases its job at time $t$,
    // then at time $t-1$ there should be less than $m$ pending jobs
    if (s.pendJobsNum < m)
        dtToNextRelease = min(max(1, (int)(s.t[N-1])), dtToNextRelease);
    
    return dtToNextRelease;
}



unsigned short get_dt_to_next_completion(const state& s, const unsigned short int m, const unsigned short *perm){

    int dtToNextCompletion = 10000;
    for (unsigned short i = 0; i < m; i++) // what to do with m ????
        if (s.c[perm[i]] > 0)
            dtToNextCompletion = min(dtToNextCompletion, (int)(s.c[perm[i]]));
        else break; // To recheck if I should break here !!
    
    return dtToNextCompletion;
}




unsigned short deltaT(const state& s, const unsigned short int N, const unsigned short int m, const unsigned short *perm) {
    
    unsigned short dtToNextRelease = get_dt_to_next_release(s, N, m);
    //unsigned short dtToNextCompletion = get_dt_to_next_completion(s, m, perm);
    //return min(dtToNextRelease, dtToNextCompletion);*/
    
    if (dtToNextRelease == 1) return dtToNextRelease;
    //if (dtToNextCompletion == 1) return dtToNextCompletion;
    else {
        unsigned short dtToNextCompletion = get_dt_to_next_completion(s, m, perm);
        //unsigned short dtToNextRelease = get_dt_to_next_release(s, N, m);
        return min(dtToNextRelease, dtToNextCompletion);
    }
}
