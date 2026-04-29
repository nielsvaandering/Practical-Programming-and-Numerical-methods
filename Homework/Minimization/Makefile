CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O  
LDLIBS = -lstdc++ -lm -lpthread

all: Out.txt Higgs_plot.svg

#f(x) = A/((x - m)**2 + (Gamma**2)/4);\
#		A = 100; m = 125; Gamma = 1;\
#		fit f(x) "higgs\_data.txt" using 1:2:3 via A,m,Gamma;\		

Higgs_plot.svg: higgs_data.txt Fit_result.txt #Makefile
	echo '\
		load "Fit_result.txt" ;\
		title_str = sprintf("f(E) = %.3f /  ((E - %.3f)^2 + %.3f ^2 / 4)", A, m, Gamma) ;\
		set terminal svg background "white" ;\
		set output "$@" ;\
		set title "Higgs data + fit";\
		set ylabel "Signal";\
		set xlabel "Energy (E)";\
		set samples 1000 ;\
		plot "$<" using 1:2:3 with yerrorbars title "Higgs data",\
		f(x) with lines title title_str ;\
		' | tee log.higgs | gnuplot


Out.txt Fit_result.txt: main higgs_data.txt
	./$< < higgs_data.txt 1> $@ 2>log

main: main.o minimization.o qr.o 

main.o: main.cpp

minimization.o: matrix.hpp qr.hpp minimization.hpp minimization.cpp

qr.o: matrix.hpp qr.hpp qr.cpp

clean:
	rm Out.txt Fit_result.txt main log* *.o *.svg *.log
