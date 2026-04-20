CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS = -lstdc++ -lm -lpthread


Out.txt: main
	./$< > $@

main: main.o Root_finding.o qr.o

main.o: main.cpp

Root_finding.o: qr.hpp Root_finding.hpp Root_finding.cpp

qr.o: matrix.hpp qr.hpp qr.cpp

clean:
	rm *.txt *.o main