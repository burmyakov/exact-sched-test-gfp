#include <iostream>
#include <string>
#include <algorithm>
//#include "ts.h"

using namespace std;


struct state {
    TS& tsLocal;
    unsigned short int* c; // remaining execution time
    //unsigned short int* d; // remaining time until deadline
    unsigned short int* p; // time to next period
    bool* interferred; // interference flags
    bool* jobCanBeReleasedBefore;
    bool* processorAvailableForTau_i;
    bool* prevState_processorAvailableForTau_i;
    unsigned short int pendJobsNum;
    unsigned short int lockedJobsNum;
    unsigned short int sumCs;
    unsigned short int sumSlacks;
    
    // constructor 1
    state(TS& _ts): tsLocal(_ts) {
        c = new unsigned short int[tsLocal.n];
        //d = new unsigned short int[tsLocal.n];
        p = new unsigned short int[tsLocal.n];
        for (int i = 0; i < tsLocal.n; i++) c[i] = p[i] = 0;

        jobCanBeReleasedBefore = new bool[tsLocal.n];
        processorAvailableForTau_i = new bool[tsLocal.n];
        prevState_processorAvailableForTau_i = new bool[tsLocal.n];
        for (int i = 0; i < tsLocal.n; i++) {
            jobCanBeReleasedBefore[i] = false; // assumption for a start state
            processorAvailableForTau_i[i] = true;
            prevState_processorAvailableForTau_i[i] = true; // check this assumption !!!
        }
        
        interferred = new bool[tsLocal.n-1];
        for (int i = 0; i < tsLocal.n-1; i++) interferred[i] = 0;
        
        pendJobsNum = 0;
        lockedJobsNum = 0;
        sumCs = 0;
        sumSlacks = 0;
    }
    
    // copy constructor
    state(const state& s) : tsLocal(s.tsLocal) {
        c = new unsigned short int[tsLocal.n];
        //d = new unsigned short int[tsLocal.n];
        p = new unsigned short int[tsLocal.n];
        
        for (int i = 0; i < tsLocal.n; i++) {
            c[i] = s.c[i];
            //d[i] = s.d[i];
            p[i] = s.p[i];
        }

        jobCanBeReleasedBefore = new bool[tsLocal.n];
        processorAvailableForTau_i = new bool[tsLocal.n];
        prevState_processorAvailableForTau_i = new bool[tsLocal.n];
        for (int i = 0; i < tsLocal.n; i++) {
            jobCanBeReleasedBefore[i] = s.jobCanBeReleasedBefore[i];
            processorAvailableForTau_i[i] = s.processorAvailableForTau_i[i];
            prevState_processorAvailableForTau_i[i] = s.prevState_processorAvailableForTau_i[i];
        }
        
        interferred = new bool[tsLocal.n-1];
        for (int i = 0; i < tsLocal.n-1; i++) interferred[i] = s.interferred[i];

        pendJobsNum = s.pendJobsNum;

        lockedJobsNum = s.lockedJobsNum;
        sumCs = s.sumCs;
        sumSlacks = s.sumSlacks;
    }
    
    state& operator=(const state& s) {
        if(this != &s) {
            for(unsigned short i=0; i<tsLocal.n; i++) {
                c[i] = s.c[i];
                //d[i] = s.d[i];
                p[i] = s.p[i];
                jobCanBeReleasedBefore[i] = s.jobCanBeReleasedBefore[i];
            }
            
            for (unsigned short i = 0; i < tsLocal.n; i++) {
                processorAvailableForTau_i[i] = s.processorAvailableForTau_i[i];
                prevState_processorAvailableForTau_i[i] = s.prevState_processorAvailableForTau_i[i];
            }

            pendJobsNum = s.pendJobsNum;
            lockedJobsNum = s.lockedJobsNum;
            sumCs = s.sumCs;
            sumSlacks = s.sumSlacks;
            for (unsigned short i = 0; i < tsLocal.n-1; i++) interferred[i] = s.interferred[i];
        }
        return *this;
    }
    
    void updatePendJobsNum() {
        pendJobsNum = 0;
        for (int i=0; i<tsLocal.n; i++) if (c[i] > 0) pendJobsNum++;
        return;
    }
    
