#include <iostream>
#include <climits>
#include "custom_types/ts.h"
#include "custom_types/state.h"
#include "get_delta_t.h"
#include "scheduler.h"
#include "pruning_constraints.h"




// check which jobs interfere lower priority jobs
void update_interferance_flags(state& s, const unsigned short int m, const unsigned short* perm) {
    if (s.pendJobsNum > m)
        for (int i = 0; i < m; i++)
            s.interferred[perm[i]] = true;
}





// Deadline check
bool deadline_miss(const state& s, const bool verbose) {
    
    const unsigned short N = s.tsLocal.n;
    
    if (s.d(N-1) < s.c[N-1]) {
        if (verbose) {
            cout << "Failure state:" << endl;
            for (int i = 0; i < N; i++) {
                cout << "c[" << i << "]: " << s.c[i] << " t[" << i << "]: " << s.t[i] << endl;
            }
        }
        return true;
    }
    
    return false;
}








// return codes:
// -1 - deadline miss
// 0 - continue traversal of successors
// 1 - schedule can be discarded
short int algorithm_move(state& s, const unsigned short int N, const unsigned short int m, bool verbose) {

    if (!conditionA_cri_tau_i(s, m)) return 1;
    if (!conditionB_cri_tau_i(s, m)) return 1;

    unsigned short* perm = new unsigned short [N];
    sortTasksByPriorities(s, N, perm);
    update_interferance_flags(s, m, perm);

    int dt = deltaT(s, N, m, perm);
    
    if (!condition_job_interference(s, m, dt, perm)) {
        // interf. cond. violated
        for (int i = 0; i < m; i++) s.c[perm[i]] = max(s.c[perm[i]] - dt, 0);
        for (int i = 0; i < N; i++) s.t[i] = max(s.t[i] - dt, 0);
        if (deadline_miss(s, verbose)) return -1;
        else return 1; // no deadline miss, but interference cond. violated
    } else {
        // interf. cond. holds
        const unsigned short previousCk = s.c[N-1];
        for (unsigned short i = 0; i < N; i++) s.jobCanBeReleasedBefore[i] = ((s.t[i] == 0)?true:false);
        
        conditionC_cri_tau_i(s, m, perm); // set .releaseAtEarliest flags
        
        for (int i = 0; i < m; i++) s.c[perm[i]] = max(s.c[perm[i]] - dt, 0);
        for (int i = 0; i < N; i++) s.t[i] = max(s.t[i] - dt, 0);
        if (deadline_miss(s, verbose)) return -1;
        
        for (unsigned short i = 0; i < N; i++) s.prevState_processorAvailableForTau_i[i] = s.processorAvailableForTau_i[i];
        
        if ((previousCk > 0) && (s.c[N-1] == 0)) return 1; // state is discarded, as analyzed job completes execution
    }
    
    return 0;
}
