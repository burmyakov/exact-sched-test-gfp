bool condition_cri_2(const state& s, const uint_fast8_t m, const uint_fast8_t i, const bool processorAvailableToTauI);
bool condition_necessary_unsched(const state& s, const TS& ts, const uint_fast8_t m);
bool condition_for_releases_of_hp_jobs(const state& s);
bool conditionA_cri_tau_i(const state& s, const TS& ts, const uint_fast8_t m);
bool conditionB_cri_tau_i(const state& s, const TS& ts, const uint_fast8_t m);
bool condition_job_interference(const state& s, const uint_fast8_t m, const uint_fast8_t& dt, const uint_fast8_t* perm);
void conditionC_cri_tau_i(const state& s, const TS& ts, const uint_fast8_t m, const uint_fast8_t* perm);
unsigned short get_wrt(const TS& ts, const uint_fast8_t i, const uint_fast8_t m);
unsigned short int get_Iub_on_tau_n(const state& s, const TS& ts, const uint_fast8_t m);
unsigned short get_response_time_UB(const state& s, const TS& ts, const uint_fast8_t taskIndx, const uint_fast8_t m);
bool condition_of_interference_at_job_completion(const state& s, const uint_fast8_t m);
void condition_on_next_release_instants(state& s, const TS& ts);
bool check_adversary_pruning_conditions(state& s, const TS& ts, const unsigned short m);
