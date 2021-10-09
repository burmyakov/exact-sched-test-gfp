#include <bitset>
#include <vector>
#include <cmath>
#include "custom_types/ts.h"
#include "custom_types/state.h"
#include "custom_types/my_types.h"



void get_keys_pj(const state& s, const unsigned short m, unsigned int& keysNum, vector<my_bitset>* bKeys_pj) {

    keysNum = 0;
    unsigned short curKeysNum = 0;
    
    // i = 0
    if (s.c[0] > 0) {
        (*bKeys_pj)[0].reset(); (*bKeys_pj)[0].set(0, 1);
        keysNum = 1;
    }
    else {
        (*bKeys_pj)[0].reset(); //(*bKeys_pj)[0].set(0, 0);
        //(*bKeys_pj)[1].reset(); (*bKeys_pj)[1].set(0, 1);
        keysNum = 1;
    }
    
    // 0 < i < m
    for (int i = 1; i < m; i++) {
        curKeysNum = keysNum;
        
        if (s.c[i] > 0) {
            for (int j = 0; j < curKeysNum; j++) {
                (*bKeys_pj)[j].set(i, 1);
            }
        } else {
            // s.c[i] == 0
            for (int j = 0; j < curKeysNum; j++) {
                (*bKeys_pj)[j].set(i, 0);
                
                //(*bKeys_pj)[keysNum] = (*bKeys_pj)[j];
                //(*bKeys_pj)[keysNum].set(i, 1);
                //keysNum++;
            }
        }
    }
    
    // i >= m
    for (int i = m; i < s.n; i++) {
        curKeysNum = keysNum;
        
        if (s.c[i] > 0) {
            for (int j = 0; j < curKeysNum; j++) {
                (*bKeys_pj)[j].set(i, 1);
            }
        } else {
            // s.c[i] == 0
            for (int j = 0; j < curKeysNum; j++) {
                //(*bKeys_pj)[j].set(i, 0);
                
                (*bKeys_pj)[keysNum] = (*bKeys_pj)[j];
                (*bKeys_pj)[keysNum].set(i, 1);
                keysNum++;
            }
        }
    }

    return;
}
