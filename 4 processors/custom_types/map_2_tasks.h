#include <map>
#include "my_types.h"

using namespace std;

typedef map<unsigned short, bool> mt1;
typedef map<unsigned short, mt1> mt2;
typedef map<unsigned short, mt2> mt3;
typedef map<unsigned short, mt3> mt4;
typedef map<my_bitset, mt4, cmpOfBitsets> mt5;
