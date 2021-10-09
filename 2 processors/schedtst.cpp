#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "custom_types/ts.h"
#include "tasks/test_3d_task.h"
#include "tasks/test_4th_task.h"
#include "tasks/test_5th_task.h"
#include "tasks/test_6th_task.h"
#include "tasks/test_7th_task.h"
/*#include "tasks/test_8th_task.h"
#include "tasks/test_9th_task.h"
#include "tasks/test_10th_task.h"
#include "tasks/test_11th_task.h"
#include "tasks/test_12th_task.h"
#include "tasks/test_13th_task.h"
#include "tasks/test_14th_task.h"*/


using namespace std;

ofstream fileResults;




string int_to_string(int i) {
    stringstream ss;
    string s;
    ss << i;
    s = ss.str();
    
    return s;
}




int main(int argc, char* argv[]) {
    
    TS tsOriginal;
    
    const unsigned short m = 2;
    int n;
    bool verbose;
    
    cout << "Processors number: 2" << endl;
    cout << "n?" << endl;
    cin >> n;
    tsOriginal.n = n;
    
    int Ci, Di, Pi;
    for (int i = 0; i < n; i++) {
        cout << "C[" << i << "]?" << endl;
        cin >> Ci;
        cout << "D[" << i << "]?" << endl;
        cin >> Di;
        cout << "P[" << i << "]?" << endl;
        cin >> Pi;
        tsOriginal.setTask(i, Ci, Di, Pi);
    }
    
    cout << "verbose?" << endl;
    cin >> verbose;
    
    
    bool dcmpoSchedule = false;
    cout << "schedule according to DCMPO priority ordering?:" << endl;
    cin >> dcmpoSchedule;
    
    
    // Sort tasks according to D-CMPO order
    if (dcmpoSchedule) {
        for (unsigned short i = 0; i < tsOriginal.n; i++) {
            for (unsigned short j = i+1; j < tsOriginal.n; j++) {
                if (tsOriginal.D[i] - tsOriginal.C[i] > tsOriginal.D[j] - tsOriginal.C[j]) {
                    swap(tsOriginal.C[i], tsOriginal.C[j]);
                    swap(tsOriginal.D[i], tsOriginal.D[j]);
                    swap(tsOriginal.P[i], tsOriginal.P[j]);
                }
            }
        }
        
        cout << endl << "Scheduling tasks according to DCMPO priority ordering:" << endl;
        for (int i = 0; i < tsOriginal.n; i++) {
            cout << "tau_" << i << ":\t" << (int)tsOriginal.C[i] << ", " << (int)tsOriginal.D[i] << ", " << (int)tsOriginal.P[i] << endl;
        }
    }
    
    
    cout << "Checking necessary schedulability condition: synchronous periodic releases" << endl;
    string inputs = int_to_string(m) + " " + int_to_string(n);
    for (int i = 0; i < n; i++) inputs += " " + int_to_string(tsOriginal.C[i]) + " " + int_to_string(tsOriginal.D[i]) + " " + int_to_string(tsOriginal.P[i]);
    string fc = "nec_sched_test_periodic_sync/./gfp_test " + inputs;
    int ret = system(fc.c_str());
    bool schedPerSync = WEXITSTATUS(ret);
    if (!schedPerSync) {
        cout << "Necessary sched. cond. does not hold" << endl;
        cout << "Task set is unschedulable!" << endl;
        return 1;
    }
    cout << "Necessary sched. cond. holds" << endl;

    
    bool sched = true;
    
    unsigned long int savedStatesNum = 0;
    unsigned long int visitedStatesNum = 0;
    unsigned long int savedStatesNumIncr = 0;
    unsigned long int visitedStatesNumIncr = 0;
    
    unsigned long int t0;
    unsigned long int tExecution_p1;
    unsigned long int tExecutionTotal_p1 = 0;
    
    
    TS ts;
    for (uint_fast8_t i = 0; i < m; i++) ts.setTask(i, tsOriginal.C[i], tsOriginal.D[i], tsOriginal.P[i]);
    
    for (uint_fast8_t N = m + 1; N <= tsOriginal.n; N++) {
        ts.n = N;
        ts.setTask(N-1, tsOriginal.C[N-1], tsOriginal.D[N-1], tsOriginal.P[N-1]);

        if (verbose) {
            cout << endl << "===================" << endl;
            cout << "Checking task " << (int)ts.n << endl;
        }

        switch (N) {
            case 3:
                t0 = clock();
                sched = test_3d_task(verbose, m, ts, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p1 = clock() - t0; tExecutionTotal_p1 += tExecution_p1;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;
                
            case 4:
                t0 = clock();
                sched = test_4th_task(verbose, m, ts, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p1 = clock() - t0; tExecutionTotal_p1 += tExecution_p1;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;
                
            case 5:
                t0 = clock();
                sched = test_5th_task(verbose, m, ts, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p1 = clock() - t0; tExecutionTotal_p1 += tExecution_p1;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;
                
            case 6:
                t0 = clock();
                sched = test_6th_task(verbose, m, ts, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p1 = clock() - t0; tExecutionTotal_p1 += tExecution_p1;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;

            case 7:
                t0 = clock();
                sched = test_7th_task(verbose, m, ts, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p1 = clock() - t0; tExecutionTotal_p1 += tExecution_p1;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;

            /*case 8:
                t0 = clock();
                sched = test_8th_task(verbose, m, ts, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p1 = clock() - t0; tExecutionTotal_p1 += tExecution_p1;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;

            case 9:
                t0 = clock();
                sched = test_9th_task(verbose, m, ts, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p1 = clock() - t0; tExecutionTotal_p1 += tExecution_p1;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;

            case 10:
                t0 = clock();
                sched = test_10th_task(verbose, m, ts, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p1 = clock() - t0; tExecutionTotal_p1 += tExecution_p1;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;

            case 11:
                t0 = clock();
                sched = test_11th_task(verbose, m, ts, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p1 = clock() - t0; tExecutionTotal_p1 += tExecution_p1;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;

            case 12:
                t0 = clock();
                sched = test_12th_task(verbose, m, ts, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p1 = clock() - t0; tExecutionTotal_p1 += tExecution_p1;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;

            case 13:
                t0 = clock();
                sched = test_13th_task(verbose, m, ts, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p1 = clock() - t0; tExecutionTotal_p1 += tExecution_p1;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;

            case 14:
                t0 = clock();
                sched = test_14th_task(verbose, m, ts, savedStatesNumIncr, visitedStatesNumIncr);
                tExecution_p1 = clock() - t0; tExecutionTotal_p1 += tExecution_p1;

                savedStatesNum += savedStatesNumIncr; visitedStatesNum += visitedStatesNumIncr;
                break;*/

                
            default: cout << "No function defined to test " << (int)N << " tasks!" << endl;
        }

        if (!sched) break;
    }
    
    cout << "Sporadic burm2018 (no r.):\t" << (float)(tExecutionTotal_p1*100/CLOCKS_PER_SEC)/100 << " sec,  \t / " << savedStatesNum << " saved states" << "  \t / " << visitedStatesNum << " visited states";
    if (sched) cout << "  \t / SCHED" << endl;
    else cout << "  \t / UNSCHED" << endl;

    return 1;
}
