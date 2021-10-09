#include <algorithm>
#include <cassert>

struct TS {
	// Task system
    uint_fast8_t n; // n. of tasks -- must be less than MAXN
	static const uint_fast8_t MAXN = 16;
    uint_fast8_t C[MAXN]; // WCETs
    uint_fast8_t D[MAXN]; // deadlines
    uint_fast8_t P[MAXN]; // minimum interarrival times
    uint_fast8_t WRTub[MAXN]; // the upper bound for the worst-case response times
	
    uint_fast8_t pmax; // max(P_i) (buffered value)
	TS() { }
    
	TS(uint_fast8_t n_) : n(n_), pmax(0) { assert(n <= MAXN); }
    
	void setTask(uint_fast8_t i, uint_fast8_t Ci, uint_fast8_t Di, uint_fast8_t Pi) {
		C[i] = Ci;
		D[i] = Di;
		P[i] = Pi;
        
		pmax = std::max(pmax, Pi);
        
		assert(C[i] <= D[i]); 
		assert(D[i] <= P[i]); // * constrained deadlines *
	}
    
    uint_fast8_t Pmax() const { return pmax; }
	void read();
};

