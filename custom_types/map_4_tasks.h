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
typedef map<uint8_t, mt6> mt7;
typedef map<uint8_t, mt7> mt8;
typedef map<uint8_t, mt8> mt9;
typedef map<uint8_t, mt9> mt10;
typedef map<my_bitset, mt10, cmpOfBitsets> mt11;
typedef map<my_bitset, mt11, cmpOfBitsets> mt12;
typedef map<my_bitset, mt12, cmpOfBitsets> mt13;
typedef map<my_bitset, mt13, cmpOfBitsets> mt14;
typedef map<my_bitset, mt14, cmpOfBitsets> mt15;
typedef map<my_bitset, mt15, cmpOfBitsets> mt16;
