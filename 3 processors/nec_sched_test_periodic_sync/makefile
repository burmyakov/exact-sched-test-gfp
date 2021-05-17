CCOPT = -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD
OPTIONS = -ansi -Wall -Wno-sign-compare $(CCFLAGS)

AUX = ts.cpp

CCFLAGS = $(CCOPT)

all: gfp

gfp: schedtst.cpp $(AUX)
	g++ $(OPTIONS) $(CCFLAGS) -Ofast -std=c++17 -D GFP -o gfp_test schedtst.cpp $(AUX)

clean: 
	rm gfp





