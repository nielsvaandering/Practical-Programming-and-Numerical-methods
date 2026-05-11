CXXFLAGS = -Wall -Wextra -std=c++23 -O #-Werror 
LDLIBS = -lstdc++ -lm -lpthread

Derivative.svg: Out.txt Makefile
	echo '\
		set terminal svg background "white" ;\
		set output "$@" ;\
		set xlabel "x" ;\
		set ylabel "y" ;\
		set title "Derivative and 2nd derivative of cos(5x - 1)exp(-x^2)" ;\
		f(x) = exp(-x**2) * (-5 * sin(5 * x - 1) - 2 * x * cos(5 * x - 1)) ;\
		g(x) = exp(-x**2) * ((4 * x**2 - 27) * cos(5 * x - 1) + 20 * x * sin(5 * x - 1)) ;\
		plot "$<" index 1 using 1:2 with points title "Derivative (from Neural network)", \
		"$<" index 1 using 1:3 with points title "2nd derivative (from Neural network)", \
		f(x) title "df / dx " ,\
		g(x) title " d^2 f / dx^2 ";\
		' | tee log.deriv | gnuplot

Out.txt: main
	./$< > $@

main: main.o minimization.o qr.o integration.o

main.o: main.cpp neural_network.hpp

minimization.o: qr.hpp minimization.hpp minimization.cpp

qr.o: qr.hpp qr.cpp matrix.hpp

integration.o: integration.hpp integration.cpp matrix.hpp

clean:
	rm main *.txt *.o *.svg log.deriv