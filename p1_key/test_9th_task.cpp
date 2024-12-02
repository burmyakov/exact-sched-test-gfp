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
#include "../custom_types/map_9_tasks.h"
#include "../generate_successors.h"
#include "../algorithm_move.h"
#include "../get_map_binary_keys.h"
#include "../pruning_constraints.h"



using namespace std;

namespace NS_9tasks {
    
    
    // Main data structures
    TS ts; // the task system being analyzed
    uint8_t m;
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
    
    
    
    void get_states_num(mt23* generated, unsigned long int& statesNum, unsigned long int& statesNum_tauKpending) {
        
        statesNum = 0;
        statesNum_tauKpending = 0;
        
        for (mt23::iterator itr23 = (*generated).begin(); itr23 != (*generated).end(); itr23++) {
            for (mt22::iterator itr22 = (itr23->second).begin(); itr22 != (itr23->second).end(); itr22++) {
                for (mt21::iterator itr21 = (itr22->second).begin(); itr21 != (itr22->second).end(); itr21++) {
                    for (mt20::iterator itr20 = (itr21->second).begin(); itr20 != (itr21->second).end(); itr20++) {
                        for (mt19::iterator itr19 = (itr20->second).begin(); itr19 != (itr20->second).end(); itr19++) {
                            for (mt18::iterator itr18 = (itr19->second).begin(); itr18 != (itr19->second).end(); itr18++) {
                                for (mt17::iterator itr17 = (itr18->second).begin(); itr17 != (itr18->second).end(); itr17++) {
                                    for (mt16::iterator itr16 = (itr17->second).begin(); itr16 != (itr17->second).end(); itr16++) {
                                        for (mt15::iterator itr15 = (itr16->second).begin(); itr15 != (itr16->second).end(); itr15++) {
                                            for (mt14::iterator itr14 = (itr15->second).begin(); itr14 != (itr15->second).end(); itr14++) {
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
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        
    }
    
    
    
     
    
    
    
    bool find_dominating_state_c_iterations(const state& s, mt9& visitedStates9) {
        
        for (mt9::reverse_iterator itr9 = visitedStates9.rbegin(); itr9 != visitedStates9.rend(); itr9++) {
            if (itr9->first < s.c[0]) break;
            else {
                for (mt8::reverse_iterator itr8 = (itr9->second).rbegin(); itr8 != (itr9->second).rend(); itr8++) {
                    if (itr8->first < s.c[1]) break;
                    else {
                        for (mt7::reverse_iterator itr7 = (itr8->second).rbegin(); itr7 != (itr8->second).rend(); itr7++) {
                            if (itr7->first < s.c[2]) break;
                            else {
                                for (mt6::reverse_iterator itr6 = (itr7->second).rbegin(); itr6 != (itr7->second).rend(); itr6++) {
                                    if (itr6->first < s.c[3]) break;
                                    else {
                                        for (mt5::reverse_iterator itr5 = (itr6->second).rbegin(); itr5 != (itr6->second).rend(); itr5++) {
                                            if (itr5->first < s.c[4]) break;
                                            else {
                                                for (mt4::reverse_iterator itr4 = (itr5->second).rbegin(); itr4 != (itr5->second).rend(); itr4++) {
                                                    if (itr4->first < s.c[5]) break;
                                                    else {
                                                        for (mt3::reverse_iterator itr3 = (itr4->second).rbegin(); itr3 != (itr4->second).rend(); itr3++) {
                                                            if (itr3->first < s.c[6]) break;
                                                            else {
                                                                for (mt2::reverse_iterator itr2 = (itr3->second).rbegin(); itr2 != (itr3->second).rend(); itr2++) {
                                                                    if (itr2->first < s.c[7]) break;
                                                                    else {
                                                                        for (mt1::reverse_iterator itr1 = (itr2->second).rbegin(); itr1 != (itr2->second).rend(); itr1++) {
                                                                            if (itr1->first < s.c[8]) break;
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
        
        return false;
    }
    
    
    
    
    
    
    bool find_dominating_state_p_iterations(const state& s, mt18& visitedStates18) {
        
        for (mt18::iterator itr18 = visitedStates18.begin(); itr18 != visitedStates18.end(); itr18++) {
            if (itr18->first > s.p[0]) break;
            else {
                for (mt17::iterator itr17 = (itr18->second).begin(); itr17 != (itr18->second).end(); itr17++) {
                    if (itr17->first > s.p[1]) break;
                    else {
                        for (mt16::iterator itr16 = (itr17->second).begin(); itr16 != (itr17->second).end(); itr16++) {
                            if (itr16->first > s.p[2]) break;
                            else {
                                for (mt15::iterator itr15 = (itr16->second).begin(); itr15 != (itr16->second).end(); itr15++) {
                                    if (itr15->first > s.p[3]) break;
                                    else {
                                        for (mt14::iterator itr14 = (itr15->second).begin(); itr14 != (itr15->second).end(); itr14++) {
                                            if (itr14->first > s.p[4]) break;
                                            else {
                                                for (mt13::iterator itr13 = (itr14->second).begin(); itr13 != (itr14->second).end(); itr13++) {
                                                    if (itr13->first > s.p[5]) break;
                                                    else {
                                                        for (mt12::iterator itr12 = (itr13->second).begin(); itr12 != (itr13->second).end(); itr12++) {
                                                            if (itr12->first > s.p[6]) break;
                                                            else {
                                                                for (mt11::iterator itr11 = (itr12->second).begin(); itr11 != (itr12->second).end(); itr11++) {
                                                                    if (itr11->first > s.p[7]) break;
                                                                    else {
                                                                        for (mt10::iterator itr10 = (itr11->second).begin(); itr10 != (itr11->second).end(); itr10++) {
                                                                            if (itr10->first > s.p[8]) break;
                                                                            else if (find_dominating_state_c_iterations(s, itr10->second)) return true;
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
    
    
    
    
    
    
    
    bool find_dominating_state(const state& s, mt23* visitedStates) {
        
        unsigned int keysNum_pj = 0;
        unsigned int keysNum_lj = 0;
        unsigned int keysNum_p1 = 0;
        
        
        get_keys_pj(s, ts.n, keysNum_pj, bKeys_pj);
        
        for (unsigned int i23 = 0; i23 < keysNum_pj; i23++) { // pending jobs binary key
            if ((*visitedStates).find((*bKeys_pj)[i23]) != (*visitedStates).end()) {
                
                get_keys_lj(s, ts.n, (*bKeys_pj)[i23], keysNum_lj, bKeys_lj);
                
                for (unsigned int i22 = 0; i22 < keysNum_lj; i22++) { // locked jobs binary key
                    if (((*visitedStates)[(*bKeys_pj)[i23]]).find((*bKeys_lj)[i22]) != ((*visitedStates)[(*bKeys_pj)[i23]]).end()) {
                        
                        get_keys_p1(s, ts, (*bKeys_lj)[i22], keysNum_p1, bKeys_p1);
                        
                        for (unsigned int i21 = 0; i21 < keysNum_p1; i21++) { // p1 keys
                            if ((((*visitedStates)[(*bKeys_pj)[i23]])[(*bKeys_lj)[i22]]).find((*bKeys_p1)[i21]) != (((*visitedStates)[(*bKeys_pj)[i23]])[(*bKeys_lj)[i22]]).end()) {
                                
                                // sum of remaining execution times
                                for (mt20::reverse_iterator itr20 = ((((*visitedStates)[(*bKeys_pj)[i23]])[(*bKeys_lj)[i22]])[(*bKeys_p1)[i21]]).rbegin(); itr20 != ((((*visitedStates)[(*bKeys_pj)[i23]])[(*bKeys_lj)[i22]])[(*bKeys_p1)[i21]]).rend(); itr20++) {
                                    
                                    if (itr20->first < s.sumCs) break;
                                    else {
                                        
                                        for (mt19::iterator itr19 = (itr20->second).begin(); itr19 != (itr20->second).end(); itr19++) {
                                            if (itr19->first > s.sumSlacks) break;
                                            else if (find_dominating_state_p_iterations(s, itr19->second)) return true;
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
    
    
    
    
    
    
    
    
    
    
    
    
    
    void remove_dominated_states_c_iterations(const state& s, mt9& visitedStates9) {
        
        for (mt9::iterator itr9 = visitedStates9.begin(); itr9 != visitedStates9.end();) {
            if (itr9->first > s.c[0]) break;
            else {
                for (mt8::iterator itr8 = (itr9->second).begin(); itr8 != (itr9->second).end();) {
                    if (itr8->first > s.c[1]) break;
                    else {
                        for (mt7::iterator itr7 = (itr8->second).begin(); itr7 != (itr8->second).end();) {
                            if (itr7->first > s.c[2]) break;
                            else {
                                for (mt6::iterator itr6 = (itr7->second).begin(); itr6 != (itr7->second).end();) {
                                    if (itr6->first > s.c[3]) break;
                                    else {
                                        for (mt5::iterator itr5 = (itr6->second).begin(); itr5 != (itr6->second).end();) {
                                            if (itr5->first > s.c[4]) break;
                                            else {
                                                for (mt4::iterator itr4 = (itr5->second).begin(); itr4 != (itr5->second).end();) {
                                                    if (itr4->first > s.c[5]) break;
                                                    else {
                                                        for (mt3::iterator itr3 = (itr4->second).begin(); itr3 != (itr4->second).end();) {
                                                            if (itr3->first > s.c[6]) break;
                                                            else {
                                                                for (mt2::iterator itr2 = (itr3->second).begin(); itr2 != (itr3->second).end();) {
                                                                    if (itr2->first > s.c[7]) break;
                                                                    else {
                                                                        for (mt1::iterator itr1 = (itr2->second).begin(); itr1 != (itr2->second).end();) {
                                                                            if (itr1->first > s.c[8]) break;
                                                                            else {
                                                                                // state s dominates the current state in map
                                                                                // thus, removing dominated state
                                                                                (itr2->second).erase(itr1++);
                                                                            }
                                                                        }
                                                                        if ((itr2->second).empty()) (itr3->second).erase(itr2++);
                                                                        else ++itr2;
                                                                    }
                                                                } // itr2
                                                                if ((itr3->second).empty()) (itr4->second).erase(itr3++);
                                                                else ++itr3;
                                                            }
                                                        } // itr3
                                                        if ((itr4->second).empty()) (itr5->second).erase(itr4++);
                                                        else ++itr4;
                                                    }
                                                } // itr4
                                                if ((itr5->second).empty()) (itr6->second).erase(itr5++);
                                                else ++itr5;
                                            }
                                        } // itr5
                                        if ((itr6->second).empty()) (itr7->second).erase(itr6++);
                                        else ++itr6;
                                    }
                                } // itr6
                                if ((itr7->second).empty()) (itr8->second).erase(itr7++);
                                else ++itr7;
                            }
                        } // itr7
                        if ((itr8->second).empty()) (itr9->second).erase(itr8++);
                        else ++itr8;
                    }
                } // itr8
                if ((itr9->second).empty()) (visitedStates9).erase(itr9++);
                else ++itr9;
            }
        } // itr9
        
        return;
    }
    
    
    
    
    
    
    void remove_dominated_states_p_iterations(const state& s, mt18& visitedStates18) {
        
        for (mt18::reverse_iterator itr18 = visitedStates18.rbegin(); itr18 != visitedStates18.rend();) {
            if (itr18->first < s.p[0]) break;
            else {
                for (mt17::reverse_iterator itr17 = (itr18->second).rbegin(); itr17 != (itr18->second).rend();) {
                    if (itr17->first < s.p[1]) break;
                    else {
                        for (mt16::reverse_iterator itr16 = (itr17->second).rbegin(); itr16 != (itr17->second).rend();) {
                            if (itr16->first < s.p[2]) break;
                            else {
                                for (mt15::reverse_iterator itr15 = (itr16->second).rbegin(); itr15 != (itr16->second).rend();) {
                                    if (itr15->first < s.p[3]) break;
                                    else {
                                        for (mt14::reverse_iterator itr14 = (itr15->second).rbegin(); itr14 != (itr15->second).rend();) {
                                            if (itr14->first < s.p[4]) break;
                                            else {
                                                for (mt13::reverse_iterator itr13 = (itr14->second).rbegin(); itr13 != (itr14->second).rend();) {
                                                    if (itr13->first < s.p[5]) break;
                                                    else {
                                                        for (mt12::reverse_iterator itr12 = (itr13->second).rbegin(); itr12 != (itr13->second).rend();) {
                                                            if (itr12->first < s.p[6]) break;
                                                            else {
                                                                for (mt11::reverse_iterator itr11 = (itr12->second).rbegin(); itr11 != (itr12->second).rend();) {
                                                                    if (itr11->first < s.p[7]) break;
                                                                    else {
                                                                        for (mt10::reverse_iterator itr10 = (itr11->second).rbegin(); itr10 != (itr11->second).rend();) {
                                                                            if (itr10->first < s.p[8]) break;
                                                                            else {
                                                                                remove_dominated_states_c_iterations(s, (itr10->second));
                                                                                if ((itr10->second).empty()) (itr11->second).erase(--(itr10.base()));
                                                                                else ++itr10;
                                                                            }
                                                                        }
                                                                        if ((itr11->second).empty()) (itr12->second).erase(--(itr11.base()));
                                                                        else ++itr11;
                                                                    }
                                                                }
                                                                if ((itr12->second).empty()) (itr13->second).erase(--(itr12.base()));
                                                                else ++itr12;
                                                            }
                                                        }
                                                        if ((itr13->second).empty()) (itr14->second).erase(--(itr13.base()));
                                                        else ++itr13;
                                                    }
                                                }
                                                if ((itr14->second).empty()) (itr15->second).erase(--(itr14.base()));
                                                else ++itr14;
                                            }
                                        }
                                        if ((itr15->second).empty()) (itr16->second).erase(--(itr15.base()));
                                        else ++itr15;
                                    }
                                }
                                if ((itr16->second).empty()) (itr17->second).erase(--(itr16.base()));
                                else ++itr16;
                            }
                        }
                        if ((itr17->second).empty()) (itr18->second).erase(--(itr17.base()));
                        else ++itr17;
                    }
                }
                if ((itr18->second).empty()) visitedStates18.erase(--(itr18.base()));
                else ++itr18;
            }
        }
        
        return;
    }
    
    
    
    
    
    void remove_dominated_states(const state& s, mt23* visitedStates) {
        
        unsigned int keysNum_pj2 = 0;
        unsigned int keysNum_lj2 = 0;
        unsigned int keysNum_p1_2 = 0;
        
        
        get_keys_pj2(s, ts.n, keysNum_pj2, bKeys_pj2);
        
        for (unsigned int i23 = 0; i23 < keysNum_pj2; i23++) { // pending jobs binary key
            if ((*visitedStates).find((*bKeys_pj2)[i23]) != (*visitedStates).end()) {
                
                get_keys_lj2(s, ts.n, (*bKeys_pj2)[i23], keysNum_lj2, bKeys_lj2);
                
                for (unsigned int i22 = 0; i22 < keysNum_lj2; i22++) { // locked jobs binary key
                    if (((*visitedStates)[(*bKeys_pj2)[i23]]).find((*bKeys_lj2)[i22]) != ((*visitedStates)[(*bKeys_pj2)[i23]]).end()) {
                        
                        get_keys_p1_2(s, ts, (*bKeys_lj2)[i22], keysNum_p1_2, bKeys_p1_2);
                        
                        for (unsigned int i21 = 0; i21 < keysNum_p1_2; i21++) { // p1 key
                            if (((*visitedStates)[(*bKeys_pj2)[i23]][(*bKeys_lj2)[i22]]).find((*bKeys_p1_2)[i21]) != ((*visitedStates)[(*bKeys_pj2)[i23]][(*bKeys_lj2)[i22]]).end()) {
                                
                                for (mt20::iterator itr20 = (((((*visitedStates)[(*bKeys_pj2)[i23]])[(*bKeys_lj2)[i22]])[(*bKeys_p1_2)[i21]])).begin(); itr20 != (((((*visitedStates)[(*bKeys_pj2)[i23]])[(*bKeys_lj2)[i22]])[(*bKeys_p1_2)[i21]])).end();) {
                                    
                                    if (itr20->first > s.sumCs) break;
                                    else {
                                        for (mt19::reverse_iterator itr19 = (itr20->second).rbegin(); itr19 != (itr20->second).rend();) {
                                            if (itr19->first < s.sumSlacks) break;
                                            else remove_dominated_states_p_iterations(s, itr19->second);
                                            
                                            if ((itr19->second).empty()) (itr20->second).erase(--(itr19.base()));
                                            else ++itr19;
                                        }
                                        if ((itr20->second).empty()) (((((*visitedStates)[(*bKeys_pj2)[i23]])[(*bKeys_lj2)[i22]])[(*bKeys_p1_2)[i21]])).erase(itr20++);
                                        else ++itr20;
                                    }
                                }
                                
                                if (((((*visitedStates)[(*bKeys_pj2)[i23]])[(*bKeys_lj2)[i22]])[(*bKeys_p1_2)[i21]]).empty()) (((*visitedStates)[(*bKeys_pj2)[i23]])[(*bKeys_lj2)[i22]]).erase((*bKeys_p1_2)[i21]);
                            }
                        }
                        
                        if ((((*visitedStates)[(*bKeys_pj2)[i23]])[(*bKeys_lj2)[i22]]).empty()) ((*visitedStates)[(*bKeys_pj2)[i23]]).erase((*bKeys_lj2)[i22]);
                    }
                }
                
                if ((((*visitedStates)[(*bKeys_pj2)[i23]])).empty()) (*visitedStates).erase((*bKeys_pj2)[i23]);
            }
        }
        
        return;
    }
    
    
    
    
    
    
    
    void add_state_to_map(const state& s, mt23* visitedStates) {

        my_bitset bs_pj;
        for (uint8_t i = 0; i < ts.n; i++) if (s.c[i] > 0) bs_pj.set(i, 1); else bs_pj.set(i, 0);

        my_bitset bs_lj;
        for (uint8_t i = 0; i < ts.n; i++) if (s.p[i] > 0) bs_lj.set(i, 1); else bs_lj.set(i, 0);

        my_bitset bs_p1;
        for (uint8_t i = 0; i < ts.n; i++) if (s.p[i] > ((float)(ts.P[i]))/2) bs_p1.set(i, 1); else bs_p1.set(i, 0);

        // add state s to map
        (*visitedStates)[bs_pj][bs_lj][bs_p1][s.sumCs][s.sumSlacks][s.p[0]][s.p[1]][s.p[2]][s.p[3]][s.p[4]][s.p[5]][s.p[6]][s.p[7]][s.p[8]][s.c[0]][s.c[1]][s.c[2]][s.c[3]][s.c[4]][s.c[5]][s.c[6]][s.c[7]][s.c[8]] = true;
    }
    
    
    
    
    
    
    bool update_map(const state& s, mt23* visitedStates, const bool removeStates) {
        
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
        mt23* generated = new mt23;
        
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
            for (unsigned int successorItr = 0; successorItr < successorsNum; successorItr++) {
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
            cout << endl << "P1 version: " << endl;
            cout << "Saved states:\t\t" << savedStatesNum << endl;
            if (savedStatesNum > 0) cout << "Saved states with tau_9 pending: " << savedStatesNum_tauKpending << "  ( " << (float)((int)(savedStatesNum_tauKpending*10000/savedStatesNum))/100 << " %)" << endl;
            cout << "Visited states:\t\t" << visitedStatesNum << endl;
            cout << "Visited states with tau_9 pending: " << visitedStatesNum_withTauKpending << "  ( " << (float)((int)(visitedStatesNum_withTauKpending*10000/visitedStatesNum))/100 << " %)" << endl << endl;
        }
        
        return schedulable;
    }
} // end of namespace NS_9tasks





bool test_9th_task(const bool verbose_, const uint8_t m_, const TS& ts_, const bool removeStates_, unsigned long int& savedStatesNum_, unsigned long int& visitedStatesNum_) {
    
    NS_9tasks::verbose = verbose_;
    
    bool schedulable = NS_9tasks::populate(m_, ts_, removeStates_);
    savedStatesNum_ = NS_9tasks::savedStatesNum;
    visitedStatesNum_ = NS_9tasks::visitedStatesNum;
    
    return schedulable;
}
