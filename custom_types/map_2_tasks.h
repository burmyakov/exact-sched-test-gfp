#include <map>
#include "my_types.h"

using namespace std;

typedef map<unsigned short, bool> mt1;
typedef map<unsigned short, mt1> mt2;
typedef map<unsigned short, mt2> mt3;
typedef map<unsigned short, mt3> mt4;
typedef map<unsigned short, mt4> mt5;
typedef map<unsigned short, mt5> mt6;
typedef map<my_bitset, mt6, cmpOfBitsets> mt7;
typedef map<my_bitset, mt7, cmpOfBitsets> mt8;
typedef map<my_bitset, mt8, cmpOfBitsets> mt9;
typedef map<my_bitset, mt9, cmpOfBitsets> mt10;
typedef map<my_bitset, mt10, cmpOfBitsets> mt11;
typedef map<my_bitset, mt11, cmpOfBitsets> mt12;
