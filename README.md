# exact-sched-test-gfp

An exact schedulability test for global fixed-priority (GFP) multiprocessor scheduling. Applies to real-time sporadic tasks with constrained deadlines. Implemented in C++. 

The provided implementation supports up to 14 tasks in a set. By default, the deadlines are assumed to be implicit (that is D_i = P_i). To reduce the compilation time, reduce the number of supported tasks in makefile and schedtst_p1.cpp files.
