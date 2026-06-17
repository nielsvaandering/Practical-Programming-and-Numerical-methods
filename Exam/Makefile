CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS = -lstdc++ -lm -lpthread

all: Out.txt Error_erf1.svg Erf_z.svg

Erf_z.svg: erf_z.txt Makefile
	echo '\
		set terminal svg background "white" ;\
		set output "$@" ;\
		set xlabel "z" ;\
		set ylabel "erf(z)" ;\
		set title "calculated erf(z) with erf(z) from gnuplot" ;\
		plot "$<" using 1:2 with points title "Calculated erf(z)" ,\
		erf(x) ;\
		' | tee log.erf_z | gnuplot


Error_erf1.svg: erf1.txt #Makefile
	echo '\
		set terminal svg background "white" ;\
		set output "$@" ;\
		set logscale xy ;\
		set xlabel "acc" ;\
		set ylabel "error" ;\
		set xrange [] reverse ;\
		set title "Difference implementation of erf(1) and tabulated value as function of acc" ;\
		plot "$<" using 1:2 with linespoints title "calculated erf(1) - tabulated erf(1)";\
		' | tee log.erf_error | gnuplot

Out.txt erf1.txt erf_z.txt: main
	./$< >$@

main: main.o adaptive3.o 

main.o: main.cpp adaptive3.hpp

adaptive3.o: adaptive3.hpp adaptive3.cpp

clean:
	rm *.txt *.o *.svg main log*