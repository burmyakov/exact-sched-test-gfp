#include <algorithm>
#include <cassert>
#include <cinttypes>

struct TS {
	// Task system
	uint8_t n; // n. of tasks -- must be less than MAXN
	static const int MAXN = 16; 
	uint8_t C[MAXN]; // WCETs
	uint8_t D[MAXN]; // deadlines
	uint8_t P[MAXN]; // minimum interarrival times
	
	uint8_t pmax; // max(P_i) (buffered value)
	TS() { }
    
	TS(uint8_t n_) : n(n_), pmax(0) { assert(n <= MAXN); }
    
	void setTask(uint8_t i, uint8_t Ci, uint8_t Di, uint8_t Pi) {
		C[i] = Ci;
		D[i] = Di;
		P[i] = Pi;
        
		pmax = std::max(pmax, Pi);
        
		assert(C[i] <= D[i]); 
		assert(D[i] <= P[i]); // * constrained deadlines *
	}
    
	int Pmax() const { return pmax; }
	void read();
};

