CXX=/usr/local/bin/g++-10
CCOPT = -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD

CCLNFLAGS = -m64 -lm -lpthread
OPTIONS = -ansi -Wall -Wno-sign-compare $(CCLNFLAGS)

AUX = custom_types/ts.cpp generate_successors.cpp algorithm_move.cpp get_delta_t.cpp get_map_binary_keys.cpp response_time_bounds.cpp response_time_Guan2009.cpp pruning_constraints.cpp scheduler.cpp tasks/test_5th_task.cpp tasks/test_6th_task.cpp tasks/test_7th_task.cpp tasks/test_8th_task.cpp tasks/test_9th_task.cpp tasks/test_10th_task.cpp tasks/test_11th_task.cpp

all: gfp_test

gfp_test: schedtst.cpp $(AUX)
	$(CXX) $(OPTIONS) $(CCOPT) -Ofast -std=c++17 -o gfp_test schedtst.cpp $(AUX)

clean: 
	rm gfp_test