    void updateLockedJobsNum() {
        lockedJobsNum = 0;
        for (int i=0; i<tsLocal.n; i++) if (p[i] > 0) lockedJobsNum++;
        return;
    }
    
    void updateSumCs() {
        sumCs = 0;
        for (int i = 0; i < tsLocal.n; i++) sumCs += c[i];
        return;
    }
    
    void updateSumSlacks() {
        sumSlacks = 0;
        for (int i = 0; i < tsLocal.n; i++) sumSlacks += p[i];
        return;
    }
    
    void updateCounters() {
        updatePendJobsNum();
        updateLockedJobsNum();
        updateSumCs();
        updateSumSlacks();
        return;
    }
    
    bool operator<(const state& s) const {
        
        if (lockedJobsNum < s.lockedJobsNum) return true;
        if (lockedJobsNum > s.lockedJobsNum) return false;
        if (pendJobsNum < s.pendJobsNum) return true;
        if (pendJobsNum > s.pendJobsNum) return false;
        
        for (int i = tsLocal.n-1; i >= 0; i--) {
            if ((c[i] > 0) && (s.c[i] > 0)) {
                if (p[i] - c[i] < s.p[i] - s.c[i]) return false;
                if (p[i] - c[i] > s.p[i] - s.c[i]) return true;
            }
            if(c[i] > s.c[i]) return true;
            if(s.c[i] > c[i]) return false;
            if(p[i] > s.p[i]) return false; // true
            if(s.p[i] > p[i]) return true; // false
        }
        
        return false;
    }
    
    
    
    
    
    // Time to next deadline of a task
    inline int d(int i) const { return max(p[i] - (tsLocal.P[i] - tsLocal.D[i]), 0); }
    
    // Printing functions
    void printCmpct() const {
        cout << "{";
        for(int i=0; i<tsLocal.n; i++) {
            cout << "(" << c[i] << ", " << d(i) << ", " << p[i] << ") ";
        }
        cout << "}";
        cout << endl;
    }
    
    void print() const {
        cout << "==============" << endl;
        cout << "{";
        for(int i=0; i<tsLocal.n; i++) {
            cout << "(" << c[i] << ", " << d(i) << ", " << p[i] << ") ";
        }
        cout << "}" << endl;
        cout << "pendJobsNum:\t" << pendJobsNum << endl;
        cout << "canReleaseBefore:\t";
        for (int i = 0; i < tsLocal.n; i++) cout << "[" << i << "]: " << jobCanBeReleasedBefore[i] << "\t";
        cout << endl;
        cout << "processorAvailable:\t";
        for (int i = 0; i < tsLocal.n; i++) cout << "[" << i << "]: " << processorAvailableForTau_i[i] << "\t";
        cout << endl;
        cout << "procAvailablePrSt:\t";
        for (int i = 0; i < tsLocal.n; i++) cout << "[" << i << "]: " << prevState_processorAvailableForTau_i[i] << "\t";
        cout << endl;
        cout << "=============" << endl << endl;
    }
    
    void print_until_tau_i(int indx) const {
        cout << "==============" << endl;
        cout << "{";
        for(int i=0; i<=indx; i++) {
            cout << "(" << c[i] << ", " << d(i) << ", " << p[i] << ") ";
        }
        cout << "}" << endl;
        cout << "pendJobsNum:\t" << pendJobsNum << endl;
        cout << "canReleaseBefore:\t";
        for (int i = 0; i <= indx; i++) cout << "[" << i << "]: " << jobCanBeReleasedBefore[i] << "\t";
        cout << endl;
        cout << "processorAvailable:\t";
        for (int i = 0; i <= indx; i++) cout << "[" << i << "]: " << processorAvailableForTau_i[i] << "\t";
        cout << endl;
        cout << "procAvailablePrSt:\t";
        for (int i = 0; i <= indx; i++) cout << "[" << i << "]: " << prevState_processorAvailableForTau_i[i] << "\t";
        cout << endl;
        cout << "=============" << endl << endl;
    }
    
    // destructor
    ~state() {
        delete [] c;
        delete [] p;
        delete [] interferred;
        delete [] jobCanBeReleasedBefore;
        delete [] processorAvailableForTau_i;
        delete [] prevState_processorAvailableForTau_i;
    }
};
