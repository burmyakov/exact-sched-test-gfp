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
#include "../custom_types/map_11_tasks.h"
#include "../generate_successors.h"
#include "../algorithm_move.h"
#include "../get_map_binary_keys.h"
#include "../pruning_constraints.h"
#include "../response_time_Guan2009.h"



using namespace std;

namespace NS_11tasks {

vector<my_bitset>* bKeys_pj;

unsigned long savedStatesNum = 0;
unsigned long visitedStatesNum = 0;
unsigned long savedStatesNum_tauKpending = 0;
unsigned long visitedStatesNum_tauKpending = 0;



bool find_dominating_state_lpts(const state& s, const TS& ts, mt14& visitedStates) {
    
    for (mt14::iterator itr14 = visitedStates.begin(); itr14 != visitedStates.end(); itr14++) {
        if (itr14->first > s.p[10]) break;
        else {
            for (mt13::reverse_iterator itr13 = (itr14->second).rbegin(); itr13 != (itr14->second).rend(); itr13++) {
                if (itr13->first < s.c[10]) break;
                else {
                    for (mt12::iterator itr12 = (itr13->second).begin(); itr12 != (itr13->second).end(); itr12++) {
                        if (itr12->first > s.p[9]) break;
                        else {
                            for (mt11::reverse_iterator itr11 = (itr12->second).rbegin(); itr11 != (itr12->second).rend(); itr11++) {
                                if (itr11->first < s.c[9]) break;
                                else {
                                    for (mt10::iterator itr10 = (itr11->second).begin(); itr10 != (itr11->second).end(); itr10++) {
                                        if (itr10->first > s.p[8]) break;
                                        else {
                                            for (mt9::reverse_iterator itr9 = (itr10->second).rbegin(); itr9 != (itr10->second).rend(); itr9++) {
                                                if (itr9->first < s.c[8]) break;
                                                else {
                                                    for (mt8::iterator itr8 = (itr9->second).begin(); itr8 != (itr9->second).end(); itr8++) {
                                                        if (itr8->first > s.p[7]) break;
                                                        else {
                                                            for (mt7::reverse_iterator itr7 = (itr8->second).rbegin(); itr7 != (itr8->second).rend(); itr7++) {
                                                                if (itr7->first < s.c[7]) break;
                                                                else {
                                                                    for (mt6::iterator itr6 = (itr7->second).begin(); itr6 != (itr7->second).end(); itr6++) {
                                                                        if (itr6->first > s.p[6]) break;
                                                                        else {
                                                                            for (mt5::reverse_iterator itr5 = (itr6->second).rbegin(); itr5 != (itr6->second).rend(); itr5++) {
                                                                                if (itr5->first < s.c[6]) break;
                                                                                else {
                                                                                    for (mt4::iterator itr4 = (itr5->second).begin(); itr4 != (itr5->second).end(); itr4++) {
                                                                                        if (itr4->first > s.p[5]) break;
                                                                                        else {
                                                                                            for (mt3::reverse_iterator itr3 = (itr4->second).rbegin(); itr3 != (itr4->second).rend(); itr3++) {
                                                                                                if (itr3->first < s.c[5]) break;
                                                                                                else {
                                                                                                    for (mt2::iterator itr2 = (itr3->second).begin(); itr2 != (itr3->second).end(); itr2++) {
                                                                                                        if (itr2->first > s.p[4]) break;
                                                                                                        else {
                                                                                                            for (mt1::reverse_iterator itr1 = (itr2->second).rbegin(); itr1 != (itr2->second).rend(); itr1++) {
                                                                                                                if (itr1->first < s.c[4]) break;
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





bool find_dominating_state_hpt4(const state& s, const TS& ts, mt16& visitedStates) {
    
    if (s.p[3] <= ts.P[3] - ts.C[3]) { // s.c[3] == 0
        for (mt16::iterator itr16 = visitedStates.begin(); itr16 != visitedStates.end(); itr16++) {
            if (itr16->first > s.p[3]) break;
            else {
                if (find_dominating_state_lpts(s, ts, itr16->second)) return true;
            }
        }
    } else { // s.c[3] > 0
        if (find_dominating_state_lpts(s, ts, visitedStates[s.p[3]])) return true;
    }
    
    return false;
}





bool find_dominating_state_hpt3(const state& s, const TS& ts, mt18& visitedStates) {
    
    if (s.p[2] <= ts.P[2] - ts.C[2]) { // s.c[2] == 0
        for (mt18::iterator itr18 = visitedStates.begin(); itr18 != visitedStates.end(); itr18++) {
            if (itr18->first > s.p[2]) break;
            else {
                if (find_dominating_state_hpt4(s, ts, itr18->second)) return true;
            }
        }
    } else { // s.c[2] > 0
        if (find_dominating_state_hpt4(s, ts, visitedStates[s.p[2]])) return true;
    }
    
    return false;
}



bool find_dominating_state_hpt2(const state& s, const TS& ts, mt20& visitedStates) {
    
    if (s.p[1] <= ts.P[1] - ts.C[1]) { // s.c[1] == 0
        for (mt20::iterator itr20 = visitedStates.begin(); itr20 != visitedStates.end(); itr20++) {
            if (itr20->first > s.p[1]) break;
            else {
                if (find_dominating_state_hpt3(s, ts, itr20->second)) return true;
            }
        }
    } else { // s.c[1] > 0
        if (find_dominating_state_hpt3(s, ts, visitedStates[s.p[1]])) return true;
    }
    
    return false;
}




bool find_dominating_state_hpt1(const state& s, const TS& ts, mt22& visitedStates) {
    
    if (s.p[0] <= ts.P[0] - ts.C[0]) { // s.c[0] == 0
        for (mt22::iterator itr22 = visitedStates.begin(); itr22 != visitedStates.end(); itr22++) {
            if (itr22->first > s.p[0]) break;
            else {
                if (find_dominating_state_hpt2(s, ts, itr22->second)) return true;
            }
        }
    } else { // s.c[0] > 0
        if (find_dominating_state_hpt2(s, ts, visitedStates[s.p[0]])) return true;
    }
    
    return false;
}



bool find_dominating_state(const state& s, const unsigned short m, const TS& ts, mt23* visitedStates) {
    
    unsigned int keysNum_pj = 0;
    get_keys_pj(s, m, keysNum_pj, bKeys_pj);
    
    for (int i23 = 0; i23 < keysNum_pj; i23++) {
        if ((*visitedStates).find((*bKeys_pj)[i23]) != (*visitedStates).end()) {
            if (find_dominating_state_hpt1(s, ts, (*visitedStates)[(*bKeys_pj)[i23]])) return true;
        }
    }

    return false;
}








void add_state_to_map(const state& s, const TS& ts, mt23* visitedStates) {
    
    my_bitset bs_pj;
    for (int i = 0; i < ts.n; i++) if (s.c[i] > 0) bs_pj.set(i, 1); else bs_pj.set(i, 0);
    
    (*visitedStates)[bs_pj][s.p[0]][s.p[1]][s.p[2]][s.p[3]][s.p[10]][s.c[10]][s.p[9]][s.c[9]][s.p[8]][s.c[8]][s.p[7]][s.c[7]][s.p[6]][s.c[6]][s.p[5]][s.c[5]][s.p[4]][s.c[4]] = true;
}






bool update_map(const state& s, const unsigned short m, const TS& ts, mt23* visitedStates) {
    
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



bool analyse_state(state& s, const TS& ts, const unsigned short m, priority_queue<state>& q, mt23* generated, const bool verbose) {

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
    
    mt23* generated = new mt23;
    
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
        if (savedStatesNum > 0) cout << "Saved states with tau_11 pending: " << savedStatesNum_tauKpending << "  ( " << (float)((int)(savedStatesNum_tauKpending*10000/savedStatesNum))/100 << " %)" << endl;
        cout << "Visited states:\t\t" << visitedStatesNum << endl;
        cout << "Visited states with tau_11 pending: " << visitedStatesNum_tauKpending << "  ( " << (float)((int)(visitedStatesNum_tauKpending*10000/visitedStatesNum))/100 << " %)" << endl << endl;
    }
    
    return schedulable;
}
} // end of namespace NS_11tasks_p2





bool test_11th_task(const bool verbose_, const uint_fast8_t m_, const TS& ts_, unsigned long int& savedStatesNum_, unsigned long int& visitedStatesNum_) {
    
    bool schedulable = NS_11tasks::populate(m_, ts_, verbose_);
    savedStatesNum_ = NS_11tasks::savedStatesNum;
    visitedStatesNum_ = NS_11tasks::visitedStatesNum;
    
    return schedulable;
}
