#include <iostream>
#include <climits>
#include "custom_types/ts.h"
#include "custom_types/state.h"
#include "get_delta_t.h"
#include "scheduler.h"
#include <algorithm>
#include <math.h>
#include "response_time_bounds.h"




uint_fast8_t get_dt_resump(const state& s, const uint_fast8_t m) {

    uint_fast8_t* cs = new uint_fast8_t[s.n];
    
    // assumption: at least m higher priority jobs at state s
    uint_fast8_t n_hp = 0;
    for (uint_fast8_t i = 0; i < s.n-1; i++) {
        if (s.c[i] > 0) {
            cs[n_hp] = s.c[i];
            n_hp++;
        }
    }
    sort(cs, cs + n_hp);

    uint_fast8_t dtResump = cs[n_hp - m];
    delete [] cs;
    
    return dtResump;
}




uint_fast8_t get_dt_preempt(const state& s, const TS& ts, const uint_fast8_t i, const uint_fast8_t m) {

    unsigned short* ps = new unsigned short[20];
    uint_fast8_t dtPreempt;
    
    if (i <= m) dtPreempt = ts.C[i];
    else {
        uint_fast8_t n_hp_i = 0;
        for (uint_fast8_t l = 0; l < i; l++) if (s.c[l] > 0) n_hp_i++;
    
        if (n_hp_i >= m) dtPreempt = 0;
        else { // i > m && n_hp[i] < m   -> tau_i gets a processor at state s
            for (uint_fast8_t l = 0; l < i; l++) { if (s.p[l] > 0) ps[l] = s.p[l]; else ps[l] = 1; }
            sort(ps, ps + (i-1));

            dtPreempt = ps[m - n_hp_i - 1];
        }
    }
    
    delete [] ps;
    return dtPreempt;
}




/* Critical release instant for tau_i */


// Condition for a critical release instant of tau_i
// when processor is available for tau_i
// (the case when the next release of tau_i must occur only after tau_k is completed)
bool conditionA_cri_tau_i(const state& s, const TS& ts, const uint_fast8_t m) {
    
    if (s.pendJobsNum <= m) {
        uint_fast8_t N = s.n;
        
        if (s.c[N-1] > 0) {
            for (uint_fast8_t i = 0; i < N-1; i++) {
                if (s.c[i] == ts.C[i]) { // tau_i job starts execution (as the number of pending jobs <= m)
                    if (s.p[i] >= s.d(N-1, ts.P[N-1], ts.D[N-1]) - 1 ) {
                        // to check if it is possible to put upper bound on the response time
                        return false;
                    }
                }
            }
        } else {
            // the examined task has not released a job yet
            uint_fast8_t length = get_max_remaining_schedule_length(s, ts, m);
            for (uint_fast8_t i = 0; i < N-1; i++) {
                if (s.c[i] == ts.C[i]) { // tau_i job starts execution (as the number of pending jobs <= m)
                    if (s.p[i] >= length - 1 ) {
                        // to check if it is possible to put upper bound on the response time
                        return false;
                    }
                }
            }
        }
    }
    
    return true;
}






// check generalized interference condition on tau_k:
// task \tau_i must release a job, if that job would iterfere with a job of \tau_k for C_i time units
bool conditionB_cri_tau_i(const state& s, const TS& ts, const uint_fast8_t m) {
    
    if (s.c[s.n-1] > 0) {
        
        // check that at most one job is missing for an interference on tau_k

        if (s.pendJobsNum == m) { // to recheck if this condition is needed !!!
            
            for (uint_fast8_t i = 0; i < s.n-1; i++) {
                
                if (s.p[i] == 0) {
                    if (s.processorAvailableForTau_i[i]) {
                        
                        // assume that tau_i releases a job
                        s.c[i] = ts.C[i];
                        s.p[i] = ts.P[i];

                        uint_fast8_t dt_resump_k = get_dt_resump(s, m); // assumption: m+1 pending jobs
                        uint_fast8_t dt_preempt_i;
                        if (dt_resump_k >= ts.C[i]) { // include case with c_k
                            
                            dt_preempt_i = get_dt_preempt(s, ts, i, m); // assumption: m+1 pending jobs
                            if (dt_preempt_i >= ts.C[i]) return false; // pruning condition holds, state is pruned
                        }
                        
                        // remove the assumption that tau_i releases a job
                        s.c[i] = 0;
                        s.p[i] = 0;
                    } else {
                        // As s.processorAvailableForTau_i[i] == false, thus terminating iterations
                        return true;
                    }
                }
            }
        }
    }
    
    return true;
}




// improved condition for cri2
void conditionC_cri_tau_i(const state& s, const TS& ts, const uint_fast8_t m, const uint_fast8_t* perm) {
    
    /*if (s.pendJobsNum <= m) { // no lower priority job is interfered at this time instant
        for (uint_fast8_t i = 0; i < m; i++)
            if (s.c[perm[i]] == ts.C[perm[i]]) // job starts execution
                s.releaseAtEarliest[perm[i]] = true;
    }*/
    
    return;
}






