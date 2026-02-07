CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LINK.o = $(CXX) $(LDFLAGS)
LDLIBS = -lstdc++ -lm

Out.txt : main
	./main > Out.txt

main : main.o 

main.o : main.cpp

clean :
	rm -f main main.o Out.txt 