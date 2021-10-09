#include <iostream>
#include <climits>
#include <vector>
#include "custom_types/ts.h"
#include "custom_types/state.h"
#include "get_delta_t.h"
#include "scheduler.h"
#include "pruning_constraints.h"


using namespace std;



bool is_processor_available_to_tau_i(const state& s, const uint_fast8_t i, const uint_fast8_t m) {
    
    uint_fast8_t hpJobsNum = 0;
    
    for (uint_fast8_t indx = 0; indx < i; indx++) {
        if (s.c[indx] > 0) {
            hpJobsNum++;
            if (hpJobsNum == m) return false;
        }
    }

    return true;
}









// Successors are not sorted
void generate_successors(const TS& ts, state& s, const uint_fast8_t m, vector<state>* successors, uint_fast16_t& successorsNum) {
    
    uint_fast16_t curSuccessorsNum;
    
    
    // Generate successor states
    (*successors)[0] = s;
    successorsNum = 1;

    for (uint_fast8_t i = 0; i < ts.n; i++) {
        
        for (uint_fast16_t successorItr = 0; successorItr < successorsNum; successorItr++) {
            (*successors)[successorItr].processorAvailableForTau_i[i] = is_processor_available_to_tau_i((*successors)[successorItr], i, m);
        }
        
        if (s.p[i] == 0) {
            
            // Davis and Burns 2011 condition A for release of tau_k:
            // if tau_k releases a job at time t, then at least one processor is idle at time t-1, or t = 0
            if ((i == (ts.n-1)) && (!s.prevState_processorAvailableForTau_i[i])) continue;

            curSuccessorsNum = successorsNum;
            for (uint_fast16_t successorItr = 0; successorItr < curSuccessorsNum; successorItr++) {
                
                // Davis and Burns 2011 condition B for tau_k and any tau_i
                // Check if it is necessary to release a job for tau_i at this state
                if (!condition_cri_2(s, m, i, (*successors)[successorItr].processorAvailableForTau_i[i])) {
                    continue;
                }

                /*if (s.releaseAtEarliest[i]) {
                    
                    // Release of a job, satisfying the constraint of the earliest release:
                    // the preceeding job did not interfere with a lower-priority job, when first getting a processor
                    (*successors)[successorItr].c[i] = ts.C[i];
                    (*successors)[successorItr].p[i] = ts.P[i];
                    (*successors)[successorItr].timePassedFromLastRelease[i] = 0;
                    (*successors)[successorItr].tauI_releaseNextJobBefore[i] = -1;
                    (*successors)[successorItr].firstJobReleased[i] = true;
                    (*successors)[successorItr].releaseAtEarliest[i] = false;
                    (*successors)[successorItr].releasedAtEarliest[i] = true;
                    (*successors)[successorItr].interferred[i] = true; // due to forcing an early release
                
                } else if (s.tauI_releaseNextJobBefore[i] == 0) {
                    
                    (*successors)[successorItr].c[i] = ts.C[i];
                    (*successors)[successorItr].p[i] = ts.P[i];
                    (*successors)[successorItr].timePassedFromLastRelease[i] = 0;
                    (*successors)[successorItr].tauI_releaseNextJobBefore[i] = -1;
                    (*successors)[successorItr].firstJobReleased[i] = true;
                    (*successors)[successorItr].releaseAtEarliest[i] = false;
                 (*successors)[successorItr].releasedAtEarliest[i] = true;
                    (*successors)[successorItr].interferred[i] = true; // due to forcing an early release
                    
                } else
                if (!s.firstJobReleased[i] && (s.timePassedFromLastRelease[i] == ts.P[i])) {
                    
                    // The release of a job due to the constraint on the maximum possible job offset:
                    // the maximum offset for the first job of tau_i is at most Pi;
                    // as the maximum offset is reached, and thus, tau_i has to release a job
                    (*successors)[successorItr].c[i] = ts.C[i];
                    (*successors)[successorItr].p[i] = ts.P[i];
                    (*successors)[successorItr].timePassedFromLastRelease[i] = 0;
                    (*successors)[successorItr].tauI_releaseNextJobBefore[i] = -1;
                    (*successors)[successorItr].firstJobReleased[i] = true;
                    //(*successors)[successorItr].releaseAtEarliest[i] = false;
                    //(*successors)[successorItr].releasedAtEarliest[i] = true;
                    (*successors)[successorItr].interferred[i] = true; // due to forcing an early release
                    
                } else if (s.firstJobReleased[i] && (s.timePassedFromLastRelease[i] == 2*ts.P[i])) {
                    
                    // The time separation between two consecuitive job releases is at most 2*Pi
                    (*successors)[successorItr].c[i] = ts.C[i];
                    (*successors)[successorItr].p[i] = ts.P[i];
                    (*successors)[successorItr].timePassedFromLastRelease[i] = 0;
                    (*successors)[successorItr].tauI_releaseNextJobBefore[i] = -1;
                    (*successors)[successorItr].firstJobReleased[i] = true;
                    //(*successors)[successorItr].releaseAtEarliest[i] = false;
                    (*successors)[successorItr].interferred[i] = true;
                    //cout << "condition for the maximum time separation between consequitive job releases worked" << endl;
                    
                } else {*/
                
                    (*successors)[successorsNum] = (*successors)[successorItr];
                
                    (*successors)[successorItr].c[i] = ts.C[i];
                    (*successors)[successorItr].p[i] = ts.P[i];
                    (*successors)[successorItr].timePassedFromLastRelease[i] = 0;
                    (*successors)[successorItr].tauI_releaseNextJobBefore[i] = -1;
                    (*successors)[successorItr].firstJobReleased[i] = true;
                    //(*successors)[successorItr].releaseAtEarliest[i] = false;
                    //(*successors)[successorItr].releasedAtEarliest[i] = false;
                    (*successors)[successorItr].interferred[i] = false;
                    
                    successorsNum++;
                //}
            } // end of for loop successorItr
        } // end of if s.p[i] == 0
    }
    

    for (uint_fast16_t successorItr = 0; successorItr < successorsNum; successorItr++) {
        
        (*successors)[successorItr].updateCounters();
        
        // update bounds on WRTs (used later to order states for traversal)
        (*successors)[successorItr].wrts[ts.n-1] = (*successors)[successorItr].c[ts.n-1] + get_Iub_on_tau_n((*successors)[successorItr], ts, m);
        
        for (uint_fast8_t j = 0; j < ts.n-1; j++) {
            (*successors)[successorItr].wrts[j] = get_response_time_UB((*successors)[successorItr], ts, j, m);
        }
    }
}
