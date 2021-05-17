#include "ts.h"
#include <iostream>

using namespace std; 

void TS::read(bool quiet) {
	if(!quiet) cerr << "Number of tasks? " << endl; 
	cin >> n; 
	tmax = 0; 
	for(int i=0; i<n; i++) {
		int C,D,T; 
		if(!quiet) cerr << "C[" << i << "] ?" << endl; 
		cin >> C; 
		if(!quiet) cerr << "D[" << i << "] ?" << endl; 
		cin >> D; 
		if(!quiet) cerr << "T[" << i << "] ?" << endl; 
		cin >> T; 
		setTask(i, C, D, T); 
	}
}

