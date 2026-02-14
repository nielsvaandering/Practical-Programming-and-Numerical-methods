CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS = -lstdc++ -lm

Out_test.txt : test_vec
	./test_vec > $@

test_vec: test_vec.o vec.o

test_vec.o: test_vec.cpp vec.hpp

vec.o: vec.hpp vec.cpp

clean:
	rm -f *.o Out_test.txt test_vec
