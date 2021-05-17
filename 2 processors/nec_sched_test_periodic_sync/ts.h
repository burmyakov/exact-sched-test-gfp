#ifndef TS_H
#define TS_H
#include <algorithm>
#include <cassert>

#ifdef DEBUG
   #define DEBUGE(x) cout << #x << ": " << x << endl
#else
   #define DEBUGE(x)
#endif

struct TS {
	// Task system
	int n; // n. of tasks -- must be less than MAXN
	static const int MAXN = 16; 
	int C[MAXN]; // WCETs
	int D[MAXN]; // deadlines
	int T[MAXN]; // minimum interarrival times
	// 
	int tmax; // max(T_i) (buffered value)
	TS() { }
	TS(int n_) : n(n_), tmax(0) { assert(n <= MAXN); }
	void setTask(int i, int Ci, int Di, int Ti) {
		C[i] = Ci;
		D[i] = Di;
		T[i] = Ti; 
		tmax = std::max(tmax, Ti); 
		assert(C[i] <= D[i]); 
		assert(D[i] <= T[i]); // * constrained deadlines *
	}
	int Tmax() const { return tmax; }
	void read(bool quiet); 
}; 

#endif // TS_H

