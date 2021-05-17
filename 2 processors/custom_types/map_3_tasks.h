#include <map>
#include "my_types.h"

using namespace std;


typedef map<unsigned short, bool> mt1;
typedef map<unsigned short, mt1> mt2;
//typedef map<unsigned short, mt2> mt3;
typedef map<unsigned short, mt2> mt4;
//typedef map<unsigned short, mt4> mt5;
typedef map<unsigned short, mt4> mt6;
typedef map<my_bitset, mt6, cmpOfBitsets> mt7;
