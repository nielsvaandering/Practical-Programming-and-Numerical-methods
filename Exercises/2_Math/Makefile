CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LINK.o = $(CXX) $(LDFLAGS)
LDLIBS = -lstdc++ -lm

Out.txt : main
	./main > Out.txt

main : main.o sfuns.o

main.o : sfuns.hpp main.cpp

sfuns.o : sfuns.hpp sfuns.cpp

clean :
	rm -f main main.o Out.txt sfuns.o