#include <iostream>
#include <climits>
#include "custom_types/ts.h"
#include "custom_types/state.h"
#include "get_delta_t.h"
#include "scheduler.h"
#include "pruning_constraints.h"




// check which jobs interfere lower priority jobs
void update_interferance_flags(state& s, const uint_fast8_t m, const uint_fast8_t* perm) {
    
    s.updatePendJobsNum();
    
    if (s.pendJobsNum > m)
        for (uint_fast8_t i = 0; i < m; i++)
            s.interferred[perm[i]] = true;
}





// Deadline check
bool deadline_miss(const state& s, const TS& ts, const bool verbose) {
    
    const uint_fast8_t N = s.n;
    
    if (s.d(N-1, ts.P[N-1], ts.D[N-1]) < s.c[N-1]) {
        if (verbose) {
            cout << "Failure state:" << endl;
            for (uint_fast8_t i = 0; i < N; i++) {
                cout << "c[" << (int)i << "]: " << (int)s.c[i] << " d[" << (int)i << "]: " << (int)s.d(N-1, ts.P[N-1], ts.D[N-1]) << " p[" << (int)i << "]" << (int)s.p[i] << endl;
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
uint_fast8_t algorithm_move(state& s, const TS& ts, const uint_fast8_t m, bool verbose) {

    uint_fast8_t N = ts.n;
    uint_fast8_t* perm = new uint_fast8_t [ts.n];

    sortTasksByPriorities(s, perm);
    update_interferance_flags(s, m, perm);

    uint_fast8_t dt = deltaT(s, m, perm);
    
    if (!condition_job_interference(s, m, dt, perm)) {
        // interf. cond. violated
        for (uint_fast8_t i = 0; i < m; i++) s.c[perm[i]] = max(s.c[perm[i]] - dt, 0);
        for (uint_fast8_t i = 0; i < N; i++) s.p[i] = max(s.p[i] - dt, 0); // ????????? to recheck
        if (deadline_miss(s, ts, verbose)) {delete [] perm; return -1;}
        else {
            //cout << "pruned by condition_job_interference(s, m, dt, perm)" << endl;
            delete [] perm;
            return 1; // no deadline miss, but interference cond. violated
        }
    } else {
        // interf. cond. holds
        const uint_fast8_t previousCk = s.c[N-1];
        for (uint_fast8_t i = 0; i < N; i++) s.jobCanBeReleasedBefore[i] = ((s.p[i] == 0)?true:false);
        
        //conditionC_cri_tau_i(s, ts, m, perm); // set .releaseAtEarliest flags
        
        for (uint_fast8_t i = 0; i < m; i++) s.c[perm[i]] = max(s.c[perm[i]] - dt, 0);
        for (uint_fast8_t i = 0; i < N; i++) s.p[i] = max(s.p[i] - dt, 0);
        for (uint_fast8_t i = 0; i < N; i++) s.timePassedFromLastRelease[i] = s.timePassedFromLastRelease[i] + dt;
        
        //if (s.tau2_releaseNextJobBefore > 0) s.tau2_releaseNextJobBefore -= dt;
        //if (s.tau3_releaseNextJobBefore > 0) s.tau3_releaseNextJobBefore -= dt;
        for (uint_fast8_t i = 0; i < ts.n; i++) {
            if (s.tauI_releaseNextJobBefore[i] > 0) s.tauI_releaseNextJobBefore[i] -= dt;
            // TO CHECK: should the computation of dt be changed? can be optimized?
        }
        
        if (deadline_miss(s, ts, verbose)) {delete [] perm; return -1;}
        
        for (uint_fast8_t i = 0; i < N; i++) s.prevState_processorAvailableForTau_i[i] = s.processorAvailableForTau_i[i];
        
        if ((previousCk > 0) && (s.c[N-1] == 0)) {
            //cout << "pruned: state is discarded, as analyzed job completes execution" << endl;
            delete [] perm;
            return 1; // state is discarded, as analyzed job completes execution
        }
    }

    delete [] perm;
    return 0;
}
