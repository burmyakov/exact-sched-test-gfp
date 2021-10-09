#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <climits>
#include "../custom_types/ts.h"
#include "../custom_types/state.h"
#include "../custom_types/map_6_tasks.h"
#include "../generate_successors.h"
#include "../algorithm_move.h"
#include "../get_map_binary_keys.h"
#include "../pruning_constraints.h"
#include "../response_time_Guan2009.h"



using namespace std;

namespace NS_6tasks {

vector<my_bitset>* bKeys_pj;

unsigned long savedStatesNum = 0;
unsigned long visitedStatesNum = 0;
unsigned long savedStatesNum_tauKpending = 0;
unsigned long visitedStatesNum_tauKpending = 0;



bool find_dominating_state_lpts(const state& s, const TS& ts, mt8& visitedStates) {
    
    for (mt8::iterator itr8 = visitedStates.begin(); itr8 != visitedStates.end(); itr8++) {
        if (itr8->first > s.p[5]) break;
        else {
            for (mt7::reverse_iterator itr7 = (itr8->second).rbegin(); itr7 != (itr8->second).rend(); itr7++) {
                if (itr7->first < s.c[5]) break;
                else {
                    for (mt6::iterator itr6 = (itr7->second).begin(); itr6 != (itr7->second).end(); itr6++) {
                        if (itr6->first > s.p[4]) break;
                        else {
                            for (mt5::reverse_iterator itr5 = (itr6->second).rbegin(); itr5 != (itr6->second).rend(); itr5++) {
                                if (itr5->first < s.c[4]) break;
                                else {
                                    for (mt4::iterator itr4 = (itr5->second).begin(); itr4 != (itr5->second).end(); itr4++) {
                                        if (itr4->first > s.p[3]) break;
                                        else {
                                            for (mt3::reverse_iterator itr3 = (itr4->second).rbegin(); itr3 != (itr4->second).rend(); itr3++) {
                                                if (itr3->first < s.c[3]) break;
                                                else {
                                                    for (mt2::iterator itr2 = (itr3->second).begin(); itr2 != (itr3->second).end(); itr2++) {
                                                        if (itr2->first > s.p[2]) break;
                                                        else {
                                                            for (mt1::reverse_iterator itr1 = (itr2->second).rbegin(); itr1 != (itr2->second).rend(); itr1++) {
                                                                if (itr1->first < s.c[2]) break;
                                                                else {
                                                                    // state s is dominated by
                                                                    // another state in the map
                                                                    return true;
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    return false;
}






bool find_dominating_state_hpt2(const state& s, const TS& ts, mt10& visitedStates) {
    
    if (s.p[1] <= ts.P[1] - ts.C[1]) { // s.c[1] == 0
        for (mt10::iterator itr10 = visitedStates.begin(); itr10 != visitedStates.end(); itr10++) {
            if (itr10->first > s.p[1]) break;
            else {
                if (find_dominating_state_lpts(s, ts, itr10->second)) return true;
            }
        }
    } else { // s.c[1] > 0
        if (find_dominating_state_lpts(s, ts, visitedStates[s.p[1]])) return true;
    }
    
    return false;
}




bool find_dominating_state_hpt1(const state& s, const TS& ts, mt12& visitedStates) {
    
    if (s.p[0] <= ts.P[0] - ts.C[0]) { // s.c[0] == 0
        for (mt12::iterator itr12 = visitedStates.begin(); itr12 != visitedStates.end(); itr12++) {
            if (itr12->first > s.p[0]) break;
            else {
                if (find_dominating_state_hpt2(s, ts, itr12->second)) return true;
            }
        }
    } else { // s.c[0] > 0
        if (find_dominating_state_hpt2(s, ts, visitedStates[s.p[0]])) return true;
    }
    
    return false;
}



bool find_dominating_state(const state& s, const unsigned short m, const TS& ts, mt13* visitedStates) {
    
    unsigned int keysNum_pj = 0;
    get_keys_pj(s, m, keysNum_pj, bKeys_pj);
    
    for (int i13 = 0; i13 < keysNum_pj; i13++) {
        if ((*visitedStates).find((*bKeys_pj)[i13]) != (*visitedStates).end()) {
            if (find_dominating_state_hpt1(s, ts, (*visitedStates)[(*bKeys_pj)[i13]])) return true;
        }
    }

    return false;
}










void add_state_to_map(const state& s, const TS& ts, mt13* visitedStates) {
    
    my_bitset bs_pj;
    for (int i = 0; i < ts.n; i++) if (s.c[i] > 0) bs_pj.set(i, 1); else bs_pj.set(i, 0);
    
    (*visitedStates)[bs_pj][s.p[0]][s.p[1]][s.p[5]][s.c[5]][s.p[4]][s.c[4]][s.p[3]][s.c[3]][s.p[2]][s.c[2]] = true;
}






bool update_map(const state& s, const unsigned short m, const TS& ts, mt13* visitedStates) {
    
    // Check if some state in map dominates state s
    if (find_dominating_state(s, m, ts, visitedStates)) return false;
    else {
        // No state in map dominates state s
        add_state_to_map(s, ts, visitedStates);
        savedStatesNum++;
        if (s.c[s.n-1] > 0) savedStatesNum_tauKpending++;
    }
    
    return true;
}








void init(const uint_fast8_t m, TS& ts) {
    
    bKeys_pj = new vector<my_bitset>(pow(2.0, ts.n));
    
    uint_fast8_t* rtsGuan = new uint_fast8_t[ts.n];
    rtsGuan = response_time_Guan2009(ts, m);
    
    for (uint_fast8_t i = 0; i < ts.n; i++) {
        ts.WRTub[i] = rtsGuan[i];
    }
    
    delete [] rtsGuan;
    
    return;
}






/*void print_queue(priority_queue<state> q, const TS& ts) {
    
    cout << "states in queue: " << q.size() << endl;
    
    while (!q.empty())
    {
        (q.top()).printCmpct(ts);
        //cout << endl;
        q.pop();
    }
    std::cout << endl << endl;
}*/



bool analyse_state(state& s, const TS& ts, const unsigned short m, priority_queue<state>& q, mt13* generated, const bool verbose) {

    //cout << "in analyse_state()" << endl;
    
    bool schedulable = true;
    bool* tauI_justHadPendJob = new bool [ts.n];
    short int algMove_ExitCode = 0;
    
    bool statePruned = false;
    bool continueSchedulerIterations = true;
    
    //cout << "starting scheduler iterations" << endl;
    while (continueSchedulerIterations) {
        
        continueSchedulerIterations = false;
        visitedStatesNum++;
        if (s.c[ts.n-1] > 0) visitedStatesNum_tauKpending++;

        for (int j = 0; j < ts.n; j++) tauI_justHadPendJob[j] = (s.c[j] > 0 ? true : false);
        
        if (!check_adversary_pruning_conditions(s, ts, m)) {
            statePruned = true;
            //cout << "some pruning cond. violated; state is pruned" << endl;
            break;
        }
        
        //cout << "state before ALG move: ";
        //s.printCmpct(ts);

        algMove_ExitCode = algorithm_move(s, ts, m, verbose);
        
        //cout << "state after ALG move: ";
        //s.printCmpct(ts);
    
        if (algMove_ExitCode == -1) { schedulable = false; break; }
        else if (algMove_ExitCode == 1) { statePruned = true; break;}
        
        s.updateLockedJobsNum();
        if (s.lockedJobsNum == ts.n) continueSchedulerIterations = true;
    } // end of while over scheduler iterations
    //cout << "scheduler iterations ended" << endl;
        
    
    if ((algMove_ExitCode == 0) && (!statePruned) && (schedulable)) {
        //cout << "checking for dominating states" << endl;
        
        s.updateSumCs();
        if (s.sumCs > 0) {
            if (update_map(s, m, ts, generated)) {
                // update state parameters
                for (unsigned short j = 0; j < ts.n-1; j++) {
                    s.wrts[j] = get_response_time_UB(s, ts, j, m);
                    s.tauI_jobJustCompleted[j] = ((tauI_justHadPendJob[j] && s.c[j] == 0) ? true : false);
                }
                
                s.wrts[ts.n-1] = s.c[ts.n-1] + get_Iub_on_tau_n(s, ts, m);
                
                //cout << "no dominating state found; state added into map and queue" << endl;
                q.push(s);
            } else {
                // else dominating state exists in map, current state is pruned
                //cout << "dominated state found" << endl;
                //cout << "state is pruned" << endl;
            }
        }
    }
    
    delete [] tauI_justHadPendJob;
    return schedulable;
}






bool populate(const unsigned short m, const TS& ts_, const bool verbose) {
    
    TS ts = ts_;
    
    unsigned long tStart, tExec;
    tStart = clock();
    
    init(m, ts);
    if (ts.WRTub[ts.n-1] <= ts.D[ts.n-1]) {
        if (verbose) cout << "Task " << (int)ts.n << " is schedulable according to Guan's sufficient test; wrt: " << (int)ts.WRTub[ts.n-1] << ", and its deadline: " << (int)ts.D[ts.n-1] << endl;
        return true;
    }

    mt13* generated = new mt13;
    
    state s(ts.n);
    priority_queue<state> q;
    q.push(s);
    
    bool schedulable = true;
    
    vector<state>* successors = new vector<state>(pow(2.0, ts.n), state(ts.n));
    uint_fast16_t successorsNum;
    
    while (!q.empty()) {

        s = q.top();
        q.pop();

        generate_successors(ts, s, m, successors, successorsNum);
        
        // Analyse generated successors;
        // discard those successors which have been visited at previous iterations
        for (int successorItr = 0; successorItr < successorsNum; successorItr++) {
            s = (*successors)[successorItr];
            
            visitedStatesNum++;
            if (s.c[ts.n-1] > 0) visitedStatesNum_tauKpending++;
            
            schedulable = analyse_state(s, ts, m, q, generated, verbose);
            if (!schedulable) break;
        } // successors have been handled
        
        if (!schedulable) break;
    } // next iterations of while loop

    // Clean memory
    priority_queue<state> qEmpty;
    swap(q, qEmpty);
    (*generated).clear();
    delete generated;
    
    delete bKeys_pj;
    
    tExec = clock() - tStart;
    
    if (verbose) {
        cout << endl << "Execution time:\t\t" << (float)(tExec*100/CLOCKS_PER_SEC)/100 << " sec" << endl;
        cout << "Saved states:\t\t" << savedStatesNum << endl;
        if (savedStatesNum > 0) cout << "Saved states with tau_6 pending: " << savedStatesNum_tauKpending << "  ( " << (float)((int)(savedStatesNum_tauKpending*10000/savedStatesNum))/100 << " %)" << endl;
        cout << "Visited states:\t\t" << visitedStatesNum << endl;
        cout << "Visited states with tau_6 pending: " << visitedStatesNum_tauKpending << "  ( " << (float)((int)(visitedStatesNum_tauKpending*10000/visitedStatesNum))/100 << " %)" << endl << endl;
    }
    
    return schedulable;
}
} // end of namespace NS_5tasks





bool test_6th_task(const bool verbose_, const unsigned short m_, const TS& ts_, unsigned long int& savedStatesNum_, unsigned long int& visitedStatesNum_) {
    
    bool schedulable = NS_6tasks::populate(m_, ts_, verbose_);
    savedStatesNum_ = NS_6tasks::savedStatesNum;
    visitedStatesNum_ = NS_6tasks::visitedStatesNum;
    
    return schedulable;
}
