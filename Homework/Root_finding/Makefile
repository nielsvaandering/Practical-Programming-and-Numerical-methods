CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS = -lstdc++ -lm -lpthread

all: Convergence_rmax.svg Convergence_rmin_acc_eps.svg Hydrogen_S_wave.svg

Convergence_rmax.svg: Out.txt #Makefile
	echo '\
		set terminal svg background "white" ;\
		set output "$@" ;\
		set title "Convergence for different values inside the ODE";\
		set ylabel "error";\
		set logscale y;\
		plot "$<" index 2 using 3:4 with linespoints title "rmax";\
		' | tee log.times | gnuplot

Convergence_rmin_acc_eps.svg: Out.txt #Makefile
	echo '\
		set terminal svg background "white" ;\
		set output "$@" ;\
		set title "Convergence for different values inside the ODE";\
		set ylabel "error";\
		set logscale x;\
		set logscale y;\
		plot "$<" index 2 using 1:2 with linespoints title "rmin",\
		"$<" index 2 using 5:6 with linespoints title "acc",\
		"$<" index 2 using 7:8 with linespoints title "eps",\
		' | tee log.times | gnuplot

Hydrogen_S_wave.svg: Out.txt #Makefile
	echo '\
		set terminal svg background "white" ;\
		set output "$@" ;\
		set title "Hydrogen s-wavefunction";\
		set xlabel "r";\
		f(x) = x * exp(-x) ;\
		plot "$<" index 1 using 1:2 with linespoints title "S_0 hydrogen",\
		f(x) title "f_0(r)=r e^{-r}" with lines;\
		' | tee log.times | gnuplot


Out.txt: main
	./$< > $@

main: main.o Root_finding.o qr.o ODE.o 

main.o: main.cpp

Root_finding.o: qr.hpp Root_finding.hpp Root_finding.cpp

qr.o: matrix.hpp qr.hpp qr.cpp

ODE.o: matrix.hpp ODE.hpp ODE.cpp

clean:
	rm *.txt *.o main *.svg log.*