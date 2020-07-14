#include <bitset>
#include <vector>
#include <cmath>
#include "custom_types/ts.h"
#include "custom_types/state.h"
#include "custom_types/my_types.h"



void get_keys_pj(const state& s, const unsigned short N, unsigned int& keysNum, vector<my_bitset>* bKeys_pj) {
    
    keysNum = 0;
    unsigned short curKeysNum = 0;
    
    // i = 0
    if (s.c[0] > 0) {
        (*bKeys_pj)[0].reset(); (*bKeys_pj)[0].set(0, 1);
        keysNum = 1;
    }
    else {
        (*bKeys_pj)[0].reset(); //(*bKeys_pj)[0].set(0, 0);
        (*bKeys_pj)[1].reset(); (*bKeys_pj)[1].set(0, 1);
        keysNum = 2;
    }
    
    // i > 0
    for (int i = 1; i < N; i++) {
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






void get_keys_pj2(const state& s, const unsigned short N, unsigned int& keysNum, vector<my_bitset>* bKeys_pj2) {
    
    keysNum = 0;
    unsigned short curKeysNum = 0;
    
    // i == 0
    if (s.c[0] == 0) {
        (*bKeys_pj2)[0].reset(); //(*bKeys_pj2)[0].set(0, 0);
        keysNum = 1;
    }
    else {
        (*bKeys_pj2)[0].reset(); (*bKeys_pj2)[0].set(0, 1);
        (*bKeys_pj2)[1].reset(); //(*bKeys_pj2)[1].set(0, 0);
        keysNum = 2;
    }
    
    // i > 0
    for (unsigned short int i = 1; i < N; i++) {
        curKeysNum = keysNum;
        
        /*if (s.c[i] == 0) {
            for (unsigned short int j = 0; j < curKeysNum; j++) {
                (*bKeys_pj2)[j].set(i, 0);
            }
        } else {*/
        if (s.c[i] > 0) {
            for (unsigned short int j = 0; j < curKeysNum; j++) {
                //(*bKeys_pj2)[j].set(i, 0);
                
                (*bKeys_pj2)[keysNum] = (*bKeys_pj2)[j];
                (*bKeys_pj2)[keysNum].set(i, 1);
                keysNum++;
            }
        }
    }

    return;
}





void get_keys_lj(const state& s, const unsigned short N, const my_bitset bKey_pj, unsigned int& keysNum, vector<my_bitset>* bKeys_lj) {
    
    keysNum = 0;
    unsigned int curKeysNum = 0;
    
    // for i = 0
    if (bKey_pj[0] == 1) {
        (*bKeys_lj)[0].reset(); (*bKeys_lj)[0].set(0, 1);
        keysNum = 1;
    } else if (s.p[0] == 0) {
        (*bKeys_lj)[0].reset(); //(*bKeys_lj)[0].set(0, 0);
        keysNum = 1;
    } else {
        (*bKeys_lj)[0].reset(); (*bKeys_lj)[0].set(0, 1);
        (*bKeys_lj)[1].reset(); //(*bKeys_lj)[1].set(0, 0);
        keysNum = 2;
    }
    
    
    // i > 0
    for (int i = 1; i < N; i++) {
        curKeysNum = keysNum;
        
        if (bKey_pj[i] == 1)
            for (int j = 0; j < curKeysNum; j++)
                (*bKeys_lj)[j].set(i, 1);
        else if (s.p[i] == 0) {
            /*for (int j = 0; j < curKeysNum; j++)
                (*bKeys_lj)[j].set(i, 0);*/
        } else
            for (int j = 0; j < curKeysNum; j++) {
                //(*bKeys_lj)[j].set(i, 0);
                
                (*bKeys_lj)[keysNum] = (*bKeys_lj)[j];
                (*bKeys_lj)[keysNum].set(i, 1);
                keysNum++;
            }
    }
    
    return;
}




void get_keys_lj2(const state& s, const unsigned short N, const my_bitset bKey_pj2, unsigned int& keysNum, vector<my_bitset>* bKeys_lj2) {
    
    keysNum = 0;
    unsigned int curKeysNum = 0;
    
    // for i = 0
    if (bKey_pj2[0] == 1) {
        (*bKeys_lj2)[0].reset(); (*bKeys_lj2)[0].set(0, 1);
        keysNum = 1;
    } else if (s.p[0] > 0) {
        (*bKeys_lj2)[0].reset(); (*bKeys_lj2)[0].set(0, 1);
        keysNum = 1;
    } else {
        (*bKeys_lj2)[0].reset(); //(*bKeys_lj2)[0].set(0, 0);
        (*bKeys_lj2)[1].reset(); (*bKeys_lj2)[1].set(0, 1);
        keysNum = 2;
    }
    
    // i > 0
    for (int i = 0; i < N; i++) {
        curKeysNum = keysNum;
        
        if (bKey_pj2[i] == 1)
            for (int j = 0; j < curKeysNum; j++)
                (*bKeys_lj2)[j].set(i, 1);
        else if (s.p[i] > 0)
            for (int j = 0; j < curKeysNum; j++)
                (*bKeys_lj2)[j].set(i, 1);
        else
            for (int j = 0; j < curKeysNum; j++) {
                //(*bKeys_lj2)[j].set(i, 0);
                
                (*bKeys_lj2)[keysNum] = (*bKeys_lj2)[j];
                (*bKeys_lj2)[keysNum].set(i, 1);
                keysNum++;
            }
    }
    
    return;
}






void get_keys_p1(const state& s, const TS& ts, const my_bitset bKey_lj, unsigned int& keysNum, vector<my_bitset>* bKeys_p1) {
    
    keysNum = 0;
    unsigned short int curKeysNum = 0;
    
    // i == 0
    if (bKey_lj[0] == 0) {
        (*bKeys_p1)[0].reset(); //(*bKeys_p1)[0].set(0, 0);
        keysNum = 1;
    } else if (s.p[0] <= ((float)(ts.P[0]))/2) {
        (*bKeys_p1)[0].reset(); //(*bKeys_p1)[0].set(0, 0);
        keysNum = 1;
    } else {
        (*bKeys_p1)[0].reset(); //(*bKeys_p1)[0].set(0, 0);
        (*bKeys_p1)[1].reset(); (*bKeys_p1)[1].set(0, 1);
        keysNum = 2;
    }
    
    // i > 0
    for (unsigned short int i = 1; i < ts.n; i++) {
        curKeysNum = keysNum;
        
        if (bKey_lj[i] == 0) {
            /*for (unsigned short int j = 0; j < curKeysNum; j++) {
                (*bKeys_p1)[j].set(i, 0);
            }*/
        } else if (s.p[i] <= ((float)(ts.P[i]))/2) {
            /*for (unsigned short int j = 0; j < curKeysNum; j++) {
                (*bKeys_p1)[j].set(i, 0);
            }*/
        } else {
            for (unsigned short int j = 0; j < curKeysNum; j++) {
                //(*bKeys_p1)[j].set(i, 0);
                
                (*bKeys_p1)[keysNum] = (*bKeys_p1)[j];
                (*bKeys_p1)[keysNum].set(i, 1);
                keysNum++;
            }
        }
    }
    
    return;
}





void get_keys_p2(const state& s, const TS& ts, const my_bitset bKey_lj, const my_bitset bKey_p1, unsigned int& keysNum, vector<my_bitset>* bKeys_p2) {
    
    keysNum = 0;
    unsigned short curKeysNum = 0;
    
    // i == 0
    (*bKeys_p2)[0].reset();
    (*bKeys_p2)[1].reset();
    
    if (bKey_lj[0] == 0) {
        //(*bKeys_p2)[0].set(0, 0);
        keysNum = 1;
    } else if (bKey_p1[0] == 0) {
        if (s.p[0] <= ((float)(ts.P[0]))/4) {
            //(*bKeys_p2)[0].set(0, 0);
            keysNum = 1;
        } else {
            //(*bKeys_p2)[0].set(0, 0);
            (*bKeys_p2)[1].set(0, 1);
            keysNum = 2;
        }
    } else { // case of (bKey_lj[0] == 1)
        if (s.p[0] <= ((float)(3*ts.P[0]))/4) {
            //(*bKeys_p2)[0].set(0, 0);
            keysNum = 1;
        } else {
            //(*bKeys_p2)[0].set(0, 0);
            (*bKeys_p2)[1].set(0, 1);
            keysNum = 2;
        }
    }
    
    // i > 0
    for (unsigned short i = 1; i < ts.n; i++) {
        curKeysNum = keysNum;
        
        if (bKey_lj[i] == 0) {
            /*for (unsigned short j = 0; j < curKeysNum; j++) {
                (*bKeys_p2)[j].set(i, 0);
            }*/
        } else if (bKey_p1[i] == 0) {
            if (s.p[i] <= ((float)(ts.P[i]))/4) {
                /*for (unsigned short j = 0; j < curKeysNum; j++) {
                    (*bKeys_p2)[j].set(i, 0);
                }*/
            } else {
                for (unsigned short j = 0; j < curKeysNum; j++) {
                    //(*bKeys_p2)[j].set(i, 0);
                    (*bKeys_p2)[keysNum] = (*bKeys_p2)[j];
                    (*bKeys_p2)[keysNum].set(i, 1);
                    keysNum++;
                }
            }
        } else { // bKey_p1[i] == 1
            if (s.p[i] <= ((float)(3*ts.P[i]))/4) {
                /*for (unsigned short j = 0; j < curKeysNum; j++) {
                    (*bKeys_p2)[j].set(i, 0);
                 }*/
            } else {
                for (unsigned short j = 0; j < curKeysNum; j++) {
                    //(*bKeys_p2)[j].set(i, 0);
                    
                    (*bKeys_p2)[keysNum] = (*bKeys_p2)[j];
                    (*bKeys_p2)[keysNum].set(i, 1);
                    keysNum++;
                }
            }
        }
    }
    
    return;
}







void get_keys_p3(const state& s, const TS& ts, const my_bitset bKey_lj, const my_bitset bKey_p1, const my_bitset bKey_p2, unsigned int& keysNum, vector<my_bitset>* bKeys_p3) {
    
    keysNum = 0;
    unsigned short curKeysNum = 0;
    
    // i == 0
    (*bKeys_p3)[0].reset();
    (*bKeys_p3)[1].reset();
    
    if (bKey_lj[0] == 0) {
        //(*bKeys_p3)[0].set(0, 0);
        keysNum = 1;
    } else if (bKey_p1[0] == 0) {
        
        if (bKey_p2[0] == 0) {
            if (s.p[0] <= ((float)(ts.P[0]))/8) {
                //(*bKeys_p3)[0].set(0, 0);
                keysNum = 1;
            } else {
                //(*bKeys_p3)[0].set(0, 0);
                (*bKeys_p3)[1].set(0, 1);
                keysNum = 2;
            }
        } else {
            if (s.p[0] <= ((float)(3*ts.P[0]))/8) {
                //(*bKeys_p3)[0].set(0, 0);
                keysNum = 1;
            } else {
                //(*bKeys_p3)[0].set(0, 0);
                (*bKeys_p3)[1].set(0, 1);
                keysNum = 2;
            }
        }
        
    } else { // bKey_p1[0] == 1
        
        if (bKey_p2[0] == 0) {
            if (s.p[0] <= ((float)(5*ts.P[0]))/8) {
                //(*bKeys_p3)[0].set(0, 0);
                keysNum = 1;
            } else {
                //(*bKeys_p3)[0].set(0, 0);
                (*bKeys_p3)[1].set(0, 1);
                keysNum = 2;
            }
        } else {
            if (s.p[0] <= ((float)(7*ts.P[0]))/8) {
                //(*bKeys_p3)[0].set(0, 0);
                keysNum = 1;
            } else {
                //(*bKeys_p3)[0].set(0, 0);
                (*bKeys_p3)[1].set(0, 1);
                keysNum = 2;
            }
        }
    }
    
    // i > 0
    for (unsigned short i = 1; i < ts.n; i++) {
        curKeysNum = keysNum;
        
        if (bKey_lj[i] == 0) {
            /*for (unsigned short j = 0; j < curKeysNum; j++) {
             (*bKeys_p2)[j].set(i, 0);
             }*/
        } else if (bKey_p1[i] == 0) {
            
            if (bKey_p2[i] == 0) {
                
                if (s.p[i] <= ((float)(1*ts.P[i]))/8) {
                    //for (unsigned short j = 0; j < curKeysNum; j++) (*bKeys_p3)[i].set(i, 0);
                } else {
                    for (unsigned short j = 0; j < curKeysNum; j++) {
                        //(*bKeys_p3)[j].set(i, 0);
                        (*bKeys_p3)[keysNum] = (*bKeys_p3)[j];
                        (*bKeys_p3)[keysNum].set(i, 1);
                        keysNum++;
                    }
                }
            } else {
                
                if (s.p[i] <= ((float)(3*ts.P[i]))/8) {
                    //for (unsigned short j = 0; j < curKeysNum; j++) (*bKeys_p3)[i].set(i, 0);
                } else {
                    for (unsigned short j = 0; j < curKeysNum; j++) {
                        //(*bKeys_p3)[j].set(i, 0);
                        (*bKeys_p3)[keysNum] = (*bKeys_p3)[j];
                        (*bKeys_p3)[keysNum].set(i, 1);
                        keysNum++;
                    }
                }
            }

        } else { // bKey_p1[i] == 1
            
            if (bKey_p2[i] == 0) {
                if (s.p[i] <= ((float)(5*ts.P[i]))/8) {
                    //(*bKeys_p3)[i].set(i, 0);
                } else {
                    for (unsigned short j = 0; j < curKeysNum; j++) {
                        //(*bKeys_p3)[j].set(i, 0);
                        (*bKeys_p3)[keysNum] = (*bKeys_p3)[j];
                        (*bKeys_p3)[keysNum].set(i, 1);
                        keysNum++;
                    }
                }
            } else {
                if (s.p[i] <= ((float)(7*ts.P[i]))/8) {
                    //for (unsigned short j = 0; j < curKeysNum; j++) (*bKeys_p3)[i].set(i, 0);
                } else {
                    for (unsigned short j = 0; j < curKeysNum; j++) {
                        //(*bKeys_p3)[j].set(i, 0);
                        (*bKeys_p3)[keysNum] = (*bKeys_p3)[j];
                        (*bKeys_p3)[keysNum].set(i, 1);
                        keysNum++;
                    }
                }
            }
        }
    }
    
    return;
}












/*void get_keys_p4(const state& s, const TS& ts, const my_bitset bKey_lj, const my_bitset bKey_p1, const my_bitset bKey_p2, const my_bitset bKey_p3, unsigned int& keysNum, vector<my_bitset>* bKeys_p4) {
    
    keysNum = 0;
    unsigned short curKeysNum = 0;
    
    // i == 0
    (*bKeys_p4)[0].reset();
    (*bKeys_p4)[1].reset();
    
    if (bKey_lj[0] == 0) {
        //(*bKeys_p4)[0].set(0, 0);
        keysNum = 1;
    } else if (bKey_p1[0] == 0) {
        
        if (bKey_p2[0] == 0) {
            if (bKey_p3[0] == 0) {
                if (s.t[0] <= ((float)(1*ts.T[0]))/16) {
                    //(*bKeys_p4)[0].set(0, 0);
                    keysNum = 1;
                } else {
                    //(*bKeys_p4)[0].set(0, 0);
                    (*bKeys_p4)[1].set(0, 1);
                    keysNum = 2;
                }
            } else { // bKey_p3[0] == 1
                if (s.t[0] <= ((float)(3*ts.T[0]))/16) {
                    //(*bKeys_p4)[0].set(0, 0);
                    keysNum = 1;
                } else {
                    //(*bKeys_p4)[0].set(0, 0);
                    (*bKeys_p4)[1].set(0, 1);
                    keysNum = 2;
                }
            }
        } else { // bKey_p2[0] == 0
            if (bKey_p3[0] == 0) {
                if (s.t[0] <= ((float)(5*ts.T[0]))/16) {
                    //(*bKeys_p4)[0].set(0, 0);
                    keysNum = 1;
                } else {
                    //(*bKeys_p4)[0].set(0, 0);
                    (*bKeys_p4)[1].set(0, 1);
                    keysNum = 2;
                }
            } else { // bKey_p3[0] == 1
                if (s.t[0] <= ((float)(7*ts.T[0]))/16) {
                    //(*bKeys_p4)[0].set(0, 0);
                    keysNum = 1;
                } else {
                    //(*bKeys_p4)[0].set(0, 0);
                    (*bKeys_p4)[1].set(0, 1);
                    keysNum = 2;
                }
            }
        }
        
    } else { // bKey_p1[0] == 1
        
        if (bKey_p2[0] == 0) {
            if (bKey_p3[0] == 0) {
                if (s.t[0] <= ((float)(9*ts.T[0]))/16) {
                    //(*bKeys_p4)[0].set(0, 0);
                    keysNum = 1;
                } else {
                    //(*bKeys_p4)[0].set(0, 0);
                    (*bKeys_p4)[1].set(0, 1);
                    keysNum = 2;
                }
            } else { // bKey_p3[0] == 1
                if (s.t[0] <= ((float)(11*ts.T[0]))/16) {
                    //(*bKeys_p4)[0].set(0, 0);
                    keysNum = 1;
                } else {
                    //(*bKeys_p4)[0].set(0, 0);
                    (*bKeys_p4)[1].set(0, 1);
                    keysNum = 2;
                }
            }
        } else { // bKey_p2[0] == 1
            if (bKey_p3[0] == 0) {
                if (s.t[0] <= ((float)(13*ts.T[0]))/16) {
                    //(*bKeys_p4)[0].set(0, 0);
                    keysNum = 1;
                } else {
                    //(*bKeys_p4)[0].set(0, 0);
                    (*bKeys_p4)[1].set(0, 1);
                    keysNum = 2;
                }
            } else { // bKey_p3[0] == 1
                if (s.t[0] <= ((float)(15*ts.T[0]))/16) {
                    //(*bKeys_p4)[0].set(0, 0);
                    keysNum = 1;
                } else {
                    //(*bKeys_p4)[0].set(0, 0);
                    (*bKeys_p4)[1].set(0, 1);
                    keysNum = 2;
                }
            }
        }
    }
    
    // i > 0
    for (unsigned short i = 1; i < ts.n; i++) {
        curKeysNum = keysNum;
        
        if (bKey_lj[i] == 0) {
            //for (unsigned short j = 0; j < curKeysNum; j++) {
            // (*bKeys_p2)[j].set(i, 0);
            // }
        } else if (bKey_p1[i] == 0) {
            if (bKey_p2[i] == 0) {
                
                if (bKey_p3[i] == 0) {
                    if (s.t[i] <= ((float)(1*ts.T[i]))/16) {
                        //for (unsigned short j = 0; j < curKeysNum; j++) (*bKeys_p4)[j].set(i, 0);
                    } else {
                        for (unsigned short j = 0; j < curKeysNum; j++) {
                            //(*bKeys_p4)[j].set(i, 0);
                            (*bKeys_p4)[keysNum] = (*bKeys_p4)[j];
                            (*bKeys_p4)[keysNum].set(i, 1);
                            keysNum++;
                        }
                    }
                } else { // bKey_p3[0] == 1
                    if (s.t[i] <= ((float)(3*ts.T[i]))/16) {
                        //for (unsigned short j = 0; j < curKeysNum; j++) (*bKeys_p4)[j].set(i, 0);
                    } else {
                        for (unsigned short j = 0; j < curKeysNum; j++) {
                            //(*bKeys_p4)[j].set(i, 0);
                            (*bKeys_p4)[keysNum] = (*bKeys_p4)[j];
                            (*bKeys_p4)[keysNum].set(i, 1);
                            keysNum++;
                        }
                    }
                }

            } else {
                
                if (bKey_p3[i] == 0) {
                    if (s.t[i] <= ((float)(5*ts.T[i]))/16) {
                        //for (unsigned short j = 0; j < curKeysNum; j++) (*bKeys_p4)[j].set(i, 0);
                    } else {
                        for (unsigned short j = 0; j < curKeysNum; j++) {
                            //(*bKeys_p4)[j].set(i, 0);
                            (*bKeys_p4)[keysNum] = (*bKeys_p4)[j];
                            (*bKeys_p4)[keysNum].set(i, 1);
                            keysNum++;
                        }
                    }
                } else { // bKey_p3[0] == 1
                    if (s.t[i] <= ((float)(7*ts.T[i]))/16) {
                        //for (unsigned short j = 0; j < curKeysNum; j++) (*bKeys_p4)[j].set(i, 0);
                    } else {
                        for (unsigned short j = 0; j < curKeysNum; j++) {
                            //(*bKeys_p4)[j].set(i, 0);
                            (*bKeys_p4)[keysNum] = (*bKeys_p4)[j];
                            (*bKeys_p4)[keysNum].set(i, 1);
                            keysNum++;
                        }
                    }
                }
            }
            
        } else { // bKey_p1[i] == 1
            
            if (bKey_p2[i] == 0) {
                
                if (bKey_p3[i] == 0) {
                    if (s.t[i] <= ((float)(9*ts.T[i]))/16) {
                        //for (unsigned short j = 0; j < curKeysNum; j++) (*bKeys_p4)[j].set(i, 0);
                    } else {
                        for (unsigned short j = 0; j < curKeysNum; j++) {
                            //(*bKeys_p4)[j].set(i, 0);
                            (*bKeys_p4)[keysNum] = (*bKeys_p4)[j];
                            (*bKeys_p4)[keysNum].set(i, 1);
                            keysNum++;
                        }
                    }
                } else { // bKey_p3[0] == 1
                    if (s.t[i] <= ((float)(11*ts.T[i]))/16) {
                        //for (unsigned short j = 0; j < curKeysNum; j++) (*bKeys_p4)[j].set(i, 0);
                    } else {
                        for (unsigned short j = 0; j < curKeysNum; j++) {
                            //(*bKeys_p4)[j].set(i, 0);
                            (*bKeys_p4)[keysNum] = (*bKeys_p4)[j];
                            (*bKeys_p4)[keysNum].set(i, 1);
                            keysNum++;
                        }
                    }
                }
                
            } else {
                
                if (bKey_p3[i] == 0) {
                    if (s.t[i] <= ((float)(13*ts.T[i]))/16) {
                        //for (unsigned short j = 0; j < curKeysNum; j++) (*bKeys_p4)[j].set(i, 0);
                    } else {
                        for (unsigned short j = 0; j < curKeysNum; j++) {
                            //(*bKeys_p4)[j].set(i, 0);
                            (*bKeys_p4)[keysNum] = (*bKeys_p4)[j];
                            (*bKeys_p4)[keysNum].set(i, 1);
                            keysNum++;
                        }
                    }
                } else { // bKey_p3[0] == 1
                    if (s.t[i] <= ((float)(15*ts.T[i]))/16) {
                        //for (unsigned short j = 0; j < curKeysNum; j++) (*bKeys_p4)[j].set(i, 0);
                    } else {
                        for (unsigned short j = 0; j < curKeysNum; j++) {
                            //(*bKeys_p4)[j].set(i, 0);
                            (*bKeys_p4)[keysNum] = (*bKeys_p4)[j];
                            (*bKeys_p4)[keysNum].set(i, 1);
                            keysNum++;
                        }
                    }
                }
            }
        }
    }
    
    return;
}*/








/*void get_keys_p4_2(const state& s, const TS& ts, const my_bitset bKey_lj2, const my_bitset bKey_p1_2, const my_bitset bKey_p2_2, const my_bitset bKey_p3_2, unsigned int& keysNum, vector<my_bitset>* bKeys_p4_2) {
    
    keysNum = 0;
    unsigned short curKeysNum = 0;
    
    // i == 0
    (*bKeys_p4_2)[0].reset();
    (*bKeys_p4_2)[1].reset();
    
    if (bKey_lj2[0] == 0) {
        //(*bKeys_p4_2)[0].set(0, 0);
        keysNum = 1;
    } else if (bKey_p1_2[0] == 0) {
        
        if (bKey_p2_2[0] == 0) {
            if (bKey_p3_2[0] == 0) {
                if (s.t[0] > ((float)(1*ts.T[0]))/16) {
                    (*bKeys_p4_2)[0].set(0, 1);
                    keysNum = 1;
                } else {
                    //(*bKeys_p4_2)[0].set(0, 0);
                    (*bKeys_p4_2)[1].set(0, 1);
                    keysNum = 2;
                }
            } else { // bKey_p3[0] == 1
                if (s.t[0] > ((float)(3*ts.T[0]))/16) {
                    (*bKeys_p4_2)[0].set(0, 1);
                    keysNum = 1;
                } else {
                    //(*bKeys_p4_2)[0].set(0, 0);
                    (*bKeys_p4_2)[1].set(0, 1);
                    keysNum = 2;
                }
            }
        } else { // bKey_p2_2[0] == 0
            if (bKey_p3_2[0] == 0) {
                if (s.t[0] > ((float)(5*ts.T[0]))/16) {
                    (*bKeys_p4_2)[0].set(0, 1);
                    keysNum = 1;
                } else {
                    //(*bKeys_p4_2)[0].set(0, 0);
                    (*bKeys_p4_2)[1].set(0, 1);
                    keysNum = 2;
                }
            } else { // bKey_p3[0] == 1
                if (s.t[0] > ((float)(7*ts.T[0]))/16) {
                    (*bKeys_p4_2)[0].set(0, 1);
                    keysNum = 1;
                } else {
                    //(*bKeys_p4_2)[0].set(0, 0);
                    (*bKeys_p4_2)[1].set(0, 1);
                    keysNum = 2;
                }
            }
        }
        
    } else { // bKey_p1_2[0] == 1
        
        if (bKey_p2_2[0] == 0) {
            if (bKey_p3_2[0] == 0) {
                if (s.t[0] > ((float)(9*ts.T[0]))/16) {
                    (*bKeys_p4_2)[0].set(0, 1);
                    keysNum = 1;
                } else {
                    //(*bKeys_p4_2)[0].set(0, 0);
                    (*bKeys_p4_2)[1].set(0, 1);
                    keysNum = 2;
                }
            } else { // bKey_p3[0] == 1
                if (s.t[0] > ((float)(11*ts.T[0]))/16) {
                    (*bKeys_p4_2)[0].set(0, 1);
                    keysNum = 1;
                } else {
                    //(*bKeys_p4_2)[0].set(0, 0);
                    (*bKeys_p4_2)[1].set(0, 1);
                    keysNum = 2;
                }
            }
        } else { // bKey_p2_2[0] == 1
            if (bKey_p3_2[0] == 0) {
                if (s.t[0] > ((float)(13*ts.T[0]))/16) {
                    (*bKeys_p4_2)[0].set(0, 1);
                    keysNum = 1;
                } else {
                    //(*bKeys_p4_2)[0].set(0, 0);
                    (*bKeys_p4_2)[1].set(0, 1);
                    keysNum = 2;
                }
            } else { // bKey_p3[0] == 1
                if (s.t[0] > ((float)(15*ts.T[0]))/16) {
                    (*bKeys_p4_2)[0].set(0, 1);
                    keysNum = 1;
                } else {
                    //(*bKeys_p4_2)[0].set(0, 0);
                    (*bKeys_p4_2)[1].set(0, 1);
                    keysNum = 2;
                }
            }
        }
    }
    
    // i > 0
    for (unsigned short i = 1; i < ts.n; i++) {
        curKeysNum = keysNum;
        
        if (bKey_lj2[i] == 0) {
            //for (unsigned short j = 0; j < curKeysNum; j++) {
             //(*bKeys_p2_2)[j].set(i, 0);
             //}
        } else if (bKey_p1_2[i] == 0) {
            if (bKey_p2_2[i] == 0) {
                
                if (bKey_p3_2[i] == 0) {
                    if (s.t[i] > ((float)(1*ts.T[i]))/16) {
                        for (unsigned short j = 0; j < curKeysNum; j++) (*bKeys_p4_2)[j].set(i, 1);
                    } else {
                        for (unsigned short j = 0; j < curKeysNum; j++) {
                            //(*bKeys_p4_2)[j].set(i, 0);
                            (*bKeys_p4_2)[keysNum] = (*bKeys_p4_2)[j];
                            (*bKeys_p4_2)[keysNum].set(i, 1);
                            keysNum++;
                        }
                    }
                } else { // bKey_p3[0] == 1
                    if (s.t[i] > ((float)(3*ts.T[i]))/16) {
                        for (unsigned short j = 0; j < curKeysNum; j++) (*bKeys_p4_2)[j].set(i, 1);
                    } else {
                        for (unsigned short j = 0; j < curKeysNum; j++) {
                            //(*bKeys_p4_2)[j].set(i, 0);
                            (*bKeys_p4_2)[keysNum] = (*bKeys_p4_2)[j];
                            (*bKeys_p4_2)[keysNum].set(i, 1);
                            keysNum++;
                        }
                    }
                }
                
            } else {
                
                if (bKey_p3_2[i] == 0) {
                    if (s.t[i] > ((float)(5*ts.T[i]))/16) {
                        for (unsigned short j = 0; j < curKeysNum; j++) (*bKeys_p4_2)[j].set(i, 1);
                    } else {
                        for (unsigned short j = 0; j < curKeysNum; j++) {
                            //(*bKeys_p4_2)[j].set(i, 0);
                            (*bKeys_p4_2)[keysNum] = (*bKeys_p4_2)[j];
                            (*bKeys_p4_2)[keysNum].set(i, 1);
                            keysNum++;
                        }
                    }
                } else { // bKey_p3[0] == 1
                    if (s.t[i] > ((float)(7*ts.T[i]))/16) {
                        for (unsigned short j = 0; j < curKeysNum; j++) (*bKeys_p4_2)[j].set(i, 1);
                    } else {
                        for (unsigned short j = 0; j < curKeysNum; j++) {
                            //(*bKeys_p4_2)[j].set(i, 0);
                            (*bKeys_p4_2)[keysNum] = (*bKeys_p4_2)[j];
                            (*bKeys_p4_2)[keysNum].set(i, 1);
                            keysNum++;
                        }
                    }
                }
            }
            
        } else { // bKey_p1[i] == 1
            
            if (bKey_p2_2[i] == 0) {
                
                if (bKey_p3_2[i] == 0) {
                    if (s.t[i] > ((float)(9*ts.T[i]))/16) {
                        for (unsigned short j = 0; j < curKeysNum; j++) (*bKeys_p4_2)[j].set(i, 1);
                    } else {
                        for (unsigned short j = 0; j < curKeysNum; j++) {
                            //(*bKeys_p4_2)[j].set(i, 0);
                            (*bKeys_p4_2)[keysNum] = (*bKeys_p4_2)[j];
                            (*bKeys_p4_2)[keysNum].set(i, 1);
                            keysNum++;
                        }
                    }
                } else { // bKey_p3[0] == 1
                    if (s.t[i] > ((float)(11*ts.T[i]))/16) {
                        for (unsigned short j = 0; j < curKeysNum; j++) (*bKeys_p4_2)[j].set(i, 1);
                    } else {
                        for (unsigned short j = 0; j < curKeysNum; j++) {
                            //(*bKeys_p4_2)[j].set(i, 0);
                            (*bKeys_p4_2)[keysNum] = (*bKeys_p4_2)[j];
                            (*bKeys_p4_2)[keysNum].set(i, 1);
                            keysNum++;
                        }
                    }
                }
                
            } else {
                
                if (bKey_p3_2[i] == 0) {
                    if (s.t[i] > ((float)(13*ts.T[i]))/16) {
                        for (unsigned short j = 0; j < curKeysNum; j++) (*bKeys_p4_2)[j].set(i, 1);
                    } else {
                        for (unsigned short j = 0; j < curKeysNum; j++) {
                            //(*bKeys_p4_2)[j].set(i, 0);
                            (*bKeys_p4_2)[keysNum] = (*bKeys_p4_2)[j];
                            (*bKeys_p4_2)[keysNum].set(i, 1);
                            keysNum++;
                        }
                    }
                } else { // bKey_p3[0] == 1
                    if (s.t[i] > ((float)(15*ts.T[i]))/16) {
                        for (unsigned short j = 0; j < curKeysNum; j++) (*bKeys_p4_2)[j].set(i, 1);
                    } else {
                        for (unsigned short j = 0; j < curKeysNum; j++) {
                            //(*bKeys_p4_2)[j].set(i, 0);
                            (*bKeys_p4_2)[keysNum] = (*bKeys_p4_2)[j];
                            (*bKeys_p4_2)[keysNum].set(i, 1);
                            keysNum++;
                        }
                    }
                }
            }
        }
    }
    
    return;
}*/











void get_keys_p3_2(const state& s, const TS& ts, const my_bitset bKey_lj2, const my_bitset bKey_p1_2, const my_bitset bKey_p2_2, unsigned int& keysNum, vector<my_bitset>* bKeys_p3_2) {
    
    keysNum = 0;
    unsigned short curKeysNum = 0;
    
    // i == 0
    (*bKeys_p3_2)[0].reset();
    (*bKeys_p3_2)[1].reset();
    
    if (bKey_lj2[0] == 0) {
        //(*bKeys_p3_2)[0].set(0, 0);
        keysNum = 1;
    } else if (bKey_p1_2[0] == 0) {
        
        if (bKey_p2_2[0] == 0) {
            if (s.p[0] > ((float)(ts.P[0]))/8) {
                (*bKeys_p3_2)[0].set(0, 1);
                keysNum = 1;
            } else {
                //(*bKeys_p3_2)[0].set(0, 0);
                (*bKeys_p3_2)[1].set(0, 1);
                keysNum = 2;
            }
        } else {
            if (s.p[0] > ((float)(3*ts.P[0]))/8) {
                (*bKeys_p3_2)[0].set(0, 1);
                keysNum = 1;
            } else {
                //(*bKeys_p3_2)[0].set(0, 0);
                (*bKeys_p3_2)[1].set(0, 1);
                keysNum = 2;
            }
        }
        
    } else { // bKey_p1[0] == 1
        
        if (bKey_p2_2[0] == 0) {
            if (s.p[0] > ((float)(5*ts.P[0]))/8) {
                (*bKeys_p3_2)[0].set(0, 1);
                keysNum = 1;
            } else {
                //(*bKeys_p3_2)[0].set(0, 0);
                (*bKeys_p3_2)[1].set(0, 1);
                keysNum = 2;
            }
        } else {
            if (s.p[0] > ((float)(7*ts.P[0]))/8) {
                (*bKeys_p3_2)[0].set(0, 1);
                keysNum = 1;
            } else {
                //(*bKeys_p3_2)[0].set(0, 0);
                (*bKeys_p3_2)[1].set(0, 1);
                keysNum = 2;
            }
        }
    }
    
    // i > 0
    for (unsigned short i = 1; i < ts.n; i++) {
        curKeysNum = keysNum;
        
        if (bKey_lj2[i] == 0) {
            /*for (unsigned short j = 0; j < curKeysNum; j++) {
             (*bKeys_p2)[j].set(i, 0);
             }*/
        } else if (bKey_p1_2[i] == 0) {
            
            if (bKey_p2_2[i] == 0) {
                
                if (s.p[i] > ((float)(1*ts.P[i]))/8) {
                    for (unsigned short j = 0; j < curKeysNum; j++) (*bKeys_p3_2)[j].set(i, 1);
                } else {
                    for (unsigned short j = 0; j < curKeysNum; j++) {
                        //(*bKeys_p3_2)[j].set(i, 0);
                        (*bKeys_p3_2)[keysNum] = (*bKeys_p3_2)[j];
                        (*bKeys_p3_2)[keysNum].set(i, 1);
                        keysNum++;
                    }
                }
            } else {
                
                if (s.p[i] > ((float)(3*ts.P[i]))/8) {
                    for (unsigned short j = 0; j < curKeysNum; j++) (*bKeys_p3_2)[j].set(i, 1);
                } else {
                    for (unsigned short j = 0; j < curKeysNum; j++) {
                        //(*bKeys_p3_2)[j].set(i, 0);
                        (*bKeys_p3_2)[keysNum] = (*bKeys_p3_2)[j];
                        (*bKeys_p3_2)[keysNum].set(i, 1);
                        keysNum++;
                    }
                }
            }
            
        } else { // bKey_p1[i] == 1
            
            if (bKey_p2_2[i] == 0) {
                if (s.p[i] > ((float)(5*ts.P[i]))/8) {
                    for (unsigned short j = 0; j < curKeysNum; j++) (*bKeys_p3_2)[j].set(i, 1);
                } else {
                    for (unsigned short j = 0; j < curKeysNum; j++) {
                        //(*bKeys_p3_2)[j].set(i, 0);
                        (*bKeys_p3_2)[keysNum] = (*bKeys_p3_2)[j];
                        (*bKeys_p3_2)[keysNum].set(i, 1);
                        keysNum++;
                    }
                }
            } else {
                if (s.p[i] > ((float)(7*ts.P[i]))/8) {
                    for (unsigned short j = 0; j < curKeysNum; j++) (*bKeys_p3_2)[j].set(i, 1);
                } else {
                    for (unsigned short j = 0; j < curKeysNum; j++) {
                        //(*bKeys_p3_2)[j].set(i, 0);
                        (*bKeys_p3_2)[keysNum] = (*bKeys_p3_2)[j];
                        (*bKeys_p3_2)[keysNum].set(i, 1);
                        keysNum++;
                    }
                }
            }
        }
    }
    
    return;
}












void get_keys_p2_2(const state& s, const TS& ts, const my_bitset bKey_lj2, const my_bitset bKey_p1_2, unsigned int& keysNum, vector<my_bitset>* bKeys_p2_2) {
    
    keysNum = 0;
    unsigned short curKeysNum = 0;
    
    // i == 0
    (*bKeys_p2_2)[0].reset();
    (*bKeys_p2_2)[1].reset();
    
    if (bKey_lj2[0] == 0) {
        //(*bKeys_p2_2)[0].set(0, 0);
        keysNum = 1;
    } else if (bKey_p1_2[0] == 0) {
        if (s.p[0] > ((float)(ts.P[0]))/4) {
            (*bKeys_p2_2)[0].set(0, 1);
            keysNum = 1;
        } else {
            //(*bKeys_p2_2)[0].set(0, 0);
            (*bKeys_p2_2)[1].set(0, 1);
            keysNum = 2;
        }
    } else { // case of (bKey_lj2[0] == 1)
        if (s.p[0] > ((float)(3*ts.P[0]))/4) {
            (*bKeys_p2_2)[0].set(0, 1);
            keysNum = 1;
        } else {
            //(*bKeys_p2_2)[0].set(0, 0);
            (*bKeys_p2_2)[1].set(0, 1);
            keysNum = 2;
        }
    }
    
    // i > 0
    for (unsigned short i = 1; i < ts.n; i++) {
        curKeysNum = keysNum;
        
        if (bKey_lj2[i] == 0) {
            /*for (unsigned short j = 0; j < curKeysNum; j++) {
             (*bKeys_p2_2)[j].set(i, 0);
             }*/
        } else if (bKey_p1_2[i] == 0) {
            if (s.p[i] > ((float)(ts.P[i]))/4) {
                for (unsigned short j = 0; j < curKeysNum; j++) {
                    (*bKeys_p2_2)[j].set(i, 1);
                }
            } else {
                for (unsigned short j = 0; j < curKeysNum; j++) {
                    //(*bKeys_p2_2)[j].set(i, 0);
                    (*bKeys_p2_2)[keysNum] = (*bKeys_p2_2)[j];
                    (*bKeys_p2_2)[keysNum].set(i, 1);
                    keysNum++;
                }
            }
        } else { // bKey_p1_2[i] == 1
            if (s.p[i] > ((float)(3*ts.P[i]))/4) {
                for (unsigned short j = 0; j < curKeysNum; j++) {
                    (*bKeys_p2_2)[j].set(i, 1);
                }
            } else {
                for (unsigned short j = 0; j < curKeysNum; j++) {
                    //(*bKeys_p2_2)[j].set(i, 0);
                    
                    (*bKeys_p2_2)[keysNum] = (*bKeys_p2_2)[j];
                    (*bKeys_p2_2)[keysNum].set(i, 1);
                    keysNum++;
                }
            }
        }
    }
    
    return;
}







void get_keys_p1_2(const state& s, const TS& ts, const my_bitset bKey_lj2, unsigned int& keysNum, vector<my_bitset>* bKeys_p1_2) {
    
    keysNum = 0;
    unsigned short int curKeysNum = 0;
    
    // i == 0
    if (bKey_lj2[0] == 0) {
        (*bKeys_p1_2)[0].reset(); //(*bKeys_p1_2)[0].set(0, 0);
        keysNum = 1;
    } else if (s.p[0] > ((float)(ts.P[0]))/2) {
        (*bKeys_p1_2)[0].reset(); (*bKeys_p1_2)[0].set(0, 1);
        keysNum = 1;
    } else {
        (*bKeys_p1_2)[0].reset(); //(*bKeys_p1_2)[0].set(0, 0);
        (*bKeys_p1_2)[1].reset(); (*bKeys_p1_2)[1].set(0, 1);
        keysNum = 2;
    }
    
    
    // i > 0
    for (unsigned short int i = 1; i < ts.n; i++) {
        curKeysNum = keysNum;
        
        if (bKey_lj2[i] == 0) {
            /*for (unsigned short int j = 0; j < curKeysNum; j++) {
                (*bKeys_p1_2)[j].set(i, 0);
            }*/
        } else if (s.p[i] > ((float)(ts.P[i]))/2) {
            for (unsigned short int j = 0; j < curKeysNum; j++) {
                (*bKeys_p1_2)[j].set(i, 1);
            }
        } else {
            for (unsigned short int j = 0; j < curKeysNum; j++) {
                //(*bKeys_p1_2)[j].set(i, 0);
                
                (*bKeys_p1_2)[keysNum] = (*bKeys_p1_2)[j];
                (*bKeys_p1_2)[keysNum].set(i, 1);
                keysNum++;
            }
        }
    }
    
    return;
}
