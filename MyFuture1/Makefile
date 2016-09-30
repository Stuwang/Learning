COMPLILE=clang++ -std=c++11 -O2 -c

LINKE=clang++ -std=c++11 -O2 -pthread

TARGETS=main.out

%.out:%.cpp
	${LINKE} $< -o $@

.DEFAULT:all

all:${TARGETS}

clean:
	rm *.out *.o -rf
