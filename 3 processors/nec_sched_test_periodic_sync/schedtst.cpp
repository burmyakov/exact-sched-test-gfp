#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <string>
#include <algorithm>
//#include <cassert>
#include <climits>
#include "ts.h"



using namespace std;

//const char* fileName = "comparison_varying_n.txt";
ofstream fileResults;

struct state;
unsigned long int savedStatesNum = 0;
unsigned long int timeIntervalLength = 0;

// Main data structures
TS ts; // the task system being analyzed
int m; // n. of processors

struct state {
	TS& ts; 
	enum { ADV, ALG } pl; // player (Adversary or Algorithm)
	
	int* c; // remaining execution time
	int* t; // time to next period

	state(TS& ts_) : ts(ts_) {
		c = new int [ts.n]; 
		t = new int [ts.n]; 
        for(int i=0; i<ts.n; i++) {
            c[i] = ts.C[i];
            t[i] = ts.T[i];
        }
		pl = ADV; 
	}
	state(const state& s) : ts(s.ts), pl(s.pl) { 
		c = new int [ts.n]; 
		t = new int [ts.n]; 
		for(int i=0; i<ts.n; i++) {
			c[i] = s.c[i]; 
			t[i] = s.t[i]; 
		}
	}
	state& operator=(const state& s) {
		if(this != &s) {
			ts = s.ts; 
			pl = s.pl; 
			for(int i=0; i<ts.n; i++) {
				c[i] = s.c[i]; 
				t[i] = s.t[i]; 
			}
		}
		return *this; 
	}
	~state() {
		delete [] c; 
		delete [] t;
	}
	
	// Time to next deadline of a task
	inline int d(int i) const { return max(t[i] - (ts.T[i] - ts.D[i]), 0); } 

	// Equality and order predicates
	bool operator==(const state& s) const { return (pl==s.pl) && equals(c,s.c,ts.n) && equals(t,s.t,ts.n); } 

	bool equals(const int* a, const int* b, int n) const {
		for(int i=0; i<n; i++)
			if(a[i]!=b[i]) return false; 
		return true;
	}

	bool operator<(const state& s) const { 
		if(pl<s.pl) return true; 
		if(s.pl<pl) return false; 
		for(int i=0; i<ts.n; i++) {
			if(c[i]<s.c[i]) return true; 
			if(s.c[i]<c[i]) return false; 
			if(t[i]<s.t[i]) return true; 
			if(s.t[i]<t[i]) return false; 
		}
		return false; 
	}
	
	// Compute a numerical ID of the state
	int id() const {
		int x = 0, b = ts.Tmax(); 
		for(int i=0; i<ts.n; i++) {
			x += c[i]; 
			x *= b;  
			x += t[i]; 
			x *= b; 
		}
		return (pl==ADV ? 2*x+1 : 2*x); 
	}
	
	// Printing functions
	void print() const {
		cout << "s" << id() << ": P" << ((int)pl)+1 << " ";  
		for(int i=0; i<ts.n; i++) {
			cout << "c["<< i << "]: " << c[i] << " "; 
			cout << "d[" << i << "]: " << d(i) << " "; 
			cout << "t["<< i << "]: " << t[i] << " "; 
		}
		cout << endl; 
	}
	
    void printCompact() const {
        cout << (pl==ADV ? "{ADV |" : "{SCH |");
        for(int i=0; i<ts.n; i++)
            cout << "(" << c[i] << ", " << t[i] << ")";
        cout << "}"; 
    }
}; 

// Options
bool quiet = false; 
bool verbose = false; 
bool dump = false; 

void init() { }





unsigned short get_dt_to_next_release_periodic(const state& s, const unsigned short int N, const unsigned short m){
    
    unsigned short dtToNextRelease = max((int)(s.t[0]), 1);
    
    for (unsigned short i = 1; i < N-1; i++) {
        dtToNextRelease = max(1, min((int)(s.t[i]), (int)(dtToNextRelease)));
        if (dtToNextRelease == 1) return dtToNextRelease;
    }
    
    return dtToNextRelease;
}




unsigned short get_dt_to_next_completion(const state& s, const unsigned short int m, const int* perm){
    
    unsigned short j = 0;
    while ((s.c[perm[j]] == 0) && (j < m)) j++;
    unsigned short dtToNextCompletion = max(0, (int)(s.c[perm[j]]));
    
    if ((j >= m-1)||(dtToNextCompletion == 1)) return dtToNextCompletion;
    else {
        for (unsigned short i = j+1; i < m; i++) {
            if (s.c[perm[i]] > 0) {
                dtToNextCompletion = min((int)(s.c[perm[i]]), (int)(dtToNextCompletion));
                if (dtToNextCompletion == 1) return dtToNextCompletion;
            }
        }
    }
    
    return dtToNextCompletion;
}




unsigned short deltaT_periodic(const state& s, const unsigned short int N, const unsigned short int m, const int *perm) {
    
    unsigned short dtToNextRelease = get_dt_to_next_release_periodic(s, N, m);
    
    if (dtToNextRelease == 1) return dtToNextRelease;
    else { // dtToNextRelease > 1
        unsigned short dtToNextCompletion = get_dt_to_next_completion(s, m, perm);
        if (dtToNextCompletion > 0) return min(dtToNextRelease, dtToNextCompletion);
        else return dtToNextRelease; // there are no pending jobs to be completed
    }
}





int gcd(int a, int b)
{
    for (;;)
    {
        if (a == 0) return b;
        b %= a;
        if (b == 0) return a;
        a %= b;
    }
}

int lcm(int a, int b)
{
    int temp = gcd(a, b);
    
    return temp ? (a / temp * b) : 0;
}




