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
#include "../custom_types/map_14_tasks.h"
#include "../generate_successors.h"
#include "../algorithm_move.h"
#include "../get_map_binary_keys.h"
#include "../pruning_constraints.h"



using namespace std;

namespace NS_14tasks_p3 {

    // Main data structures
    TS ts; // the task system being analyzed
    int m;
    unsigned long int visitedStatesNum = 0;
    unsigned long int visitedStatesNum_withTauKpending = 0;
    unsigned long int savedStatesNum = 0;
    unsigned long int savedStatesNum_tauKpending = 0;
    bool verbose = false;
    
    
    vector<my_bitset>* bKeys_pj;
    vector<my_bitset>* bKeys_p1;
    vector<my_bitset>* bKeys_p2;
    vector<my_bitset>* bKeys_p3;
    vector<my_bitset>* bKeys_lj;
    vector<my_bitset>* bKeys_pj2;
    vector<my_bitset>* bKeys_p1_2;
    vector<my_bitset>* bKeys_p2_2;
    vector<my_bitset>* bKeys_p3_2;
    vector<my_bitset>* bKeys_lj2;
    
    
    
    
    void get_states_num(mt35* generated, unsigned long int& statesNum, unsigned long int& statesNum_tauKpending) {
        
        statesNum = 0;
        statesNum_tauKpending = 0;
        
        for (mt35::iterator itr35 = (*generated).begin(); itr35 != (*generated).end(); itr35++) {
            for (mt34::iterator itr34 = (itr35->second).begin(); itr34 != (itr35->second).end(); itr34++) {
                for (mt33::iterator itr33 = (itr34->second).begin(); itr33 != (itr34->second).end(); itr33++) {
                    for (mt32::iterator itr32 = (itr33->second).begin(); itr32 != (itr33->second).end(); itr32++) {
                        for (mt31::iterator itr31 = (itr32->second).begin(); itr31 != (itr32->second).end(); itr31++) {
                            for (mt30::iterator itr30 = (itr31->second).begin(); itr30 != (itr31->second).end(); itr30++) {
                                for (mt29::iterator itr29 = (itr30->second).begin(); itr29 != (itr30->second).end(); itr29++) {
                                    for (mt28::iterator itr28 = (itr29->second).begin(); itr28 != (itr29->second).end(); itr28++) {
                                        for (mt27::iterator itr27 = (itr28->second).begin(); itr27 != (itr28->second).end(); itr27++) {
                                            for (mt26::iterator itr26 = (itr27->second).begin(); itr26 != (itr27->second).end(); itr26++) {
                                                for (mt25::iterator itr25 = (itr26->second).begin(); itr25 != (itr26->second).end(); itr25++) {
                                                    for (mt24::iterator itr24 = (itr25->second).begin(); itr24 != (itr25->second).end(); itr24++) {
                                                        for (mt23::iterator itr23 = (itr24->second).begin(); itr23 != (itr24->second).end(); itr23++) {
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
    
    
    
    
    
    
    
    
    bool find_dominating_state_c_iterations(const state& s, mt14& visitedStates14) {
        
        for (mt14::reverse_iterator itr14 = visitedStates14.rbegin(); itr14 != visitedStates14.rend(); itr14++) {
            if (itr14->first < s.c[0]) break;
            else {
                for (mt13::reverse_iterator itr13 = (itr14->second).rbegin(); itr13 != (itr14->second).rend(); itr13++) {
                    if (itr13->first < s.c[1]) break;
                    else {
                        for (mt12::reverse_iterator itr12 = (itr13->second).rbegin(); itr12 != (itr13->second).rend(); itr12++) {
                            if (itr12->first < s.c[2]) break;
                            else {
                                for (mt11::reverse_iterator itr11 = (itr12->second).rbegin(); itr11 != (itr12->second).rend(); itr11++) {
                                    if (itr11->first < s.c[3]) break;
                                    else {
                                        for (mt10::reverse_iterator itr10 = (itr11->second).rbegin(); itr10 != (itr11->second).rend(); itr10++) {
                                            if (itr10->first < s.c[4]) break;
                                            else {
                                                for (mt9::reverse_iterator itr9 = (itr10->second).rbegin(); itr9 != (itr10->second).rend(); itr9++) {
                                                    if (itr9->first < s.c[5]) break;
                                                    else {
                                                        for (mt8::reverse_iterator itr8 = (itr9->second).rbegin(); itr8 != (itr9->second).rend(); itr8++) {
                                                            if (itr8->first < s.c[6]) break;
                                                            else {
                                                                for (mt7::reverse_iterator itr7 = (itr8->second).rbegin(); itr7 != (itr8->second).rend(); itr7++) {
                                                                    if (itr7->first < s.c[7]) break;
                                                                    else {
                                                                        for (mt6::reverse_iterator itr6 = (itr7->second).rbegin(); itr6 != (itr7->second).rend(); itr6++) {
                                                                            if (itr6->first < s.c[8]) break;
                                                                            else {
                                                                                for (mt5::reverse_iterator itr5 = (itr6->second).rbegin(); itr5 != (itr6->second).rend(); itr5++) {
                                                                                    if (itr5->first < s.c[9]) break;
                                                                                    else {
                                                                                        for (mt4::reverse_iterator itr4 = (itr5->second).rbegin(); itr4 != (itr5->second).rend(); itr4++) {
                                                                                            if (itr4->first < s.c[10]) break;
                                                                                            else {
                                                                                                for (mt3::reverse_iterator itr3 = (itr4->second).rbegin(); itr3 != (itr4->second).rend(); itr3++) {
                                                                                                    if (itr3->first < s.c[11]) break;
                                                                                                    else {
                                                                                                        for (mt2::reverse_iterator itr2 = (itr3->second).rbegin(); itr2 != (itr3->second).rend(); itr2++) {
                                                                                                            if (itr2->first < s.c[12]) break;
                                                                                                            else {
                                                                                                                for (mt1::reverse_iterator itr1 = (itr2->second).rbegin(); itr1 != (itr2->second).rend(); itr1++) {
                                                                                                                    if (itr1->first < s.c[13]) break;
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
    
    
    
    
    
    
    bool find_dominating_state_p_iterations(const state& s, mt28& visitedStates28) {
        
        for (mt28::iterator itr28 = visitedStates28.begin(); itr28 != visitedStates28.end(); itr28++) {
            if (itr28->first > s.t[0]) break;
            else {
                for (mt27::iterator itr27 = (itr28->second).begin(); itr27 != (itr28->second).end(); itr27++) {
                    if (itr27->first > s.t[1]) break;
                    else {
                        for (mt26::iterator itr26 = (itr27->second).begin(); itr26 != (itr27->second).end(); itr26++) {
                            if (itr26->first > s.t[2]) break;
                            else {
                                for (mt25::iterator itr25 = (itr26->second).begin(); itr25 != (itr26->second).end(); itr25++) {
                                    if (itr25->first > s.t[3]) break;
                                    else {
                                        for (mt24::iterator itr24 = (itr25->second).begin(); itr24 != (itr25->second).end(); itr24++) {
                                            if (itr24->first > s.t[4]) break;
                                            else {
                                                for (mt23::iterator itr23 = (itr24->second).begin(); itr23 != (itr24->second).end(); itr23++) {
                                                    if (itr23->first > s.t[5]) break;
                                                    else {
                                                        for (mt22::iterator itr22 = (itr23->second).begin(); itr22 != (itr23->second).end(); itr22++) {
                                                            if (itr22->first > s.t[6]) break;
                                                            else {
                                                                for (mt21::iterator itr21 = (itr22->second).begin(); itr21 != (itr22->second).end(); itr21++) {
                                                                    if (itr21->first > s.t[7]) break;
                                                                    else {
                                                                        for (mt20::iterator itr20 = (itr21->second).begin(); itr20 != (itr21->second).end(); itr20++) {
                                                                            if (itr20->first > s.t[8]) break;
                                                                            else {
                                                                                for (mt19::iterator itr19 = (itr20->second).begin(); itr19 != (itr20->second).end(); itr19++) {
                                                                                    if (itr19->first > s.t[9]) break;
                                                                                    else {
                                                                                        for (mt18::iterator itr18 = (itr19->second).begin(); itr18 != (itr19->second).end(); itr18++) {
                                                                                            if (itr18->first > s.t[10]) break;
                                                                                            else {
                                                                                                for (mt17::iterator itr17 = (itr18->second).begin(); itr17 != (itr18->second).end(); itr17++) {
                                                                                                    if (itr17->first > s.t[11]) break;
                                                                                                    else {
                                                                                                        for (mt16::iterator itr16 = (itr17->second).begin(); itr16 != (itr17->second).end(); itr16++) {
                                                                                                            if (itr16->first > s.t[12]) break;
                                                                                                            else {
                                                                                                                for (mt15::iterator itr15 = (itr16->second).begin(); itr15 != (itr16->second).end(); itr15++) {
                                                                                                                    if (itr15->first > s.t[13]) break;
                                                                                                                    else if (find_dominating_state_c_iterations(s, itr15->second)) return true;
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
    
    
    
    
    
    
    
    bool find_dominating_state(const state& s, mt35* visitedStates) {
        
        unsigned int keysNum_pj = 0;
        unsigned int keysNum_lj = 0;
        unsigned int keysNum_p1 = 0;
        unsigned int keysNum_p2 = 0;
        unsigned int keysNum_p3 = 0;
        
        
        get_keys_pj(s, ts.n, keysNum_pj, bKeys_pj);
        
        for (int i35 = 0; i35 < keysNum_pj; i35++) { // pending jobs binary key
            if ((*visitedStates).find((*bKeys_pj)[i35]) != (*visitedStates).end()) {
                
                get_keys_lj(s, ts.n, (*bKeys_pj)[i35], keysNum_lj, bKeys_lj);
                for (int i34 = 0; i34 < keysNum_lj; i34++) { // locked jobs binary key
                    
                    if (((*visitedStates)[(*bKeys_pj)[i35]]).find((*bKeys_lj)[i34]) != ((*visitedStates)[(*bKeys_pj)[i35]]).end()) {
                        
                        get_keys_p1(s, ts, (*bKeys_lj)[i34], keysNum_p1, bKeys_p1);
                        for (int i33 = 0; i33 < keysNum_p1; i33++) { // p1 keys
                            
                            if ((((*visitedStates)[(*bKeys_pj)[i35]])[(*bKeys_lj)[i34]]).find((*bKeys_p1)[i33]) != (((*visitedStates)[(*bKeys_pj)[i35]])[(*bKeys_lj)[i34]]).end()) {
                                
                                get_keys_p2(s, ts, (*bKeys_lj)[i34], (*bKeys_p1)[i33], keysNum_p2, bKeys_p2);
                                for (int i32 = 0; i32 < keysNum_p2; i32++) {
                                    
                                    if (((((*visitedStates)[(*bKeys_pj)[i35]])[(*bKeys_lj)[i34]])[(*bKeys_p1)[i33]]).find((*bKeys_p2)[i32]) != (((*visitedStates)[(*bKeys_pj)[i35]])[(*bKeys_lj)[i34]])[(*bKeys_p1)[i33]].end()) {
                                        
                                        get_keys_p3(s, ts, (*bKeys_lj)[i34], (*bKeys_p1)[i33], (*bKeys_p2)[i32], keysNum_p3, bKeys_p3);
                                        for (int i31 = 0; i31 < keysNum_p3; i31++) {
                                            
                                            if (((((*visitedStates)[(*bKeys_pj)[i35]])[(*bKeys_lj)[i34]])[(*bKeys_p1)[i33]])[(*bKeys_p2)[i32]].find((*bKeys_p3)[i31]) != (((*visitedStates)[(*bKeys_pj)[i35]])[(*bKeys_lj)[i34]])[(*bKeys_p1)[i33]][(*bKeys_p2)[i32]].end()) {
                                                
                                                // sum of remaining execution times
                                                for (mt30::reverse_iterator itr30 = (((((*visitedStates)[(*bKeys_pj)[i35]])[(*bKeys_lj)[i34]])[(*bKeys_p1)[i33]]))[(*bKeys_p2)[i32]][(*bKeys_p3)[i31]].rbegin(); itr30 != (((((*visitedStates)[(*bKeys_pj)[i35]])[(*bKeys_lj)[i34]])[(*bKeys_p1)[i33]]))[(*bKeys_p2)[i32]][(*bKeys_p3)[i31]].rend(); itr30++) {
                                                    
                                                    if (itr30->first < s.sumCs) break;
                                                    else {
                                                        
                                                        for (mt29::iterator itr29 = (itr30->second).begin(); itr29 != (itr30->second).end(); itr29++) {
                                                            if (itr29->first > s.sumSlacks) break;
                                                            else if (find_dominating_state_p_iterations(s, itr29->second)) return true;
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
        
        return false; // no state in map dominates state s
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    void remove_dominated_states_c_iterations(const state& s, mt14& visitedStates14) {
        
        for (mt14::iterator itr14 = visitedStates14.begin(); itr14 != visitedStates14.end();) {
            if (itr14->first > s.c[0]) break;
            else {
                for (mt13::iterator itr13 = (itr14->second).begin(); itr13 != (itr14->second).end();) {
                    if (itr13->first > s.c[1]) break;
                    else {
                        for (mt12::iterator itr12 = (itr13->second).begin(); itr12 != (itr13->second).end();) {
                            if (itr12->first > s.c[2]) break;
                            else {
                                for (mt11::iterator itr11 = (itr12->second).begin(); itr11 != (itr12->second).end();) {
                                    if (itr11->first > s.c[3]) break;
                                    else {
                                        for (mt10::iterator itr10 = (itr11->second).begin(); itr10 != (itr11->second).end();) {
                                            if (itr10->first > s.c[4]) break;
                                            else {
                                                for (mt9::iterator itr9 = (itr10->second).begin(); itr9 != (itr10->second).end();) {
                                                    if (itr9->first > s.c[5]) break;
                                                    else {
                                                        for (mt8::iterator itr8 = (itr9->second).begin(); itr8 != (itr9->second).end();) {
                                                            if (itr8->first > s.c[6]) break;
                                                            else {
                                                                for (mt7::iterator itr7 = (itr8->second).begin(); itr7 != (itr8->second).end();) {
                                                                    if (itr7->first > s.c[7]) break;
                                                                    else {
                                                                        for (mt6::iterator itr6 = (itr7->second).begin(); itr6 != (itr7->second).end();) {
                                                                            if (itr6->first > s.c[8]) break;
                                                                            else {
                                                                                for (mt5::iterator itr5 = (itr6->second).begin(); itr5 != (itr6->second).end();) {
                                                                                    if (itr5->first > s.c[9]) break;
                                                                                    else {
                                                                                        for (mt4::iterator itr4 = (itr5->second).begin(); itr4 != (itr5->second).end();) {
                                                                                            if (itr4->first > s.c[10]) break;
                                                                                            else {
                                                                                                for (mt3::iterator itr3 = (itr4->second).begin(); itr3 != (itr4->second).end();) {
                                                                                                    if (itr3->first > s.c[11]) break;
                                                                                                    else {
                                                                                                        for (mt2::iterator itr2 = (itr3->second).begin(); itr2 != (itr3->second).end();) {
                                                                                                            if (itr2->first > s.c[12]) break;
                                                                                                            else {
                                                                                                                for (mt1::iterator itr1 = (itr2->second).begin(); itr1 != (itr2->second).end();) {
                                                                                                                    if (itr1->first > s.c[13]) break;
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
                                                        if ((itr9->second).empty()) (itr10->second).erase(itr9++);
                                                        else ++itr9;
                                                    }
                                                } // itr9
                                                if ((itr10->second).empty()) (itr11->second).erase(itr10++);
                                                else ++itr10;
                                            }
                                        } // itr10
                                        if ((itr11->second).empty()) (itr12->second).erase(itr11++);
                                        else ++itr11;
                                    }
                                } // itr11
                                if ((itr12->second).empty()) (itr13->second).erase(itr12++);
                                else ++itr12;
                            }
                        } // itr12
                        if ((itr13->second).empty()) (itr14->second).erase(itr13++);
                        else ++itr13;
                    }
                } // itr13
                if ((itr14->second).empty()) (visitedStates14).erase(itr14++);
                else ++itr14;
            }
        } // itr14
        
        return;
    }
    
    
    
    
    
    
    void remove_dominated_states_p_iterations(const state& s, mt28& visitedStates28) {
        
        for (mt28::reverse_iterator itr28 = visitedStates28.rbegin(); itr28 != visitedStates28.rend();) {
            if (itr28->first < s.t[0]) break;
            else {
                for (mt27::reverse_iterator itr27 = (itr28->second).rbegin(); itr27 != (itr28->second).rend();) {
                    if (itr27->first < s.t[1]) break;
                    else {
                        for (mt26::reverse_iterator itr26 = (itr27->second).rbegin(); itr26 != (itr27->second).rend();) {
                            if (itr26->first < s.t[2]) break;
                            else {
                                for (mt25::reverse_iterator itr25 = (itr26->second).rbegin(); itr25 != (itr26->second).rend();) {
                                    if (itr25->first < s.t[3]) break;
                                    else {
                                        for (mt24::reverse_iterator itr24 = (itr25->second).rbegin(); itr24 != (itr25->second).rend();) {
                                            if (itr24->first < s.t[4]) break;
                                            else {
                                                for (mt23::reverse_iterator itr23 = (itr24->second).rbegin(); itr23 != (itr24->second).rend();) {
                                                    if (itr23->first < s.t[5]) break;
                                                    else {
                                                        for (mt22::reverse_iterator itr22 = (itr23->second).rbegin(); itr22 != (itr23->second).rend();) {
                                                            if (itr22->first < s.t[6]) break;
                                                            else {
                                                                for (mt21::reverse_iterator itr21 = (itr22->second).rbegin(); itr21 != (itr22->second).rend();) {
                                                                    if (itr21->first < s.t[7]) break;
                                                                    else {
                                                                        for (mt20::reverse_iterator itr20 = (itr21->second).rbegin(); itr20 != (itr21->second).rend();) {
                                                                            if (itr20->first < s.t[8]) break;
                                                                            else {
                                                                                for (mt19::reverse_iterator itr19 = (itr20->second).rbegin(); itr19 != (itr20->second).rend();) {
                                                                                    if (itr19->first < s.t[9]) break;
                                                                                    else {
                                                                                        for (mt18::reverse_iterator itr18 = (itr19->second).rbegin(); itr18 != (itr19->second).rend();) {
                                                                                            if (itr18->first < s.t[10]) break;
                                                                                            else {
                                                                                                for (mt17::reverse_iterator itr17 = (itr18->second).rbegin(); itr17 != (itr18->second).rend();) {
                                                                                                    if (itr17->first < s.t[11]) break;
                                                                                                    else {
                                                                                                        for (mt16::reverse_iterator itr16 = (itr17->second).rbegin(); itr16 != (itr17->second).rend();) {
                                                                                                            if (itr16->first < s.t[12]) break;
                                                                                                            else {
                                                                                                                for (mt15::reverse_iterator itr15 = (itr16->second).rbegin(); itr15 != (itr16->second).rend();) {
                                                                                                                    if (itr15->first < s.t[13]) break;
                                                                                                                    else {
                                                                                                                        remove_dominated_states_c_iterations(s, (itr15->second));
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
                                                                                                if ((itr18->second).empty()) (itr19->second).erase(--(itr18.base()));
                                                                                                else ++itr18;
                                                                                            }
                                                                                        }
                                                                                        if ((itr19->second).empty()) (itr20->second).erase(--(itr19.base()));
                                                                                        else ++itr19;
                                                                                    }
                                                                                }
                                                                                if ((itr20->second).empty()) (itr21->second).erase(--(itr20.base()));
                                                                                else ++itr20;
                                                                            }
                                                                        }
                                                                        if ((itr21->second).empty()) (itr22->second).erase(--(itr21.base()));
                                                                        else ++itr21;
                                                                    }
                                                                }
                                                                if ((itr22->second).empty()) (itr23->second).erase(--(itr22.base()));
                                                                else ++itr22;
                                                            }
                                                        }
                                                        if ((itr23->second).empty()) (itr24->second).erase(--(itr23.base()));
                                                        else ++itr23;
                                                    }
                                                }
                                                if ((itr24->second).empty()) (itr25->second).erase(--(itr24.base()));
                                                else ++itr24;
                                            }
                                        }
                                        if ((itr25->second).empty()) (itr26->second).erase(--(itr25.base()));
                                        else ++itr25;
                                    }
                                }
                                if ((itr26->second).empty()) (itr27->second).erase(--(itr26.base()));
                                else ++itr26;
                            }
                        }
                        if ((itr27->second).empty()) (itr28->second).erase(--(itr27.base()));
                        else ++itr27;
                    }
                }
                if ((itr28->second).empty()) visitedStates28.erase(--(itr28.base()));
                else ++itr28;
            }
        }
        
        return;
    }
    
    
    
    
    
    void remove_dominated_states(const state& s, mt35* visitedStates) {
        
        unsigned int keysNum_pj2 = 0;
        unsigned int keysNum_lj2 = 0;
        unsigned int keysNum_p1_2 = 0;
        unsigned int keysNum_p2_2 = 0;
        unsigned int keysNum_p3_2 = 0;
        
        
        get_keys_pj2(s, ts.n, keysNum_pj2, bKeys_pj2);
        
        for (int i35 = 0; i35 < keysNum_pj2; i35++) { // pending jobs binary key
            if ((*visitedStates).find((*bKeys_pj2)[i35]) != (*visitedStates).end()) {
                
                get_keys_lj2(s, ts.n, (*bKeys_pj2)[i35], keysNum_lj2, bKeys_lj2);
                
                for (int i34 = 0; i34 < keysNum_lj2; i34++) { // locked jobs binary key
                    
                    if (((*visitedStates)[(*bKeys_pj2)[i35]]).find((*bKeys_lj2)[i34]) != ((*visitedStates)[(*bKeys_pj2)[i35]]).end()) {
                        
                        get_keys_p1_2(s, ts, (*bKeys_lj2)[i34], keysNum_p1_2, bKeys_p1_2);
                        for (int i33 = 0; i33 < keysNum_p1_2; i33++) { // p1 key
                            
                            if (((*visitedStates)[(*bKeys_pj2)[i35]][(*bKeys_lj2)[i34]]).find((*bKeys_p1_2)[i33]) != ((*visitedStates)[(*bKeys_pj2)[i35]][(*bKeys_lj2)[i34]]).end()) {
                                
                                get_keys_p2_2(s, ts, (*bKeys_lj2)[i34], (*bKeys_p1_2)[i33], keysNum_p2_2, bKeys_p2_2);
                                for (int i32 = 0; i32 < keysNum_p2_2; i32++) {
                                    
                                    if (((*visitedStates)[(*bKeys_pj2)[i35]][(*bKeys_lj2)[i34]])[(*bKeys_p1_2)[i33]].find((*bKeys_p2_2)[i32]) != ((*visitedStates)[(*bKeys_pj2)[i35]][(*bKeys_lj2)[i34]])[(*bKeys_p1_2)[i33]].end()) {
                                        
                                        get_keys_p3_2(s, ts, (*bKeys_lj2)[i34], (*bKeys_p1_2)[i33], (*bKeys_p2_2)[i32], keysNum_p3_2, bKeys_p3_2);
                                        for (int i31 = 0; i31 < keysNum_p3_2; i31++) {
                                            
                                            if (((((*visitedStates)[(*bKeys_pj2)[i35]])[(*bKeys_lj2)[i34]])[(*bKeys_p1_2)[i33]])[(*bKeys_p2_2)[i32]].find((*bKeys_p3_2)[i31]) != (((*visitedStates)[(*bKeys_pj2)[i35]])[(*bKeys_lj2)[i34]])[(*bKeys_p1_2)[i33]][(*bKeys_p2_2)[i32]].end()) {
                                                
                                                
                                                for (mt30::iterator itr30 = (((((*visitedStates)[(*bKeys_pj2)[i35]])[(*bKeys_lj2)[i34]])[(*bKeys_p1_2)[i33]]))[(*bKeys_p2_2)[i32]][(*bKeys_p3_2)[i31]].begin(); itr30 != (((((*visitedStates)[(*bKeys_pj2)[i35]])[(*bKeys_lj2)[i34]])[(*bKeys_p1_2)[i33]]))[(*bKeys_p2_2)[i32]][(*bKeys_p3_2)[i31]].end();) {
                                                    
                                                    if (itr30->first > s.sumCs) break;
                                                    else {
                                                        
                                                        for (mt29::reverse_iterator itr29 = (itr30->second).rbegin(); itr29 != (itr30->second).rend();) {
                                                            if (itr29->first < s.sumSlacks) break;
                                                            else remove_dominated_states_p_iterations(s, itr29->second);
                                                            
                                                            if ((itr29->second).empty()) (itr30->second).erase(--(itr29.base()));
                                                            else ++itr29;
                                                        }
                                                        
                                                        if ((itr30->second).empty()) (((((*visitedStates)[(*bKeys_pj2)[i35]])[(*bKeys_lj2)[i34]])[(*bKeys_p1_2)[i33]]))[(*bKeys_p2_2)[i32]][(*bKeys_p3_2)[i31]].erase(itr30++);
                                                        else ++itr30;
                                                    }
                                                }
                                                
                                                if (((((*visitedStates)[(*bKeys_pj2)[i35]])[(*bKeys_lj2)[i34]])[(*bKeys_p1_2)[i33]])[(*bKeys_p2_2)[i32]][(*bKeys_p3_2)[i31]].empty()) (((*visitedStates)[(*bKeys_pj2)[i35]])[(*bKeys_lj2)[i34]])[(*bKeys_p1_2)[i33]][(*bKeys_p2_2)[i32]].erase((*bKeys_p3_2)[i31]);
                                            }
                                        }
                                        
                                        if (((((*visitedStates)[(*bKeys_pj2)[i35]])[(*bKeys_lj2)[i34]])[(*bKeys_p1_2)[i33]])[(*bKeys_p2_2)[i32]].empty()) (((*visitedStates)[(*bKeys_pj2)[i35]])[(*bKeys_lj2)[i34]])[(*bKeys_p1_2)[i33]].erase((*bKeys_p2_2)[i32]);
                                    }
                                }
                                
                                if (((((*visitedStates)[(*bKeys_pj2)[i35]])[(*bKeys_lj2)[i34]])[(*bKeys_p1_2)[i33]]).empty()) (((*visitedStates)[(*bKeys_pj2)[i35]])[(*bKeys_lj2)[i34]]).erase((*bKeys_p1_2)[i33]);
                            }
                        }
                        
                        if ((((*visitedStates)[(*bKeys_pj2)[i35]])[(*bKeys_lj2)[i34]]).empty()) ((*visitedStates)[(*bKeys_pj2)[i35]]).erase((*bKeys_lj2)[i34]);
                    }
                }
                
                if ((((*visitedStates)[(*bKeys_pj2)[i35]])).empty()) (*visitedStates).erase((*bKeys_pj2)[i35]);
            }
        }
        
        return;
    }
    
    
    
    
    
    
    
    void add_state_to_map(const state& s, mt35* visitedStates) {

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

        my_bitset bs_p3;
        for (unsigned short i = 0; i < ts.n; i++) {
            if ((s.t[i] <= ((float)(ts.T[i]))/8)) bs_p3.set(i, 0);
            else if ((s.t[i] > ((float)(2*ts.T[i]))/8)&&(s.t[i] <= ((float)(3*ts.T[i]))/8)) bs_p3.set(i, 0);
            else if ((s.t[i] > ((float)(4*ts.T[i]))/8)&&(s.t[i] <= ((float)(5*ts.T[i]))/8)) bs_p3.set(i, 0);
            else if ((s.t[i] > ((float)(6*ts.T[i]))/8)&&(s.t[i] <= ((float)(7*ts.T[i]))/8)) bs_p3.set(i, 0);
            else bs_p3.set(i, 1);
        }
        
        // add state s to map
        (*visitedStates)[bs_pj][bs_lj][bs_p1][bs_p2][bs_p3][s.sumCs][s.sumSlacks][s.t[0]][s.t[1]][s.t[2]][s.t[3]][s.t[4]][s.t[5]][s.t[6]][s.t[7]][s.t[8]][s.t[9]][s.t[10]][s.t[11]][s.t[12]][s.t[13]][s.c[0]][s.c[1]][s.c[2]][s.c[3]][s.c[4]][s.c[5]][s.c[6]][s.c[7]][s.c[8]][s.c[9]][s.c[10]][s.c[11]][s.c[12]][s.c[13]] = true;
    }
    
    
    
    
    
    
    bool update_map(const state& s, mt35* visitedStates, const bool removeStates) {
        
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
        bKeys_p3 = new vector<my_bitset>(pow(2.0, ts.n));
        bKeys_lj = new vector<my_bitset>(pow(2.0, ts.n));
        bKeys_pj2 = new vector<my_bitset>(pow(2.0, ts.n));
        bKeys_p1_2 = new vector<my_bitset>(pow(2.0, ts.n));
        bKeys_p2_2 = new vector<my_bitset>(pow(2.0, ts.n));
        bKeys_p3_2 = new vector<my_bitset>(pow(2.0, ts.n));
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
        mt35* generated = new mt35;
        
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
        delete bKeys_p1;
        delete bKeys_p2;
        delete bKeys_p3;
        delete bKeys_lj;
        delete bKeys_pj2;
        delete bKeys_p1_2;
        delete bKeys_p2_2;
        delete bKeys_p3_2;
        delete bKeys_lj2;
        
        
        if (verbose) {
            cout << endl << "P3 version: " << endl;
            cout << "Saved states:\t\t" << savedStatesNum << endl;
            if (savedStatesNum > 0) cout << "Saved states with tau_14 pending: " << savedStatesNum_tauKpending << "  ( " << (float)((int)(savedStatesNum_tauKpending*10000/savedStatesNum))/100 << " %)" << endl;
            cout << "Visited states:\t\t" << visitedStatesNum << endl;
            cout << "Visited states with tau_14 pending: " << visitedStatesNum_withTauKpending << "  ( " << (float)((int)(visitedStatesNum_withTauKpending*10000/visitedStatesNum))/100 << " %)" << endl << endl;
        }
        
        return schedulable;
    }
} // end of namespace NS_14tasks_p3





bool test_14th_task_p3(const bool verbose_, const unsigned short m_, const TS& ts_, const bool removeStates_, unsigned long int& savedStatesNum_, unsigned long int& visitedStatesNum_) {
    
    NS_14tasks_p3::verbose = verbose_;
    
    bool schedulable = NS_14tasks_p3::populate(m_, ts_, removeStates_);
    savedStatesNum_ = NS_14tasks_p3::savedStatesNum;
    visitedStatesNum_ = NS_14tasks_p3::visitedStatesNum;
    
    return schedulable;
}
