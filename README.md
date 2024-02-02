# Exact schedulability test for Global Fixed Priorities on multicore

An exact schedulability test for global fixed-priority (GFP) multiprocessor scheduling. Applies to real-time sporadic tasks with constrained deadlines. Implemented in C++. 

The provided implementation supports up to 14 tasks in a set. By default, the deadlines are assumed to be implicit (that is D_i = P_i). To reduce the compilation time, reduce the number of supported tasks in makefile and schedtst_p1.cpp files.

This code implements the algorithm and pruning rule described in the paper

> Artem Burmyakov, Enrico Bini, Chang-Gun Lee.
> *"Towards a tractable exact test for global multiprocessor fixed priority scheduling"*,
> IEEE Transactions on Computers 71(11):2955-2967, January 2022. DOI: [10.1109/TC.2022.3142540](https://dx.doi.org/10.1109/TC.2022.3142540)
