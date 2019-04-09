#include <iostream>
#include <string>
#include <fstream>
#include "custom_types/ts.h"
#include "p1_key/test_2d_task.h"
#include "p1_key/test_3d_task.h"
#include "p1_key/test_4th_task.h"
#include "p1_key/test_5th_task.h"
#include "p1_key/test_6th_task.h"
#include "p1_key/test_7th_task.h"
#include "p1_key/test_8th_task.h"
#include "p1_key/test_9th_task.h"
#include "p1_key/test_10th_task.h"
#include "p1_key/test_11th_task.h"
#include "p1_key/test_12th_task.h"
#include "p1_key/test_13th_task.h"
#include "p1_key/test_14th_task.h"


using namespace std;

ofstream fileResults;



int main(int argc, char* argv[]) {
    
    TS tsOriginal, ts;

    unsigned short m;
    cerr << "Number of processors?" << endl;
    cin >> m;
    
    unsigned short n;
    cerr << "Number of tasks?" << endl;
    cin >> n;
    
    tsOriginal.n = n;
    int C, P;
    for (int i = 0; i < n; i++) {
        cerr << "C[" << i << "]?" << endl;
        cin >> C;
        cerr << "P[" << i << "]?" << endl;
        cin >> P;
        tsOriginal.setTask(i, C, P, P);
    }
    
    bool removeDominatedStatesFromMap = 0; // default setting
    
    bool verbose = 0;
    cerr << "Verbose? (0 - no, 1 -yes)" << endl;
    cin >> verbose;

    
    for (int i = 0; i < m; i++) ts.setTask(i, tsOriginal.C[i], tsOriginal.D[i], tsOriginal.T[i]);
    
    unsigned long int savedStatesNum = 0;
    unsigned long int visitedStatesNum = 0;
    unsigned long int savedStatesNumIncr = 0;
    unsigned long int visitedStatesNumIncr = 0;
    
    bool sched = true;
    
    unsigned long int t0;
    unsigned long int tExecution_p1;
    unsigned long int tExecutionTotal_p1 = 0;
    
    
    for (int N = m + 1; N <= tsOriginal.n; N++) {
        ts.n = N;
        ts.setTask(N-1, tsOriginal.C[N-1], tsOriginal.D[N-1], tsOriginal.T[N-1]);

        if (verbose) {
            cout << endl << "===================" << endl;
            cout << "Checking task " << ts.n << endl;
        }

        switch (N) {
            case 2:
                t0 = clock();
                sched = test_2d_task(verbose, m, ts, removeDominatedStatesFromMap, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p1 = clock() - t0; tExecutionTotal_p1 += tExecution_p1;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;
                
            case 3:
                t0 = clock();
                sched = test_3d_task(verbose, m, ts, removeDominatedStatesFromMap, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p1 = clock() - t0; tExecutionTotal_p1 += tExecution_p1;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;
                
            case 4:
                t0 = clock();
                sched = test_4th_task(verbose, m, ts, removeDominatedStatesFromMap, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p1 = clock() - t0; tExecutionTotal_p1 += tExecution_p1;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;
                
            case 5:
                t0 = clock();
                sched = test_5th_task(verbose, m, ts, removeDominatedStatesFromMap, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p1 = clock() - t0; tExecutionTotal_p1 += tExecution_p1;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;
                
            case 6:
                t0 = clock();
                sched = test_6th_task(verbose, m, ts, removeDominatedStatesFromMap, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p1 = clock() - t0; tExecutionTotal_p1 += tExecution_p1;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;

            case 7:
                t0 = clock();
                sched = test_7th_task(verbose, m, ts, removeDominatedStatesFromMap, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p1 = clock() - t0; tExecutionTotal_p1 += tExecution_p1;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;

            case 8:
                t0 = clock();
                sched = test_8th_task(verbose, m, ts, removeDominatedStatesFromMap, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p1 = clock() - t0; tExecutionTotal_p1 += tExecution_p1;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;

            case 9:
                t0 = clock();
                sched = test_9th_task(verbose, m, ts, removeDominatedStatesFromMap, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p1 = clock() - t0; tExecutionTotal_p1 += tExecution_p1;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;

            case 10:
                t0 = clock();
                sched = test_10th_task(verbose, m, ts, removeDominatedStatesFromMap, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p1 = clock() - t0; tExecutionTotal_p1 += tExecution_p1;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;

            case 11:
                t0 = clock();
                sched = test_11th_task(verbose, m, ts, removeDominatedStatesFromMap, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p1 = clock() - t0; tExecutionTotal_p1 += tExecution_p1;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;

            case 12:
                t0 = clock();
                sched = test_12th_task(verbose, m, ts, removeDominatedStatesFromMap, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p1 = clock() - t0; tExecutionTotal_p1 += tExecution_p1;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;

            case 13:
                t0 = clock();
                sched = test_13th_task(verbose, m, ts, removeDominatedStatesFromMap, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p1 = clock() - t0; tExecutionTotal_p1 += tExecution_p1;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;

            case 14:
                t0 = clock();
                sched = test_14th_task(verbose, m, ts, removeDominatedStatesFromMap, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p1 = clock() - t0; tExecutionTotal_p1 += tExecution_p1;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;

                
            default: cout << "No function defined to test " << N << " tasks!" << endl;
        }

        if (!sched) break;
    }


    const char* fileName = (argv[2*(tsOriginal.n)+5]);

    fileResults.open(fileName, ios::app);
    fileResults << "\t" << sched << "\t" << tExecutionTotal_p1 << "\t" << savedStatesNum;
    fileResults.close();
    
    if (!removeDominatedStatesFromMap) cout << "Sporadic burm2018 p1 (no r.):\t" << (float)(tExecutionTotal_p1*100/CLOCKS_PER_SEC)/100 << " sec,  \t / " << savedStatesNum << " saved states" << "  \t / " << visitedStatesNum << " visited states";
    else cout << "Sporadic burm2018 p1:\t\t" << (float)(tExecutionTotal_p1*100/CLOCKS_PER_SEC)/100 << " sec,  \t / " << savedStatesNum << " saved states" << "  \t / " << visitedStatesNum << " visited states";
    
    if (sched) cout << "  \t / SCHED" << endl;
    else cout << "  \t / UNSCHED" << endl;

    return sched;
}
