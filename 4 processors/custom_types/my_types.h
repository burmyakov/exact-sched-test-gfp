using namespace std;

typedef bitset<16> my_bitset;

struct cmpOfBitsets {
    bool operator()(const my_bitset& bs1, const my_bitset& bs2) const {
        return bs1.to_ulong() < bs2.to_ulong();
    }
};
