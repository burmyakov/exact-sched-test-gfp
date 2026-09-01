CCACHE_FOUND := $(shell command -v ccache 2> /dev/null)
DEFAULT_CXX = g++

ifdef CCACHE_FOUND
    CXX = ccache $(DEFAULT_CXX)
else
    CXX = $(DEFAULT_CXX)
endif

CXXFLAGS  = -ansi -Wall -Wno-sign-compare \
            -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD \
            -O3 -ffast-math -std=c++17

LDFLAGS   = -m64 -lm -lpthread
INCLUDES  = -I./p1_key -I./custom_types

# Auto-Header dependency tracking
# https://news.ycombinator.com/item?id=15061255
DEPFLAGS  = -MMD -MP

TASK_SRC  = \
			p1_key/test_2d_task.cpp   \
			p1_key/test_3d_task.cpp   \
			p1_key/test_4th_task.cpp  \
			p1_key/test_5th_task.cpp  \
			p1_key/test_6th_task.cpp  \
			p1_key/test_7th_task.cpp  \
			p1_key/test_8th_task.cpp  \

			# p1_key/test_9th_task.cpp  \
			# p1_key/test_10th_task.cpp \
			# p1_key/test_11th_task.cpp \
			# p1_key/test_12th_task.cpp \
			# p1_key/test_13th_task.cpp \
			# p1_key/test_14th_task.cpp \

TASK_OBJ  = $(patsubst p1_key/%.cpp,obj/p1_key/%.o,$(TASK_SRC))

AUX_SRC   = \
		custom_types/ts.cpp \
        generate_successors.cpp \
        algorithm_move.cpp \
        get_delta_t.cpp \
        get_map_binary_keys.cpp \
        pruning_constraints.cpp \
        scheduler.cpp

AUX_OBJ   = $(patsubst %.cpp,obj/%.o,$(AUX_SRC))

ALL_OBJ   = $(TASK_OBJ) $(AUX_OBJ) obj/schedtst.o obj/schedtst_demo.o
DEPS      = $(ALL_OBJ:.o=.d)

.PHONY: all clean

all: gfp_test_p1

libgfp.a: $(TASK_OBJ)
		ar rcs $@ $^

obj/tasks/%.o: tasks/%.cpp
		@mkdir -p $(dir $@)
		$(CXX) $(CXXFLAGS) $(DEPFLAGS) $(INCLUDES) -c $< -o $@

obj/%.o: %.cpp
		@mkdir -p $(dir $@)
		$(CXX) $(CXXFLAGS) $(DEPFLAGS) $(INCLUDES) -c $< -o $@

gfp_test_p1: obj/schedtst_p1.o $(AUX_OBJ) libgfp.a
		$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean:
		rm -rf obj libgfp.a gfp_test_p1
