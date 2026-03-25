CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS = -lstdc++ -lm -lpthread

all: Example_scipy_odeint.svg First_test.svg B_precession_planet.svg

B_precession_planet.svg: Out.txt Makefile
	echo '\
		set terminal svg background "white" ;\
		set output "$@" ;\
		set size ratio 1 ;\
		plot "$<" index 2 using (1/$$2)*cos($$1):(1/$$2)*sin($$1) with points title "B1", \
		"$<" index 3 using (1/$$2)*cos($$1):(1/$$2)*sin($$1) with lines title "B2", \
		"$<" index 4 using (1/$$2)*cos($$1):(1/$$2)*sin($$1) with lines dashtype 2 title "B3"; \
		' | tee log.times | gnuplot

Example_scipy_odeint.svg: Out.txt #Makefile
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
		plot "$<" index 0 using 1:3 with linespoints title "Solving ü = -u"; \
		' | tee log.times | gnuplot

Out.txt: main
	./$< > $@

main: main.o ODE.o 

main.o: main.cpp

ODE.o: ODE.hpp ODE.cpp matrix.hpp

clean:
	rm *.svg *.o log.times *.txt main