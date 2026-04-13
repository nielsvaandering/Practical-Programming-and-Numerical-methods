CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS = -lstdc++ -lm -lpthread

all: Out.txt Error_function.svg Error_function_error.svg

Error_function.svg: error_function.txt #Makefile
	echo '\
		set terminal svg background "white" ;\
		set output "$@" ;\
		set title "My implementation erf(z) compared to std::erf(z)";\
		plot "$<" using 1:2 with linespoints title "my implementation erf(z)", \
		"$<" using 1:3 with linespoints title "std::erf(z)"; \
		' | tee log.erf | gnuplot

Error_function_error.svg: erf1.txt #Makefile
	echo '\
		set terminal svg background "white" ;\
		set output "$@" ;\
		set logscale xy ;\
		set xlabel "acc" ;\
		set ylabel "error" ;\
		set title "Difference my implementation erf(z) and tabulated value" ;\
		plot "$<" using 1:2 with linespoints;\
		' | tee log.erf_error | gnuplot

Out.txt erf1.txt error_function.txt: main
	./$< > $@

main: main.o integration.o 

main.o: main.cpp

integration.o: integration.hpp integration.cpp

clean:
	rm *.txt *.o *.svg log.* main