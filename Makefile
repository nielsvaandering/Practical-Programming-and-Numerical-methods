CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS = -lstdc++ -lm
Out.txt : main
	./main > Out.txt

main : main.o hello.o
	c++ main.o hello.o -o main $(LDLIBS)

main.o : hello.hpp main.cpp
	c++ $(CXXFLAGS) -c main.cpp -o main.o

hello.o : hello.hpp hello.cpp
	c++ $(CXXFLAGS) -c hello.cpp -o hello.o

clean :
	rm -f main main.o hello.o Out.txt