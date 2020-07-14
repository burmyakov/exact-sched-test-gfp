#include <iostream>
#include <climits>
#include "custom_types/ts.h"
#include "custom_types/state.h"
#include "get_delta_t.h"
#include "scheduler.h"
#include <algorithm>



//unsigned short* n_hp = new unsigned short[20];
unsigned short* cs = new unsigned short[20];
unsigned short* ps = new unsigned short[20];


unsigned short get_dt_resump(const state& s, const unsigned short m) {

    // assumption: at least m higher priority jobs at state s
    unsigned short n_hp = 0;
    for (unsigned short i = 0; i < s.tsLocal.n-1; i++) {
        if (s.c[i] > 0) {
            cs[n_hp] = s.c[i];
            n_hp++;
        }
    }
    sort(cs, cs + n_hp);
    
    //cout << "cs: ";
    //for (unsigned short i = 0; i < s.tsLocal.n; i++) cout << cs[i] << ", ";
    //cout << endl;
    
    /*unsigned short n_hp_k = 0;
    for (unsigned short i = 0; i < s.tsLocal.n-1; i++)
        if (s.c[i] > 0) n_hp_k++;
    
    if (n_hp_k != j) cout << "ERROR ERROR" << endl;*/
    
    //cout << "n_hp_k: " << n_hp_k << endl;
    
    //unsigned short dt_resump = cs[n_hp - m];
    /*unsigned short i = 1;
    while (dt_resump == 0) {
        dt_resump = cs[n_hp_k - m + i];
        i++;
    }*/
    
    //cout << "value to return: " << dt_resump << endl;

    return cs[n_hp - m];
}




unsigned short get_dt_preempt(const state& s, const unsigned short i, const unsigned short m) {

    if (i <= m) return s.tsLocal.C[i];
    
    unsigned short n_hp_i = 0;
    for (unsigned short l = 0; l < i; l++)
        if (s.c[l] > 0) n_hp_i++;
    
    if (n_hp_i >= m) return 0;
    else { // i > m && n_hp[i] < m   -> tau_i gets a processor at state s
        for (unsigned short l = 0; l < i; l++) { if (s.p[l] > 0) ps[l] = s.p[l]; else ps[l] = 1; }
        sort(ps, ps + (i-1));

        return ps[m - n_hp_i - 1];
    }
    
    //return 0;
}



/* Critical release instant for tau_i */


