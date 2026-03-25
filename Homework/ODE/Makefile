CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS = -lstdc++ -lm -lpthread

all: Example_scipy_odeint.svg First_test.svg

Example_scipy_odeint.svg: Out.txt Makefile
	echo '\
		set terminal svg background "white" ;\
		set output "$@" ;\
		plot "$<" index 1 using 1:2 with linespoints title "theta(t)", \
		"$<" index 1 using 1:3 with linespoints title "omega(t)"; \
		' | tee log.times | gnuplot

First_test.svg: Out.txt #Makefile
	echo '\
		set terminal svg background "white" ;\
		set output "$@" ;\
		plot "$<" using 1:3 with linespoints title "Solving u'' = -u"; \
		' | tee log.times | gnuplot

Out.txt: main
	./$< > $@

main: main.o ODE.o 

main.o: main.cpp

ODE.o: ODE.hpp ODE.cpp matrix.hpp