CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS = -lstdc++ -lm
Out.txt : main
	./main > Out.txt

main : main.o 
	c++ main.o -o main $(LDLIBS)

main.o : Hello_World.cpp
	c++ $(CXXFLAGS) -c Hello_World.cpp -o main.o

clean :
	rm -f main main.o Out.txt