// Condition for a critical release instant of tau_i
// when processor is available for tau_i
// (the case when the next release of tau_i must occur only after tau_k is completed)
bool conditionA_cri_tau_i(const state& s, const unsigned short m) {
    
    unsigned short N = s.tsLocal.n;
    
    if (s.c[N-1] > 0) {
        if (s.pendJobsNum <= m) {
            for (unsigned short i = 0; i < N-1; i++) {
                if (s.c[i] == s.tsLocal.C[i]) { // tau_i job starts execution
                    if (s.processorAvailableForTau_i[i]) {
                        if (s.p[i] >= s.p[N-1]) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    
    return true;
}






// check generalized interference condition on tau_k:
// task \tau_i must release a job, if that job would iterfere with a job of \tau_k for C_i time units
bool conditionB_cri_tau_i(const state& s, const unsigned short m) {
    
    unsigned short N = s.tsLocal.n;
    
    if (s.c[N-1] > 0) {
        
        //unsigned short* perm2 = new unsigned short[N];
        //int dt2;
        
        // check that at most one job is missing for an interference on tau_k
        
        if (s.pendJobsNum == m) { // to recheck if this condition is needed !!!
            
            for (unsigned short i = 0; i < N-1; i++) {
                
                // update n_hp_i
                //if (i == 0) n_hp[i] = 0;
                //else {n_hp[i] = n_hp[i-1]; if (s.c[i-1] > 0) n_hp[i]++;}
                
                if (s.p[i] == 0) {
                    if (s.processorAvailableForTau_i[i]) {
                        
                        // assume that tau_i releases a job
                        s.c[i] = s.tsLocal.C[i];
                        s.p[i] = s.tsLocal.P[i];
                        
                        // compute dt for the next scheduling interval
                        //sortTasksByPriorities(s, N, perm2);
                        //dt2 = deltaT(s, N, m, perm2);
                        
                        unsigned short dt_resump_k = get_dt_resump(s, m); // assumption: m+1 pending jobs
                        unsigned short dt_preempt_i;
                        if (dt_resump_k >= s.tsLocal.C[i]) { // include case with c_k
                            
                            dt_preempt_i = get_dt_preempt(s, i, m); // assumption: m+1 pending jobs
                            if (dt_preempt_i >= s.tsLocal.C[i]) return false; // pruning condition holds, state is pruned
                        }
                        
                        /*if (dt2 == s.tsLocal.C[i]) {
                            cout << "ERROR" << endl;
                            cout << "dt2: " << dt2 << endl;
                            cout << "dt_resump: " << dt_resump_k << endl;
                            cout << "dt_preemp: " << dt_preempt_i << endl;
                            cout << "i: " << i << endl;
                            s.printCmpct();
                            abort();
                        }*/
                        
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
void conditionC_cri_tau_i(const state& s, const unsigned short m, const unsigned short* perm) {
    
    /*if (s.pendJobsNum <= m) { // no lower priority job is interfered
        for (unsigned short i = 0; i < m; i++)
            if (s.c[perm[i]] == (s.tsLocal).C[perm[i]]) // job starts execution
                s.releaseAtEarliest[perm[i]] = true;
    }*/
    
    return;
}






bool condition_job_interference(const state& s, const unsigned short m, const int& dt, const unsigned short* perm) {

    for (unsigned short i = 0; i < m; i++)
        if ((s.c[perm[i]] > 0) && (s.c[perm[i]] <= dt))
            if (!s.interferred[perm[i]])
                return false;
    
    return true;
}








bool condition_cri_2(const state& s, const unsigned short m, const unsigned short i, const bool processorAvailableToTauI) {
    
    if ((i == s.tsLocal.n-1) && (processorAvailableToTauI)) return false;
    else if ((i >= m) && (!processorAvailableToTauI)) {
        if ((s.jobCanBeReleasedBefore[i]) && (!s.prevState_processorAvailableForTau_i[i])) {
            return false;
        }
    }
    
    return true;
}












// check the condition for HP jobs releases:
// the scenario when each higher priority task, except tau_n, can release a job,
// but none of them do, can be discarded
bool condition_for_releases_of_hp_jobs(const state& s){
    
    if (s.c[s.tsLocal.n-1] > 0) {
        for (int i = 0; i < s.tsLocal.n-1; i++)
            if (s.p[i] > 0) return true;
        
        return false;
    } else return true;
}











/* Necessary unschedulability condition of Baruah 2009 */

float get_Iub(const state& s, const unsigned short m) {
    
    int W = 0;
    const unsigned short N = s.tsLocal.n;
    const int t = s.d(N-1);
    
    for (int i = 0; i < N-1; i++) {
        W += s.c[i] + (max(0, t - max(0, (int)(s.p[i])))/s.tsLocal.P[i])*s.tsLocal.C[i] + min((int)(s.tsLocal.C[i]), (max(0, t - max(0, (int)(s.p[i]))) % s.tsLocal.P[i]));
    }
    
    return W/m;
}


// returns true, if necessary condition holds
bool condition_necessary_unsched(const state& s, const unsigned short m){
    
    if (s.c[s.tsLocal.n-1] > 0) {
        int N = s.tsLocal.n;
        
        if (s.c[N-1] > 0) {
            float Iub = get_Iub(s, m);
            if (s.d(N-1) - Iub >= s.c[N-1]) return false;
        }
    }
    
    return true;
}
