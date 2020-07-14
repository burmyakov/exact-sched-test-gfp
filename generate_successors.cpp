#include <iostream>
#include <climits>
#include <vector>
#include "custom_types/ts.h"
#include "custom_types/state.h"
#include "get_delta_t.h"
#include "scheduler.h"
#include "pruning_constraints.h"


using namespace std;



bool is_processor_available_to_tau_i(const state& s, const unsigned short i, const unsigned short m) {
    
    unsigned short hpJobsNum = 0;
    
    for (unsigned short indx = 0; indx < i; indx++) {
        if (s.c[indx] > 0) {
            hpJobsNum++;
            if (hpJobsNum == m) break;
        }
    }
    
    return ((hpJobsNum < m)?true:false);
}









// Successors are not sorted
void generate_successors(const TS& ts, state& s, const unsigned short m, vector<state>* successors, unsigned short& successorsNum) {
    
    int curSuccessorsNum;
    
    // Generate successor states
    (*successors)[0] = s;
    successorsNum = 1;

    for (int i = 0; i < ts.n; i++) {
        
        for (unsigned short successorItr = 0; successorItr < successorsNum; successorItr++)
            (*successors)[successorItr].processorAvailableForTau_i[i] = is_processor_available_to_tau_i((*successors)[successorItr], i, m);
        
        if (s.p[i] == 0) {
            
            // Davis and Burns 2011 condition A for release of tau_k
            if ((i == (ts.n-1)) && (!s.prevState_processorAvailableForTau_i[i])) continue;
            
            curSuccessorsNum = successorsNum;
            for (int successorItr = 0; successorItr < curSuccessorsNum; successorItr++) {
                
                // Davis and Burns 2011 condition B for tau_k and any tau_i
                if (!condition_cri_2(s, m, i, (*successors)[successorItr].processorAvailableForTau_i[i]))
                    continue;
                
                (*successors)[successorsNum] = (*successors)[successorItr];
                (*successors)[successorsNum].c[i] = ts.C[i];
                (*successors)[successorsNum].p[i] = ts.P[i];
                (*successors)[successorsNum].interferred[i] = false;
                successorsNum++;
            }
        }
    }
    
    
    for (unsigned short successorItr = 0; successorItr < successorsNum; successorItr++) {
        (*successors)[successorItr].updateCounters();
        
        for (unsigned short i = 0; i < ts.n; i++)
            (*successors)[successorItr].processorAvailableForTau_i[i] = is_processor_available_to_tau_i((*successors)[successorItr], i, m);
    }
    
}