bool condition_job_interference(const state& s, const uint_fast8_t m, const uint_fast8_t& dt, const uint_fast8_t* perm) {

    for (uint_fast8_t i = 0; i < m; i++)
        if ((s.c[perm[i]] > 0) && (s.c[perm[i]] <= dt))
            if (!s.interferred[perm[i]])
                return false;
    
    return true;
}








bool condition_cri_2(const state& s, const uint_fast8_t m, const uint_fast8_t i, const bool processorAvailableToTauI) {
    
    if ((i == s.n-1) && (processorAvailableToTauI)) return false; // assumption: tau_n can release a job only once
    else if (i >= m) {
        if ((s.jobCanBeReleasedBefore[i]) && (!s.prevState_processorAvailableForTau_i[i])) {
            return false;
        }
    }
    
    return true;
}







// Necessary condition of interference at the last execution slot of a job, with a lower priority job
bool condition_of_interference_at_job_completion(const state& s, const uint_fast8_t m){
    
    bool conditionOnInterferenceAtCompletionHolds = true;
    
    if (s.pendJobsNum <= m) {
        for (uint_fast8_t j = 0; j < s.n-1; j++) {
            if (s.c[j] == 1) { // job will complete execution by the next time instant
                if (s.jobCanBeReleasedBefore[j]) {
                    // job could be released before
                    // thus, no need to consider the current execution scenario
                    conditionOnInterferenceAtCompletionHolds = false;
                    break;
                }
            }
        }
    }
    
    return conditionOnInterferenceAtCompletionHolds;
}












// check the condition for HP jobs releases:
// the scenario when each higher priority task, except tau_n, can release a job,
// but none of them does, can be discarded
bool condition_for_releases_of_hp_jobs(const state& s){
    
    /*const uint_fast8_t m = 3;
    
    if (s.c[s.tsLocal.n-1] == 0) return true;
    else {
    
        bool jobJustReleased = false;
    
        for (uint_fast8_t i = 0; i < s.tsLocal.n-1; i++) {
            if ((s.p[i] > 0) && (s.p[i] < s.tsLocal.P[i]))
                return true;
        
            if (s.p[i] == s.tsLocal.P[i]) jobJustReleased = true;
        }
        
        if (!jobJustReleased) return true;
        
        if ((jobJustReleased) && (s.pendJobsNum < m)) {
            cout << "==================== condition works !!!! =====================================" << endl;
            return false;
        }
    }*/
    
    if (s.c[s.n-1] > 0) {
        for (uint_fast8_t i = 0; i < s.n-1; i++)
            if (s.p[i] > 0) return true;
        
        return false;
    } else return true;
    
    return true;
}






void condition_on_next_release_instants(state& s, const TS& ts) {
    
    for (uint_fast8_t i = 0; i < ts.n; i++) {
        if (s.tauI_jobJustCompleted[i]) { // to update the condition
            
            // tau_i has just completed execution;
            // checking, if any HP job starts execution
            for (int j = i-1; j >= 0; j--) {
                if (s.p[j] == ts.P[j]) {
                    // tau_j has released a job at the completion of tau_i
                    if (s.tauI_releaseNextJobBefore[i] == -1)
                        s.tauI_releaseNextJobBefore[i] = ts.C[j] + ts.P[i] - 1;
                    else
                        s.tauI_releaseNextJobBefore[i] = min((int)s.tauI_releaseNextJobBefore[i], (int)ts.C[j] + ts.P[i] - 1);
                    //break;
                }
            }
            
        }
    }
}










/* Necessary unschedulability condition of Baruah 2009 */





// returns true, if necessary condition holds
bool condition_necessary_unsched(const state& s, const TS& ts, const uint_fast8_t m){
    
    uint_fast8_t Iub = 0;
    uint_fast8_t N = s.n;
    
    if (s.c[s.n-1] > 0) {
        // an examined task has released its job
        Iub = get_Iub_on_tau_n(s, ts, m);
        if (s.d(N-1, ts.P[N-1], ts.D[N-1]) - Iub >= s.c[N-1])
            return false;
        
    } else {
        // an examined task has not released its job yet
        Iub = get_Iub_on_tau_n(s, ts, m);
        if (ts.D[N-1] - Iub >= ts.C[N-1]) {
            return false;
        }
    }
    
    return true;
}




bool check_adversary_pruning_conditions(state& s, const TS& ts, const unsigned short m) {
    
    s.updateLockedJobsNum();
    s.updatePendJobsNum();
    
    if (!condition_necessary_unsched(s, ts, m)) return false;
    if (!condition_of_interference_at_job_completion(s, m)) return false;
    if (!conditionA_cri_tau_i(s, ts, m)) return false;
    if (!conditionB_cri_tau_i(s, ts, m)) return false;
    if (!condition_for_releases_of_hp_jobs(s)) return false;
    condition_on_next_release_instants(s, ts);
    // job interf. cond. -- checked at the alg. move
    
    return true;
}

