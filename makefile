CXX=/usr/local/bin/g++-4.9
CCOPT = -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD

CCLNFLAGS = -m64 -lm -lpthread
OPTIONS = -ansi -Wall -Wno-sign-compare $(CCLNFLAGS)

AUX = custom_types/ts.cpp generate_successors.cpp algorithm_move.cpp get_delta_t.cpp get_map_binary_keys.cpp pruning_constraints.cpp scheduler.cpp p1_key/test_2d_task.cpp p1_key/test_3d_task.cpp p1_key/test_4th_task.cpp p1_key/test_5th_task.cpp p1_key/test_6th_task.cpp p1_key/test_7th_task.cpp p1_key/test_8th_task.cpp

all: gfp_test_p1

gfp_test_p1: schedtst_p1.cpp $(AUX)
	g++ $(OPTIONS) $(CCOPT) -Ofast -std=c++11 -o gfp_test_p1 schedtst_p1.cpp $(AUX)

clean: 
	rm gfp_test_p1





