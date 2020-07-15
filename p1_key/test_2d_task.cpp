#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <climits>
#include <cinttypes>
#include "../custom_types/ts.h"
#include "../custom_types/state.h"
#include "../custom_types/map_2_tasks.h"
#include "../generate_successors.h"
#include "../algorithm_move.h"
#include "../get_map_binary_keys.h"
#include "../pruning_constraints.h"


using namespace std;


namespace NS_2tasks {

    
    // Main data structures
    TS ts; // the task system being analyzed
    uint8_t m;
    //map<state, bool> generated;
    unsigned long int visitedStatesNum = 0;
    unsigned long int visitedStatesNum_withTauKpending = 0;
    unsigned long int savedStatesNum = 0;
    unsigned long int savedStatesNum_tauKpending = 0;
    bool verbose = false;

    
    vector<my_bitset>* bKeys_pj;
    vector<my_bitset>* bKeys_p1;
    vector<my_bitset>* bKeys_lj;
    vector<my_bitset>* bKeys_pj2;
    vector<my_bitset>* bKeys_p1_2;
    vector<my_bitset>* bKeys_lj2;
    
    
    
    
    void get_states_num(mt9* generated, unsigned long int& statesNum, unsigned long int& statesNum_tauKpending) {
        
        statesNum = 0;
        statesNum_tauKpending = 0;
        
        for (mt9::iterator itr9 = (*generated).begin(); itr9 != (*generated).end(); itr9++) {
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
    
    
    
    
    
    bool find_dominating_state_c_iterations(const state& s, mt2& visitedStates2) {
        
        for (mt2::reverse_iterator itr2 = visitedStates2.rbegin(); itr2 != visitedStates2.rend(); itr2++) {
            if (itr2->first < s.c[0]) break;
            else {
                for (mt1::reverse_iterator itr1 = (itr2->second).rbegin(); itr1 != (itr2->second).rend(); itr1++) {
                    if (itr1->first < s.c[1]) break;
                    else {
                        // state s is dominated by
                        // another state in the map
                        return true;
                    }
                }
            }
        }
        
        return false;
    }





    
    bool find_dominating_state_p_iterations(const state& s, mt4& visitedStates4) {
        
        for (mt4::iterator itr4 = visitedStates4.begin(); itr4 != visitedStates4.end(); itr4++) {
            if (itr4->first > s.p[0]) break;
            else {
                for (mt3::iterator itr3 = (itr4->second).begin(); itr3 != (itr4->second).end(); itr3++) {
                    if (itr3->first > s.p[1]) break;
                    else if (find_dominating_state_c_iterations(s, itr3->second)) return true;
                }
            }
        }
        
        return false;
    }
    
    
    
    
    
    
    
    bool find_dominating_state(const state& s, mt9* visitedStates) {


        unsigned int keysNum_pj = 0;
        unsigned int keysNum_lj = 0;
        unsigned int keysNum_p1 = 0;
        
        
        get_keys_pj(s, ts.n, keysNum_pj, bKeys_pj);
        
        for (unsigned int i9 = 0; i9 < keysNum_pj; i9++) { // pending jobs binary key
            if ((*visitedStates).find((*bKeys_pj)[i9]) != (*visitedStates).end()) {
                
                get_keys_lj(s, ts.n, (*bKeys_pj)[i9], keysNum_lj, bKeys_lj);
                
                for (unsigned int i8 = 0; i8 < keysNum_lj; i8++) { // locked jobs binary key
                    if (((*visitedStates)[(*bKeys_pj)[i9]]).find((*bKeys_lj)[i8]) != ((*visitedStates)[(*bKeys_pj)[i9]]).end()) {
                        
                        get_keys_p1(s, ts, (*bKeys_lj)[i8], keysNum_p1, bKeys_p1);
                        for (unsigned int i7 = 0; i7 < keysNum_p1; i7++) { // p1 keys
                            
                            if ((((*visitedStates)[(*bKeys_pj)[i9]])[(*bKeys_lj)[i8]]).find((*bKeys_p1)[i7]) != (((*visitedStates)[(*bKeys_pj)[i9]])[(*bKeys_lj)[i8]]).end()) {
                                
                                // sum of remaining execution times
                                for (mt6::reverse_iterator itr6 = ((((*visitedStates)[(*bKeys_pj)[i9]])[(*bKeys_lj)[i8]])[(*bKeys_p1)[i7]]).rbegin(); itr6 != ((((*visitedStates)[(*bKeys_pj)[i9]])[(*bKeys_lj)[i8]])[(*bKeys_p1)[i7]]).rend(); itr6++) {
                                    
                                    if (itr6->first < s.sumCs) break;
                                    else {
                                        
                                        for (mt5::iterator itr5 = (itr6->second).begin(); itr5 != (itr6->second).end(); itr5++) {
                                            if (itr5->first > s.sumSlacks) break;
                                            else if (find_dominating_state_p_iterations(s, itr5->second)) return true;
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
    
    
    
    
    
    
    
    
    
    
    
    
    
    void remove_dominated_states_c_iterations(const state& s, mt2& visitedStates2) {
        
        for (mt2::iterator itr2 = visitedStates2.begin(); itr2 != visitedStates2.end();) {
            if (itr2->first > s.c[0]) break;
            else {
                for (mt1::iterator itr1 = (itr2->second).begin(); itr1 != (itr2->second).end();) {
                    if (itr1->first > s.c[1]) break;
                    else {
                        // state s dominates the current state in map
                        // thus, removing dominated state
                        (itr2->second).erase(itr1++);
                    }
                } // itr1
                if ((itr2->second).empty()) visitedStates2.erase(itr2++);
                else ++itr2;
            }
        } // itr2
        
        return;
    }
    
    
    
    
    
    
    void remove_dominated_states_p_iterations(const state& s, mt4& visitedStates4) {
        
        for (mt4::reverse_iterator itr4 = visitedStates4.rbegin(); itr4 != visitedStates4.rend();) {
            if (itr4->first < s.p[0]) break;
            else {
                for (mt3::reverse_iterator itr3 = (itr4->second).rbegin(); itr3 != (itr4->second).rend();) {
                    if (itr3->first < s.p[1]) break;
                    else {
                        remove_dominated_states_c_iterations(s, (itr3->second));
                        if ((itr3->second).empty()) (itr4->second).erase(--(itr3.base()));
                        else ++itr3;
                    }
                } // itr3
                if ((itr4->second).empty()) visitedStates4.erase(--(itr4.base()));
                else ++itr4;
            }
        } // itr5
        
        return;
    }
    
    
    
    
    
    void remove_dominated_states(const state& s, mt9* visitedStates) {

        unsigned int keysNum_pj2 = 0;
        unsigned int keysNum_lj2 = 0;
        unsigned int keysNum_p1_2 = 0;
        
        
        get_keys_pj2(s, ts.n, keysNum_pj2, bKeys_pj2);
        
        for (unsigned int i9 = 0; i9 < keysNum_pj2; i9++) { // pending jobs binary key
            if ((*visitedStates).find((*bKeys_pj2)[i9]) != (*visitedStates).end()) {
                
                get_keys_lj2(s, ts.n, (*bKeys_pj2)[i9], keysNum_lj2, bKeys_lj2);
                
                for (unsigned int i8 = 0; i8 < keysNum_lj2; i8++) { // locked jobs binary key
                    if (((*visitedStates)[(*bKeys_pj2)[i9]]).find((*bKeys_lj2)[i8]) != ((*visitedStates)[(*bKeys_pj2)[i9]]).end()) {
                        
                        get_keys_p1_2(s, ts, (*bKeys_lj2)[i8], keysNum_p1_2, bKeys_p1_2);
                        
                        for (unsigned int i7 = 0; i7 < keysNum_p1_2; i7++) { // p1 key
                            if (((*visitedStates)[(*bKeys_pj2)[i9]][(*bKeys_lj2)[i8]]).find((*bKeys_p1_2)[i7]) != ((*visitedStates)[(*bKeys_pj2)[i9]][(*bKeys_lj2)[i8]]).end()) {
                                
                                for (mt6::iterator itr6 = ((((*visitedStates)[(*bKeys_pj2)[i9]])[(*bKeys_lj2)[i8]])[(*bKeys_p1_2)[i7]]).begin(); itr6 != ((((*visitedStates)[(*bKeys_pj2)[i9]])[(*bKeys_lj2)[i8]])[(*bKeys_p1_2)[i7]]).end();) {
                                    
                                    if (itr6->first > s.sumCs) break;
                                    else {
                                        for (mt5::reverse_iterator itr5 = (itr6->second).rbegin(); itr5 != (itr6->second).rend();) {
                                            if (itr5->first < s.sumSlacks) break;
                                            else remove_dominated_states_p_iterations(s, itr5->second);
                                            
                                            if ((itr5->second).empty()) (itr6->second).erase(--(itr5.base()));
                                            else ++itr5;
                                        }
                                        if ((itr6->second).empty()) ((((*visitedStates)[(*bKeys_pj2)[i9]])[(*bKeys_lj2)[i8]])[(*bKeys_p1_2)[i7]]).erase(itr6++);
                                        else ++itr6;
                                    }
                                }
                                
                                if (((((*visitedStates)[(*bKeys_pj2)[i9]])[(*bKeys_lj2)[i8]])[(*bKeys_p1_2)[i7]]).empty()) (((*visitedStates)[(*bKeys_pj2)[i9]])[(*bKeys_lj2)[i8]]).erase((*bKeys_p1_2)[i7]);
                                
                            }
                        }
                        
                        if ((((*visitedStates)[(*bKeys_pj2)[i9]])[(*bKeys_lj2)[i8]]).empty()) ((*visitedStates)[(*bKeys_pj2)[i9]]).erase((*bKeys_lj2)[i8]);
                    }
                }
                
                if ((((*visitedStates)[(*bKeys_pj2)[i9]])).empty()) (*visitedStates).erase((*bKeys_pj2)[i9]);
            }
            
        }

        return;
    }
    
    
    
    
    
    
    
    void add_state_to_map(const state& s, mt9* visitedStates) {

        // Get bitset keys of state s
        my_bitset bs_pj;
        for (uint8_t i = 0; i < ts.n; i++) if (s.c[i] > 0) bs_pj.set(i, 1); else bs_pj.set(i, 0);
        
        my_bitset bs_lj;
        for (uint8_t i = 0; i < ts.n; i++) if (s.p[i] > 0) bs_lj.set(i, 1); else bs_lj.set(i, 0);
        
        my_bitset bs_p1;
        for (uint8_t i = 0; i < ts.n; i++) if (s.p[i] > ((float)(ts.P[i]))/2) bs_p1.set(i, 1); else bs_p1.set(i, 0);
        
        // add state s to map
        (*visitedStates)[bs_pj][bs_lj][bs_p1][s.sumCs][s.sumSlacks][s.p[0]][s.p[1]][s.c[0]][s.c[1]] = true;
    }
    
    
    
    
    
    
    bool update_map(const state& s, mt9* visitedStates, const bool removeStates) {

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
        bKeys_lj = new vector<my_bitset>(pow(2.0, ts.n));
        bKeys_pj2 = new vector<my_bitset>(pow(2.0, ts.n));
        bKeys_p1_2 = new vector<my_bitset>(pow(2.0, ts.n));
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
        mt9* generated = new mt9;
        
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
                
                int8_t algMove_ExitCode = algorithm_move(s, ts.n, m, verbose);
                
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
        delete bKeys_pj2;
        delete bKeys_lj2;
        delete bKeys_p1_2;
        
        
        if (verbose) {
            cout << endl << "P1 vesrion: " << endl;
            cout << "Saved states:\t\t" << savedStatesNum << endl;
            if (savedStatesNum > 0) cout << "Saved states with tau_2 pending: " << savedStatesNum_tauKpending << "  ( " << (float)((int)(savedStatesNum_tauKpending*10000/savedStatesNum))/100 << " %)" << endl;
            cout << "Visited states:\t\t" << visitedStatesNum << endl;
            cout << "Visited states with tau_2 pending: " << visitedStatesNum_withTauKpending << "  ( " << (float)((int)(visitedStatesNum_withTauKpending*10000/visitedStatesNum))/100 << " %)" << endl << endl;
        }
        
        return schedulable;
    }
} // end of namespace NS_2tasks





bool test_2d_task(const bool verbose_, const uint8_t m_, const TS& ts_, const bool removeStates_, unsigned long int& savedStatesNum_, unsigned long int& visitedStatesNum_) {

    NS_2tasks::verbose = verbose_;
    
    bool schedulable = NS_2tasks::populate(m_, ts_, removeStates_);
    savedStatesNum_ = NS_2tasks::savedStatesNum;
    visitedStatesNum_ = NS_2tasks::visitedStatesNum;
    
    return schedulable;
}
