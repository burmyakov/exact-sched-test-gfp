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
#include "../custom_types/map_4_tasks.h"
#include "../generate_successors.h"
#include "../algorithm_move.h"
#include "../get_map_binary_keys.h"
#include "../pruning_constraints.h"


using namespace std;


namespace NS_4tasks_p2 {
    
    // Main data structures
    TS ts; // the task system being analyzed
    int m;
    //map<state, bool> generated;
    unsigned long int visitedStatesNum = 0;
    unsigned long int visitedStatesNum_withTauKpending = 0;
    unsigned long int savedStatesNum = 0;
    unsigned long int savedStatesNum_tauKpending = 0;
    bool verbose = false;

    
    vector<my_bitset>* bKeys_pj;
    vector<my_bitset>* bKeys_p1;
    vector<my_bitset>* bKeys_p2;
    vector<my_bitset>* bKeys_lj;
    vector<my_bitset>* bKeys_pj2;
    vector<my_bitset>* bKeys_p1_2;
    vector<my_bitset>* bKeys_p2_2;
    vector<my_bitset>* bKeys_lj2;
    
    
    
    void get_states_num(mt14* generated, unsigned long int& statesNum, unsigned long int& statesNum_tauKpending) {
        
        statesNum = 0;
        statesNum_tauKpending = 0;
        
        for (mt14::iterator itr14 = (*generated).begin(); itr14 != (*generated).end(); itr14++) {
            for (mt13::iterator itr13 = (itr14->second).begin(); itr13 != (itr14->second).end(); itr13++) {
                for (mt12::iterator itr12 = (itr13->second).begin(); itr12 != (itr13->second).end(); itr12++) {
                    for (mt11::iterator itr11 = (itr12->second).begin(); itr11 != (itr12->second).end(); itr11++) {
                        for (mt10::iterator itr10 = (itr11->second).begin(); itr10 != (itr11->second).end(); itr10++) {
                            for (mt9::iterator itr9 = (itr10->second).begin(); itr9 != (itr10->second).end(); itr9++) {
                                for (mt8::iterator itr8 = (itr9->second).begin(); itr8 != (itr9->second).end(); itr8++) {
                                    for (mt7::iterator itr7 = (itr8->second).begin(); itr7 != (itr8->second).end(); itr7++) {
                                        for (mt6::iterator itr6 = (itr7->second).begin(); itr6 != (itr7->second).end(); itr6++) {
                                            for (mt5::iterator itr5 = (itr6->second).begin(); itr5 != (itr6->second).end(); itr5++) {
                                                for (mt4::iterator itr4 = (itr5->second).begin(); itr4 != (itr5->second).end(); itr4++) {
                                                    for (mt3::iterator itr3 = (itr4->second).begin(); itr3 != (itr4->second).end(); itr3++) {
                                                        for (mt2::iterator itr2 = (itr3->second).begin(); itr2 != (itr3->second).end(); itr2++) {
                                                            for (mt1::iterator itr1 = (itr2->second).begin(); itr1 != (itr2->second).end(); itr1++) {
                                                                statesNum++;
                                                                if ((itr1->first) > 0) statesNum_tauKpending++;
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

    
    
    
    bool find_dominating_state_c_iterations(const state& s, mt4& visitedStates4) {
        
        for (mt4::reverse_iterator itr4 = visitedStates4.rbegin(); itr4 != visitedStates4.rend(); itr4++) {
            if (itr4->first < s.c[0]) break;
            else {
                for (mt3::reverse_iterator itr3 = (itr4->second).rbegin(); itr3 != (itr4->second).rend(); itr3++) {
                    if (itr3->first < s.c[1]) break;
                    else {
                        for (mt2::reverse_iterator itr2 = (itr3->second).rbegin(); itr2 != (itr3->second).rend(); itr2++) {
                            if (itr2->first < s.c[2]) break;
                            else {
                                for (mt1::reverse_iterator itr1 = (itr2->second).rbegin(); itr1 != (itr2->second).rend(); itr1++) {
                                    if (itr1->first < s.c[3]) break;
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
        
        return false;
    }






    bool find_dominating_state_p_iterations(const state& s, mt8& visitedStates8) {
        
        for (mt8::iterator itr8 = visitedStates8.begin(); itr8 != visitedStates8.end(); itr8++) {
            if (itr8->first > s.t[0]) break;
            else {
                for (mt7::iterator itr7 = (itr8->second).begin(); itr7 != (itr8->second).end(); itr7++) {
                    if (itr7->first > s.t[1]) break;
                    else {
                        for (mt6::iterator itr6 = (itr7->second).begin(); itr6 != (itr7->second).end(); itr6++) {
                            if (itr6->first > s.t[2]) break;
                            else {
                                for (mt5::iterator itr5 = (itr6->second).begin(); itr5 != (itr6->second).end(); itr5++) {
                                    if (itr5->first > s.t[3]) break;
                                    else if (find_dominating_state_c_iterations(s, itr5->second)) return true;
                                }
                            }
                        }
                    }
                }
            }
        }
        
        return false;
    }
    
    
    
    
    
    
    
    bool find_dominating_state(const state& s, mt14* visitedStates) {

        unsigned int keysNum_pj = 0;
        unsigned int keysNum_lj = 0;
        unsigned int keysNum_p1 = 0;
        unsigned int keysNum_p2 = 0;
        
        
        get_keys_pj(s, ts.n, keysNum_pj, bKeys_pj);
        
        for (int i14 = 0; i14 < keysNum_pj; i14++) { // pending jobs binary key
            if ((*visitedStates).find((*bKeys_pj)[i14]) != (*visitedStates).end()) {
                
                get_keys_lj(s, ts.n, (*bKeys_pj)[i14], keysNum_lj, bKeys_lj);
                
                for (int i13 = 0; i13 < keysNum_lj; i13++) { // locked jobs binary key
                    if (((*visitedStates)[(*bKeys_pj)[i14]]).find((*bKeys_lj)[i13]) != ((*visitedStates)[(*bKeys_pj)[i14]]).end()) {
                        
                        get_keys_p1(s, ts, (*bKeys_lj)[i13], keysNum_p1, bKeys_p1);
                        
                        for (int i12 = 0; i12 < keysNum_p1; i12++) { // p1 keys
                            if ((((*visitedStates)[(*bKeys_pj)[i14]])[(*bKeys_lj)[i13]]).find((*bKeys_p1)[i12]) != (((*visitedStates)[(*bKeys_pj)[i14]])[(*bKeys_lj)[i13]]).end()) {
                                
                                get_keys_p2(s, ts, (*bKeys_lj)[i13], (*bKeys_p1)[i12], keysNum_p2, bKeys_p2);
                                for (int i11 = 0; i11 < keysNum_p2; i11++) {
                                    
                                    if (((((*visitedStates)[(*bKeys_pj)[i14]])[(*bKeys_lj)[i13]])[(*bKeys_p1)[i12]]).find((*bKeys_p2)[i11]) != (((*visitedStates)[(*bKeys_pj)[i14]])[(*bKeys_lj)[i13]])[(*bKeys_p1)[i12]].end()) {
                                        
                                        // sum of remaining execution times
                                        for (mt10::reverse_iterator itr10 = ((((*visitedStates)[(*bKeys_pj)[i14]])[(*bKeys_lj)[i13]])[(*bKeys_p1)[i12]])[(*bKeys_p2)[i11]].rbegin(); itr10 != ((((*visitedStates)[(*bKeys_pj)[i14]])[(*bKeys_lj)[i13]])[(*bKeys_p1)[i12]])[(*bKeys_p2)[i11]].rend(); itr10++) {
                                            
                                            if (itr10->first < s.sumCs) break;
                                            else {
                                                
                                                for (mt9::iterator itr9 = (itr10->second).begin(); itr9 != (itr10->second).end(); itr9++) {
                                                    if (itr9->first > s.sumSlacks) break;
                                                    else if (find_dominating_state_p_iterations(s, itr9->second)) return true;
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
        
        
        return false; // no state in map dominates state s
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    void remove_dominated_states_c_iterations(const state& s, mt4& visitedStates4) {
        
        for (mt4::iterator itr4 = visitedStates4.begin(); itr4 != visitedStates4.end();) {
            if (itr4->first > s.c[0]) break;
            else {
                for (mt3::iterator itr3 = (itr4->second).begin(); itr3 != (itr4->second).end();) {
                    if (itr3->first > s.c[1]) break;
                    else {
                        for (mt2::iterator itr2 = (itr3->second).begin(); itr2 != (itr3->second).end();) {
                            if (itr2->first > s.c[2]) break;
                            else {
                                for (mt1::iterator itr1 = (itr2->second).begin(); itr1 != (itr2->second).end();) {
                                    if (itr1->first > s.c[3]) break;
                                    else {
                                        // state s dominates the current state in map
                                        // thus, removing dominated state
                                        (itr2->second).erase(itr1++);
                                    }
                                } // itr1
                                if ((itr2->second).empty()) (itr3->second).erase(itr2++);
                                else ++itr2;
                            }
                        } // itr2
                        if ((itr3->second).empty()) (itr4->second).erase(itr3++);
                        else ++itr3;
                    }
                } // itr3
                if ((itr4->second).empty()) visitedStates4.erase(itr4++);
                else ++itr4;
            }
        } // itr4
        
        return;
    }
    
    
    
    
    
    
    void remove_dominated_states_p_iterations(const state& s, mt8& visitedStates8) {
        
        for (mt8::reverse_iterator itr8 = visitedStates8.rbegin(); itr8 != visitedStates8.rend();) {
            if (itr8->first < s.t[0]) break;
            else {
                for (mt7::reverse_iterator itr7 = (itr8->second).rbegin(); itr7 != (itr8->second).rend();) {
                    if (itr7->first < s.t[1]) break;
                    else {
                        for (mt6::reverse_iterator itr6 = (itr7->second).rbegin(); itr6 != (itr7->second).rend();) {
                            if (itr6->first < s.t[2]) break;
                            else {
                                for (mt5::reverse_iterator itr5 = (itr6->second).rbegin(); itr5 != (itr6->second).rend();) {
                                    if (itr5->first < s.t[3]) break;
                                    else {
                                        remove_dominated_states_c_iterations(s, (itr5->second));
                                        if ((itr5->second).empty()) (itr6->second).erase(--(itr5.base()));
                                        else ++itr5;
                                    }
                                } // itr5
                                if ((itr6->second).empty()) (itr7->second).erase(--(itr6.base()));
                                else ++itr6;
                            }
                        } // itr6
                        if ((itr7->second).empty()) (itr8->second).erase(--(itr7.base()));
                        else ++itr7;
                    }
                }
                if ((itr8->second).empty()) visitedStates8.erase(--(itr8.base()));
                else ++itr8;
            }
        }
        
        return;
    }
    
    
    
    
    
    void remove_dominated_states(const state& s, mt14* visitedStates) {

        unsigned int keysNum_pj2 = 0;
        unsigned int keysNum_lj2 = 0;
        unsigned int keysNum_p1_2 = 0;
        unsigned int keysNum_p2_2 = 0;
        
        
        get_keys_pj2(s, ts.n, keysNum_pj2, bKeys_pj2);
        
        for (int i14 = 0; i14 < keysNum_pj2; i14++) { // pending jobs binary key
            if ((*visitedStates).find((*bKeys_pj2)[i14]) != (*visitedStates).end()) {
                
                get_keys_lj2(s, ts.n, (*bKeys_pj2)[i14], keysNum_lj2, bKeys_lj2);
                
                for (int i13 = 0; i13 < keysNum_lj2; i13++) { // locked jobs binary key
                    if (((*visitedStates)[(*bKeys_pj2)[i14]]).find((*bKeys_lj2)[i13]) != ((*visitedStates)[(*bKeys_pj2)[i14]]).end()) {
                        
                        get_keys_p1_2(s, ts, (*bKeys_lj2)[i13], keysNum_p1_2, bKeys_p1_2);
                        
                        for (int i12 = 0; i12 < keysNum_p1_2; i12++) { // p1 key
                            if (((*visitedStates)[(*bKeys_pj2)[i14]][(*bKeys_lj2)[i13]]).find((*bKeys_p1_2)[i12]) != ((*visitedStates)[(*bKeys_pj2)[i14]][(*bKeys_lj2)[i13]]).end()) {
                                
                                get_keys_p2_2(s, ts, (*bKeys_lj2)[i13], (*bKeys_p1_2)[i12], keysNum_p2_2, bKeys_p2_2);
                                for (int i11 = 0; i11 < keysNum_p2_2; i11++) {
                                    
                                    if (((*visitedStates)[(*bKeys_pj2)[i14]][(*bKeys_lj2)[i13]])[(*bKeys_p1_2)[i12]].find((*bKeys_p2_2)[i11]) != ((*visitedStates)[(*bKeys_pj2)[i14]][(*bKeys_lj2)[i13]])[(*bKeys_p1_2)[i12]].end()) {
                                        
                                        for (mt10::iterator itr10 = ((((*visitedStates)[(*bKeys_pj2)[i14]])[(*bKeys_lj2)[i13]])[(*bKeys_p1_2)[i12]])[(*bKeys_p2_2)[i11]].begin(); itr10 != ((((*visitedStates)[(*bKeys_pj2)[i14]])[(*bKeys_lj2)[i13]])[(*bKeys_p1_2)[i12]])[(*bKeys_p2_2)[i11]].end();) {
                                            
                                            if (itr10->first > s.sumCs) break;
                                            else {
                                                for (mt9::reverse_iterator itr9 = (itr10->second).rbegin(); itr9 != (itr10->second).rend();) {
                                                    if (itr9->first < s.sumSlacks) break;
                                                    else remove_dominated_states_p_iterations(s, itr9->second);
                                                    
                                                    if ((itr9->second).empty()) (itr10->second).erase(--(itr9.base()));
                                                    else ++itr9;
                                                }
                                                if ((itr10->second).empty()) ((((*visitedStates)[(*bKeys_pj2)[i14]])[(*bKeys_lj2)[i13]])[(*bKeys_p1_2)[i12]])[(*bKeys_p2_2)[i11]].erase(itr10++);
                                                else ++itr10;
                                            }
                                        }
                                        if (((((*visitedStates)[(*bKeys_pj2)[i14]])[(*bKeys_lj2)[i13]])[(*bKeys_p1_2)[i12]])[(*bKeys_p2_2)[i11]].empty()) (((*visitedStates)[(*bKeys_pj2)[i14]])[(*bKeys_lj2)[i13]])[(*bKeys_p1_2)[i12]].erase((*bKeys_p2_2)[i11]);
                                    }
                                }
                                
                                if (((((*visitedStates)[(*bKeys_pj2)[i14]])[(*bKeys_lj2)[i13]])[(*bKeys_p1_2)[i12]]).empty()) (((*visitedStates)[(*bKeys_pj2)[i14]])[(*bKeys_lj2)[i13]]).erase((*bKeys_p1_2)[i12]);
                            }
                        }
                        
                        if ((((*visitedStates)[(*bKeys_pj2)[i14]])[(*bKeys_lj2)[i13]]).empty()) ((*visitedStates)[(*bKeys_pj2)[i14]]).erase((*bKeys_lj2)[i13]);
                    }
                }
                
                if ((((*visitedStates)[(*bKeys_pj2)[i14]])).empty()) (*visitedStates).erase((*bKeys_pj2)[i14]);
            }
        }

        return;
    }
    
    
    
    
    
    
    
    void add_state_to_map(const state& s, mt14* visitedStates) {

        my_bitset bs_pj;
        for (int i = 0; i < ts.n; i++) if (s.c[i] > 0) bs_pj.set(i, 1); else bs_pj.set(i, 0);

        my_bitset bs_lj;
        for (int i = 0; i < ts.n; i++) if (s.t[i] > 0) bs_lj.set(i, 1); else bs_lj.set(i, 0);

        my_bitset bs_p1;
        for (int i = 0; i < ts.n; i++) if (s.t[i] > ((float)(ts.T[i]))/2) bs_p1.set(i, 1); else bs_p1.set(i, 0);
        
        my_bitset bs_p2;
        for (unsigned short i = 0; i < ts.n; i++)
            if ((s.t[i] <= ((float)(ts.T[i]))/4)||((s.t[i] > ((float)(ts.T[i]))/2)&&(s.t[i] <= ((float)(3*ts.T[i]))/4)))
                bs_p2.set(i, 0); else bs_p2.set(i, 1);

        // add state s to map
        (*visitedStates)[bs_pj][bs_lj][bs_p1][bs_p2][s.sumCs][s.sumSlacks][s.t[0]][s.t[1]][s.t[2]][s.t[3]][s.c[0]][s.c[1]][s.c[2]][s.c[3]] = true;
    }
    
    
    
    
    
    
    bool update_map(const state& s, mt14* visitedStates, const bool removeStates) {

        // Check if some state in map dominates state s
        if (find_dominating_state(s, visitedStates)) return false;
        else {
            // No state in map dominates state s
            if (removeStates) remove_dominated_states(s, visitedStates);
            add_state_to_map(s, visitedStates);
        }
        
        return true;
    }
    
    
    
    
    
    
    
    
    void init() {
        
        bKeys_pj = new vector<my_bitset>(pow(2.0, ts.n));
        bKeys_p1 = new vector<my_bitset>(pow(2.0, ts.n));
        bKeys_p2 = new vector<my_bitset>(pow(2.0, ts.n));
        bKeys_lj = new vector<my_bitset>(pow(2.0, ts.n));
        bKeys_pj2 = new vector<my_bitset>(pow(2.0, ts.n));
        bKeys_p1_2 = new vector<my_bitset>(pow(2.0, ts.n));
        bKeys_p2_2 = new vector<my_bitset>(pow(2.0, ts.n));
        bKeys_lj2 = new vector<my_bitset>(pow(2.0, ts.n));
        
        return;
    }
    
    
    
    
    
    
    
    
    
    bool populate(const unsigned short m_, const TS& ts_, const bool removeStates) {
        
        ts = ts_;
        m = m_;
        
        init();
        
        savedStatesNum = 0;
        savedStatesNum_tauKpending = 0;
        visitedStatesNum = 0;
		visitedStatesNum_withTauKpending = 0;
        mt14* generated = new mt14;
        
        state s(ts);
        priority_queue<state> q;
        q.push(s);
        
        bool schedulable = true;
        
        vector<state>* successors = new vector<state>(pow(2.0, ts.n), state(ts));
        unsigned short successorsNum;
        
        
        while (!q.empty()) {
            s = q.top();
            q.pop();
            
            generate_successors(ts, s, m, successors, successorsNum);
            
            // Analyse generated successors;
            // discard those successors which have been visited at previous iterations
            for (int successorItr = 0; successorItr < successorsNum; successorItr++) {
                s = (*successors)[successorItr];
                
                visitedStatesNum++;
                if (s.c[ts.n-1] > 0) visitedStatesNum_withTauKpending++;
                
                if (!condition_for_releases_of_hp_jobs(s)) continue;
                if (!condition_necessary_unsched(s, m)) continue;
                
                short int algMove_ExitCode = algorithm_move(s, ts.n, m, verbose);
                
                if (algMove_ExitCode == -1) {
                    // deadline miss
                    schedulable = false;
                    break;
                } else if (algMove_ExitCode == 0) {
                    visitedStatesNum++;
                    if (s.c[ts.n-1] > 0) visitedStatesNum_withTauKpending++;
                    
                    s.updateSumCs();
                    if (s.sumCs > 0) {
                        s.updateSumSlacks();
                        s.updateLockedJobsNum();
                        s.updatePendJobsNum();
                        if (update_map(s, generated, removeStates))
                            q.push(s);
                    }
                    
                } else {
                    // state is discarded
                }
            } // successors have been handled
            if (!schedulable) break;
        } // next iterations of while loop
        
        get_states_num(generated, savedStatesNum, savedStatesNum_tauKpending);
        
        // Clean memory
        priority_queue<state> qEmpty;
        swap(q, qEmpty);
        (*generated).clear();
        delete generated;
        
        delete bKeys_pj;
        delete bKeys_lj;
        delete bKeys_p1;
        delete bKeys_p2;
        delete bKeys_pj2;
        delete bKeys_lj2;
        delete bKeys_p1_2;
        delete bKeys_p2_2;
        
        
        if (verbose) {
            cout << endl << "P2 version: " << endl;
            cout << "Saved states:\t\t" << savedStatesNum << endl;
            if (savedStatesNum > 0) cout << "Saved states with tau_4 pending: " << savedStatesNum_tauKpending << "  ( " << (float)((int)(savedStatesNum_tauKpending*10000/savedStatesNum))/100 << " %)" << endl;
            cout << "Visited states:\t\t" << visitedStatesNum << endl;
            cout << "Visited states with tau_4 pending: " << visitedStatesNum_withTauKpending << "  ( " << (float)((int)(visitedStatesNum_withTauKpending*10000/visitedStatesNum))/100 << " %)" << endl << endl;
        }
        
        return schedulable;
    }
} // end of namespace NS_4tasks_p2





bool test_4th_task_p2(const bool verbose_, const unsigned short m_, const TS& ts_, const bool removeStates_, unsigned long int& savedStatesNum_, unsigned long int& visitedStatesNum_) {

    NS_4tasks_p2::verbose = verbose_;
    
    bool schedulable = NS_4tasks_p2::populate(m_, ts_, removeStates_);
    savedStatesNum_ = NS_4tasks_p2::savedStatesNum;
    visitedStatesNum_ = NS_4tasks_p2::visitedStatesNum;
    
    return schedulable;
}
