bool condition_cri_2(const state& s, const uint8_t m, const uint8_t i, const bool processorAvailableToTauI);
bool condition_necessary_unsched(const state& s, const uint8_t m);
bool condition_for_releases_of_hp_jobs(const state& s);
bool conditionA_cri_tau_i(const state& s, const uint8_t m);
bool conditionB_cri_tau_i(const state& s, const uint8_t m);
bool condition_job_interference(const state& s, const uint8_t m, const uint8_t& dt, const uint8_t* perm);
void conditionC_cri_tau_i(const state& s, const uint8_t m, const uint8_t* perm);
