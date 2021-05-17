#include <iostream>
#include <climits>
#include "custom_types/ts.h"
#include "custom_types/state.h"
#include "get_delta_t.h"
#include "scheduler.h"
#include <algorithm>
#include <math.h>





uint_fast8_t get_wrt(const TS& ts, const uint_fast8_t taskIndx, const uint_fast8_t m) {

    if (taskIndx < m) {
        return ts.C[taskIndx];
    }
    
    uint_fast16_t W = 0;
    uint_fast8_t t = ts.D[taskIndx];
    uint_fast8_t Ci, Pi;
    
    for (uint_fast8_t i = 0; i < taskIndx; i++) {
        Ci = ts.C[i];
        Pi = ts.P[i];
        W += min((int)t, (int)Ci + max(0, ((t - (Ci + Pi - ts.WRTub[i]))/Pi))*Ci + min((int)Ci, max(0, (t - (Ci + Pi - ts.WRTub[i]))) % Pi));
    }
    
    return min(ts.C[taskIndx] + W/m, (int)ts.D[taskIndx]);
}




uint_fast8_t get_response_time_UB(const state& s, const TS& ts, const uint_fast8_t taskIndx, const uint_fast8_t m) {

    // Assumption: task with taskIndx is released, with s.c[taskIndx] > 0
    
    if (taskIndx < m) return s.c[taskIndx];

    uint_fast16_t W = 0;
    uint_fast8_t t = s.d(taskIndx, ts.P[taskIndx], ts.D[taskIndx]);

    for (uint_fast8_t i = 0; i < taskIndx; i++) {
        W += min((int)t, (int)s.c[i] + (max(0, t - max(0, (int)(s.p[i])))/ts.P[i])*ts.C[i] + min((int)(ts.C[i]), (max(0, t - max(0, (int)(s.p[i]))) % ts.P[i])));
    }

    return min(s.c[taskIndx] + W/m, (int)t);
}




uint_fast16_t get_max_remaining_schedule_length(const state& s, const TS& ts, const uint_fast8_t m) {

    const uint_fast8_t N = s.n;
    uint_fast16_t length = 0;
    
    if (s.c[N-1] > 0) {
        // tau_n has already released a job
        return length = s.d(N-1, ts.P[N-1], ts.D[N-1]);
        
    } else {
        // tau_n has not released a job yet
        for (short i = N-1; i >= 0; i--) {
            
            if (s.c[i] > 0) { // removed the second condition of interference -- not needed
                length += (get_response_time_UB(s, ts, i, m) - 1);
                //return length;
                break;
            } else {
                // that is s.c[i] == 0
                if (i < N-1) length += (ts.WRTub[i] - 1);
                else length += ts.D[N-1];
            }
        }
    }

    return length;
}



uint_fast8_t get_Iub_on_tau_n(const state& s, const TS& ts, const uint_fast8_t m) {

    uint_fast16_t W = 0;
    const uint_fast8_t N = ts.n;
    uint_fast16_t maxRemainingScheduleLength = get_max_remaining_schedule_length(s, ts, m);
    
    if (s.c[s.n-1] > 0) {
        
        const uint_fast8_t t = s.d(N-1, ts.P[N-1], ts.D[N-1]);
        for (uint_fast8_t i = 0; i < N-1; i++) {
            W += min((int)t, (int)s.c[i] + (max(0, t - max(0, (int)(s.p[i])))/ts.P[i])*ts.C[i] + min((int)(ts.C[i]), (max(0, t - max(0, (int)(s.p[i]))) % ts.P[i])));
        }
        
    } else {
        for (uint_fast8_t i = 0; i < N-1; i++) {
            //W += min(maxRemainingScheduleLength, (int)s.c[i] + (max(0, maxRemainingScheduleLength - max(0, (int)(s.p[i])))/ts.P[i])*ts.C[i] + min((int)(ts.C[i]), (max(0, maxRemainingScheduleLength - max(0, (int)(s.p[i]))) % ts.P[i])));
            W += min((int)ts.D[s.n-1], (int)s.c[i] + (max(0, maxRemainingScheduleLength - max(0, (int)(s.p[i])))/ts.P[i])*ts.C[i] + min((int)(ts.C[i]), (max(0, maxRemainingScheduleLength - max(0, (int)(s.p[i]))) % ts.P[i])));
        }
    }
    
    return W/m;
}