// Adjusted for periodic tasks
void adversaryMove(state& s) {
	s.pl = state::ALG;
	for(int i=0; i<ts.n; i++) {
		//if((K & (1<<i)) && s.t[i]==0) {
        if (s.t[i] == 0) {
			s.c[i] = ts.C[i];
			s.t[i] = ts.T[i];
		}
	}
}

bool prefer(const state&, int, int); 

bool algorithmMove(state& s) {
	s.pl = state::ADV;	// Dynamic priority
    //timeIntervalLength++;
	int* perm = new int[ts.n];

	// Sort tasks/jobs according to scheduler (see prefer() function)
	for(int i=0; i<ts.n; i++) perm[i] = i; 
	for(int i=0; i<ts.n; i++)
		for(int k=i+1; k<ts.n; k++)
			if(!prefer(s, perm[i], perm[k]))
				swap(perm[i], perm[k]);
    
    unsigned short dt = deltaT_periodic(s, ts.n, m, perm);

	// Schedule the m highest-priority ones 
	for(int i=0; i<m; i++)
		s.c[perm[i]] = max(s.c[perm[i]]-dt, 0);
	delete [] perm;
    
    timeIntervalLength += dt;

	for(int i=0; i<ts.n; i++) {
		// Clock tick
		s.t[i] = max(s.t[i]-dt, 0);
		// Check deadlines
		//if(s.d(i)==0 && s.c[i]>0) {
        if (s.d(i) < s.c[i]) {
			// Failure
			return false; 
		}
	}
	return true; 
}

// Example 1: Global EDF
#ifdef GEDF
#define ALGNAME "GEDF"
bool prefer(const state& s, int i, int k) {
	if(s.c[i]==0 && s.c[k]==0) return (i < k); 		// no active job from i or k -- use default ordering
	if(s.c[i]==0 || s.c[k]==0) return s.c[i] > 0; 	// only 1 active -- prefer that one
	if(s.d(i) == s.d(k)) return (i < k); 			// break ties as necessary
	return (s.d(i) < s.d(k)); 						// EDF rule
}
#endif

// Example 2: Global FP (priority ordering given by indices, index 1 == highest priority)
#ifdef GFP
#define ALGNAME "GFP with the given priorities"
bool prefer(const state& s, int i, int k) {
	if(s.c[i]==0 && s.c[k]==0) return (i < k); 		// no active job from i or k -- use default ordering
	if(s.c[i]==0 || s.c[k]==0) return s.c[i] > 0; 	// only 1 active -- prefer that one
	return (i < k); 								// FP rule (no ties are possible)
}
#endif

// Example 3: Least Laxity First
// The fact that LLF is predictable is nontrivial, see Han & Park (2006)
#ifdef LLF
#define ALGNAME "LLF"
int laxity(const state& s, int i) {
	// laxity == time to deadline - remaining WCET
	return s.d(i) - s.c[i]; 
}

bool prefer(const state& s, int i, int k) {
	if(s.c[i]==0 && s.c[k]==0) return (i < k); 		// no active job from i or k -- use default ordering
	if(s.c[i]==0 || s.c[k]==0) return s.c[i] > 0; 	// only 1 active -- prefer that one
	if(laxity(s, i) == laxity(s, k)) return i < k; 	// break ties as necessary
	return laxity(s, i) < laxity(s, k); 			// LLF rule
}
#endif

bool populate(unsigned long int lcm_) {
    
    cout << "starting" << endl;
    
	state s(ts);
	bool failureStateGenerated = false;
    
    while (timeIntervalLength <= lcm_) {
        
        if(s.pl==state::ADV) {
            // V1 -> V2
            adversaryMove(s);
        }
        else if(s.pl==state::ALG) {
            // V2 -> V1
            //state v1 = s;
            bool ok = algorithmMove(s);
            savedStatesNum++;
            
            if(!ok) {
                //s.failure = v1.failure = true; // unnecessary -- we stop anyway
                failureStateGenerated = true;
                break; // Break immediately -- we are done!
            }
        }
    }
    
	return failureStateGenerated; 
}



int main(int argc, char* argv[]) {

	init(); 

	m = (unsigned short) strtoul(argv[1], NULL, 0);
    ts.n = (unsigned short) strtoul(argv[2], NULL, 0);
    
    int C, D, P;
    unsigned long int lcm_ = 1;
    for (int i = 0; i < ts.n; i++) {
        C = (int) strtoul(argv[3+3*i], NULL, 0);
        D = (int) strtoul(argv[4+3*i], NULL, 0);
        P = (int) strtoul(argv[5+3*i], NULL, 0);
        lcm_ = lcm(lcm_, P);
        ts.setTask(i, C, D, P);
        //cout << "( " << C << ", " << D << ", " << P << " )" << endl;
    }

    //const char* fileName = (argv[3*(ts.n)+5]);
    //cout << "file name for results: " << fileName << endl;
    
    
    unsigned long int tExecutionStart = clock();
    bool sched = (populate(lcm_) == 0);
    unsigned long int tExecutionTotal_p1 = clock() - tExecutionStart;
    
    //fileResults.open(fileName, ios::app);
    //fileResults << "\t" << sched << "\t" << tExecutionTotal_p1 << "\t" << savedStatesNum;
    //fileResults.close();
    
    cout << "Periodic sync. release:\t\t\t" << (float)(tExecutionTotal_p1*100/CLOCKS_PER_SEC)/100 << " sec,  \t / " << savedStatesNum << " states";
    if (sched) cout << "  \t / SCHED" << endl;
    else cout << "  \t / UNSCHED" << endl;

	return sched;
}


