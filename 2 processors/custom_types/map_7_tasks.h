#include <map>
#include "my_types.h"

using namespace std;


typedef map<unsigned short, bool> mt1;
typedef map<unsigned short, mt1> mt2;
typedef map<unsigned short, mt2> mt3;
typedef map<unsigned short, mt3> mt4;
typedef map<unsigned short, mt4> mt5;
typedef map<unsigned short, mt5> mt6;
typedef map<unsigned short, mt6> mt7;
typedef map<unsigned short, mt7> mt8;
typedef map<unsigned short, mt8> mt9;
typedef map<unsigned short, mt9> mt10;
//typedef map<unsigned short, mt10> mt11;
typedef map<unsigned short, mt10> mt12;
//typedef map<unsigned short, mt12> mt13;
typedef map<unsigned short, mt12> mt14;
typedef map<my_bitset, mt14, cmpOfBitsets> mt15;
