#include <map>
#include "my_types.h"
#include <cinttypes>

using namespace std;

typedef map<uint8_t, bool> mt1;
typedef map<uint8_t, mt1> mt2;
typedef map<uint8_t, mt2> mt3;
typedef map<uint8_t, mt3> mt4;
typedef map<uint8_t, mt4> mt5;
typedef map<uint8_t, mt5> mt6;
typedef map<my_bitset, mt6, cmpOfBitsets> mt7;
typedef map<my_bitset, mt7, cmpOfBitsets> mt8;
typedef map<my_bitset, mt8, cmpOfBitsets> mt9;
typedef map<my_bitset, mt9, cmpOfBitsets> mt10;
typedef map<my_bitset, mt10, cmpOfBitsets> mt11;
typedef map<my_bitset, mt11, cmpOfBitsets> mt12;
