#include <algorithm>
#include <cassert>

struct TS {
	// Task system
	int n; // n. of tasks -- must be less than MAXN
	static const int MAXN = 16; 
	int C[MAXN]; // WCETs
	int D[MAXN]; // deadlines
	int P[MAXN]; // minimum interarrival times
	
	int pmax; // max(P_i) (buffered value)
	TS() { }
    
	TS(int n_) : n(n_), pmax(0) { assert(n <= MAXN); }
    
	void setTask(int i, int Ci, int Di, int Pi) {
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

