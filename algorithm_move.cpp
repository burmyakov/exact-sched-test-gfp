#include <iostream>
#include <climits>
#include "custom_types/ts.h"
#include "custom_types/state.h"
#include "get_delta_t.h"
#include "scheduler.h"
#include "pruning_constraints.h"
#include <cinttypes>




// check which jobs interfere lower priority jobs
void update_interferance_flags(state& s, const uint8_t m, const uint8_t* perm) {
    if (s.pendJobsNum > m)
        for (int i = 0; i < m; i++)
            s.interferred[perm[i]] = true;
}





// Deadline check
bool deadline_miss(const state& s, const bool verbose) {
    
    const uint8_t N = s.tsLocal.n;
    
    if (s.d(N-1) < s.c[N-1]) {
        if (verbose) {
            cout << "Failure state:" << endl;
            for (int i = 0; i < N; i++) {
                cout << "c[" << i << "]: " << s.c[i] << " d[" << i << "]: " << s.d(i) << " p[" << i << "]" << s.p[i] << endl;
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
int8_t algorithm_move(state& s, const uint8_t N, const uint8_t m, bool verbose) {

    if (!conditionA_cri_tau_i(s, m)) return 1;
    if (!conditionB_cri_tau_i(s, m)) return 1;

    uint8_t* perm = new uint8_t [N];
    //unsigned short* perm = new unsigned short [N];
    sortTasksByPriorities(s, N, perm);
    update_interferance_flags(s, m, perm);

    //uint8_t dt = deltaT(s, N, m, perm);
    int dt = deltaT(s, N, m, perm);
    
    if (!condition_job_interference(s, m, dt, perm)) {
        // interf. cond. violated
        for (uint8_t i = 0; i < m; i++) s.c[perm[i]] = max(s.c[perm[i]] - dt, 0);
        for (uint8_t i = 0; i < N; i++) s.p[i] = max(s.p[i] - dt, 0); // ????????? to recheck
        if (deadline_miss(s, verbose)) return -1;
        else return 1; // no deadline miss, but interference cond. violated
    } else {
        // interf. cond. holds
        const uint8_t previousCk = s.c[N-1];
        for (uint8_t i = 0; i < N; i++) s.jobCanBeReleasedBefore[i] = ((s.p[i] == 0)?true:false);
        
        conditionC_cri_tau_i(s, m, perm); // set .releaseAtEarliest flags
        
        for (uint8_t i = 0; i < m; i++) s.c[perm[i]] = max(s.c[perm[i]] - dt, 0);
        for (uint8_t i = 0; i < N; i++) s.p[i] = max(s.p[i] - dt, 0);
        if (deadline_miss(s, verbose)) return -1;
        
        for (uint8_t i = 0; i < N; i++) s.prevState_processorAvailableForTau_i[i] = s.processorAvailableForTau_i[i];
        
        if ((previousCk > 0) && (s.c[N-1] == 0)) return 1; // state is discarded, as analyzed job completes execution
    }
    
    return 0;
}
