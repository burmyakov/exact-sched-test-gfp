//bool pruning_cri_tauk_DavisBurns_1(const state& s);
//bool pruning_cri_tauk_DavisBurns_2(const bool processorAvailableToTauK);
bool condition_cri_2(const state& s, const unsigned short m, const unsigned short i, const bool processorAvailableToTauI);
bool condition_necessary_unsched(const state& s, const unsigned short m);
bool condition_for_releases_of_hp_jobs(const state& s);
bool conditionA_cri_tau_i(const state& s, const unsigned short m);
bool conditionB_cri_tau_i(const state& s, const unsigned short m);
bool condition_job_interference(const state& s, const unsigned short m, const int& dt, const unsigned short* perm);
void conditionC_cri_tau_i(const state& s, const unsigned short m, const unsigned short* perm);
