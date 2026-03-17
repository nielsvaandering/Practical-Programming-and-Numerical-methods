CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS = -lstdc++ -lm -lpthread

Decay.svg: Out.txt Fit_result.txt #Makefile
	echo '\
		load "Fit_result.txt" ;\
		title_str = sprintf("f(t) = %.5f * exp(-%.5f * t)", alpha, lambda) ;\
		set terminal svg background "white" ;\
		set output "$@" ;\
		set xlabel "Time (years)" ;\
		set ylabel "Activity" ;\
		plot "$<" using 1:2:3 with yerrorbars title "Rutherford and Soddy datapoints", \
		f(x) with lines title title_str ,\
		g(x) with lines title "c+dc",\
		h(x) with lines title "c-dc";\
		' | tee log.times | gnuplot

Out.txt Fit_function.txt: main
	./$< > $@

main: main.o fit.o qr.o

main.o: main.cpp

qr.o: qr.cpp qr.hpp matrix.hpp

fit.o: qr.hpp fit.cpp fit.hpp matrix.hpp

clean:
	rm *.svg *.txt main *.o log.times
