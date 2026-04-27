CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS = -lstdc++ -lm -lpthread


Out.txt: main
	./$< > $@

main: main.o minimization.o qr.o 

main.o: main.cpp

minimization.o: matrix.hpp qr.hpp minimization.hpp minimization.cpp

qr.o: matrix.hpp qr.hpp qr.cpp

clean:
	rm *.txt main *.o