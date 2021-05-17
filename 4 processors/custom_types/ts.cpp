#include "ts.h"
#include <iostream>

using namespace std; 

void TS::read() {
    
	cerr << "Number of tasks? " << endl;
	cin >> n;
    
	for(int i = 0; i < n; i++) {
		int C, D, P;
		cerr << "C[" << i << "] ?" << endl;
		cin >> C; 
		cerr << "D[" << i << "] ?" << endl;
		cin >> D;
		cerr << "P[" << i << "] ?" << endl;
		cin >> P;
		setTask(i, C, D, P);
	}
}

