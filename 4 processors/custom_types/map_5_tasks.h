#include <map>
#include "my_types.h"

using namespace std;


typedef map<unsigned short, bool> mt1;
typedef map<unsigned short, mt1> mt2;
//typedef map<unsigned short, mt2> mt3;
typedef map<unsigned short, mt2> mt4;
//typedef map<unsigned short, mt4> mt5;
typedef map<unsigned short, mt4> mt6;
//typedef map<unsigned short, mt6> mt7;
typedef map<unsigned short, mt6> mt8;
//typedef map<unsigned short, mt8> mt9;
typedef map<unsigned short, mt8> mt10;
typedef map<my_bitset, mt10, cmpOfBitsets> mt11;
