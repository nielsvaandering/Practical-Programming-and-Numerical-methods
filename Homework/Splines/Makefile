CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS = -lstdc++ -lm -lpthread

all: Quadratic_interpolation1.svg Quadratic_interpolation2.svg Cubic_interpolation2.svg Linear_interpolation.svg

Cubic_interpolation2.svg: Out2.txt cubic_interpolation.txt
	echo '\
		set terminal svg background "white" ;\
		set output "$@" ;\
		set xlabel "x" ;\
		set ylabel "y" ;\
		plot "$<" using 1:6 with points title " y = 3cos(x) - 2sin(2x)", \
			"cubic_interpolation.txt" using 1:2 with points title "interpolation (my code)", \
     		"cubic_interpolation.txt" using 1:3 with points title "interpolation Integral" ,\
			"cubic_interpolation.txt" using 1:2 smooth csplines title "gnuplot cubic spline" ;\
		' | tee log.times | gnuplot

Quadratic_interpolation2.svg: Out2.txt quadratic_interpolation.txt
	echo '\
		set terminal svg background "white" ;\
		set output "$@" ;\
		set xlabel "x" ;\
		set ylabel "y" ;\
		plot "$<" using 1:4 with points title "linear", \
			"$<" using 1:5 with points title "quadratic", \
			"quadratic_interpolation.txt" using 1:6 with points title "interpolation y = x", \
     		"quadratic_interpolation.txt" using 1:7 with points title "interpolation y = x Integral" ,\
			"quadratic_interpolation.txt" using 1:8 with points title "interpolation y = x^2", \
     		"quadratic_interpolation.txt" using 1:9 with points title "interpolation y = x^2 Integral" ;\
		' | tee log.times | gnuplot

Quadratic_interpolation1.svg: Out2.txt quadratic_interpolation.txt
	echo '\
		set terminal svg background "white" ;\
		set output "$@" ;\
		set xlabel "x" ;\
		set ylabel "y" ;\
		plot "$<" using 1:2 with points title "cos(x)", \
			"$<" using 1:3 with points title "constant", \
     		"quadratic_interpolation.txt" using 1:2 with points title "interpolation cos(x)", \
     		"quadratic_interpolation.txt" using 1:3 with points title "interpolation cos(x) Integral" ,\
			"quadratic_interpolation.txt" using 1:4 with points title "interpolation const", \
     		"quadratic_interpolation.txt" using 1:5 with points title "interpolation const Integral" ;\
		' | tee log.times | gnuplot

Linear_interpolation.svg: Out.txt linear_interpolation.txt
	echo '\
		set terminal svg background "white" ;\
		set output "$@" ;\
		set xlabel "x" ;\
		set ylabel "y" ;\
		plot "$<" using 1:2 with points title "cos(x)", \
     		"linear_interpolation.txt" using 1:2 with points title "Linear_interpolation", \
     		"linear_interpolation.txt" using 1:3 with points title "Linear_interpolation Integral" ;\
		' | tee log.times | gnuplot

Out2.txt quadratic_interpolation.txt cubic_interpolation.txt: main2
	./$< > $@

main2: main2.o

main2.o: spline.hpp matrix.hpp


Out.txt linear_interpolation.txt: main
	./$< > $@

main: main.o

main.o: spline.hpp matrix.hpp

clean: 
	rm *.svg *.txt log.times main main2 *.o 