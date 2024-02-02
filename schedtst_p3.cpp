#include <iostream>
#include <string>
#include <fstream>
#include "custom_types/ts.h"
#include "p3_key/test_2d_task_p3.h"
#include "p3_key/test_3d_task_p3.h"
#include "p3_key/test_4th_task_p3.h"
#include "p3_key/test_5th_task_p3.h"
#include "p3_key/test_6th_task_p3.h"
#include "p3_key/test_7th_task_p3.h"
#include "p3_key/test_8th_task_p3.h"
#include "p3_key/test_9th_task_p3.h"
#include "p3_key/test_10th_task_p3.h"
#include "p3_key/test_11th_task_p3.h"
#include "p3_key/test_12th_task_p3.h"
#include "p3_key/test_13th_task_p3.h"
#include "p3_key/test_14th_task_p3.h"


using namespace std;

ofstream fileResults;



int main(int argc, char* argv[]) {
    
    TS tsOriginal, ts;

    unsigned short m = (unsigned short) strtoul(argv[1], NULL, 0);
    unsigned short n = (unsigned short) strtoul(argv[2], NULL, 0);
    
    tsOriginal.n = n;
    int C, P;
    for (int i = 0; i < n; i++) {
        C = (int) strtoul(argv[3+2*i], NULL, 0);
        P = (int) strtoul(argv[4+2*i], NULL, 0);
        tsOriginal.setTask(i, C, P, P);
    }
    
    bool removeDominatedStatesFromMap = (bool) strtoul(argv[3+2*n], NULL, 0);
    bool verbose = (bool) strtoul(argv[4+2*n], NULL, 0);

    
    for (int i = 0; i < m; i++) ts.setTask(i, tsOriginal.C[i], tsOriginal.D[i], tsOriginal.T[i]);
    
    unsigned long int savedStatesNum = 0;
    unsigned long int visitedStatesNum = 0;
    unsigned long int savedStatesNumIncr = 0;
    unsigned long int visitedStatesNumIncr = 0;
    
    bool sched = true;
    
    unsigned long int t0;
    unsigned long int tExecution_p3;
    unsigned long int tExecutionTotal_p3 = 0;
    
    
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
                sched = test_2d_task_p3(verbose, m, ts, removeDominatedStatesFromMap, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p3 = clock() - t0; tExecutionTotal_p3 += tExecution_p3;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;
                
            case 3:
                t0 = clock();
                sched = test_3d_task_p3(verbose, m, ts, removeDominatedStatesFromMap, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p3 = clock() - t0; tExecutionTotal_p3 += tExecution_p3;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;
                
            case 4:
                t0 = clock();
                sched = test_4th_task_p3(verbose, m, ts, removeDominatedStatesFromMap, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p3 = clock() - t0; tExecutionTotal_p3 += tExecution_p3;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;
                
            case 5:
                t0 = clock();
                sched = test_5th_task_p3(verbose, m, ts, removeDominatedStatesFromMap, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p3 = clock() - t0; tExecutionTotal_p3 += tExecution_p3;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;
                
            case 6:
                t0 = clock();
                sched = test_6th_task_p3(verbose, m, ts, removeDominatedStatesFromMap, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p3 = clock() - t0; tExecutionTotal_p3 += tExecution_p3;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;

            case 7:
                t0 = clock();
                sched = test_7th_task_p3(verbose, m, ts, removeDominatedStatesFromMap, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p3 = clock() - t0; tExecutionTotal_p3 += tExecution_p3;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;

            case 8:
                t0 = clock();
                sched = test_8th_task_p3(verbose, m, ts, removeDominatedStatesFromMap, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p3 = clock() - t0; tExecutionTotal_p3 += tExecution_p3;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;

            case 9:
                t0 = clock();
                sched = test_9th_task_p3(verbose, m, ts, removeDominatedStatesFromMap, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p3 = clock() - t0; tExecutionTotal_p3 += tExecution_p3;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;

            case 10:
                t0 = clock();
                sched = test_10th_task_p3(verbose, m, ts, removeDominatedStatesFromMap, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p3 = clock() - t0; tExecutionTotal_p3 += tExecution_p3;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;

            case 11:
                t0 = clock();
                sched = test_11th_task_p3(verbose, m, ts, removeDominatedStatesFromMap, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p3 = clock() - t0; tExecutionTotal_p3 += tExecution_p3;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;

            case 12:
                t0 = clock();
                sched = test_12th_task_p3(verbose, m, ts, removeDominatedStatesFromMap, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p3 = clock() - t0; tExecutionTotal_p3 += tExecution_p3;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;

            case 13:
                t0 = clock();
                sched = test_13th_task_p3(verbose, m, ts, removeDominatedStatesFromMap, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p3 = clock() - t0; tExecutionTotal_p3 += tExecution_p3;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;

            case 14:
                t0 = clock();
                sched = test_14th_task_p3(verbose, m, ts, removeDominatedStatesFromMap, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p3 = clock() - t0; tExecutionTotal_p3 += tExecution_p3;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;

                
            default: cout << "No function defined to test " << N << " tasks!" << endl;
        }

        if (!sched) break;
    }


    const char* fileName = (argv[2*(tsOriginal.n)+5]);

    fileResults.open(fileName, ios::app);
    fileResults << "\t" << sched << "\t" << tExecutionTotal_p3 << "\t" << savedStatesNum;
    fileResults.close();
    
    if (!removeDominatedStatesFromMap) cout << "Sporadic burm2018 p3 (no r.):\t" << (float)(tExecutionTotal_p3*100/CLOCKS_PER_SEC)/100 << " sec,  \t / " << savedStatesNum << " saved states" << "  \t / " << visitedStatesNum << " visited states";
    else cout << "Sporadic burm2018 p3:\t\t" << (float)(tExecutionTotal_p3*100/CLOCKS_PER_SEC)/100 << " sec,  \t / " << savedStatesNum << " saved states" << "  \t / " << visitedStatesNum << " visited states";
    
    if (sched) cout << "  \t / SCHED" << endl;
    else cout << "  \t / UNSCHED" << endl;

    return sched;
}
