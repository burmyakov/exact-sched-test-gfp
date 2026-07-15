#pragma once
#include "custom_types/state.h"
#include "custom_types/ts.h"

void generate_successors(const TS&, state&, const uint_fast8_t, vector<state>*, uint_fast16_t&);
