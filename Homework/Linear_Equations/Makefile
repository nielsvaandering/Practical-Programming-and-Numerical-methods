CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS = -lstdc++ -lm -lpthread

all: Out.txt Times.svg

Times.svg: out.times Makefile
	echo '\
		set terminal svg background "white" ;\
		set output "$@" ;\
		set xlabel "N: rows/columns matrix" ;\
		set ylabel "running time" ;\
		a = 1;b = 1; c = 1; d = 1;\
		f(x) = a + b* x + c* x**2 + d * x**3;\
		fit f(x) "$<" using 1:2 via a,b,c,d ;\
		plot "$<" using 1:2 with linespoints title "times QR factorisation of NxN matrix", \
		f(x) title "fit with a + b x + c x^2 + d x^3" ;\
		' | tee log.times | gnuplot


#i get out_times of 0.01 to 0.03-0.04 on my own laptop for N=100 and N=200 respectively, So I will have to get a little bit bigger
out.times : main2 #Makefile
	>$@
	rm -f out err
	for N in $$(seq 100 100 2000); do \
		time --format "$$N %e" --output $@ --append \
		./$< -N $$N 1>>out 2>>err ;\
	done

main2: main2.o qr.o make_test_matrix.o 

main2.o: main2.cpp  

Out.txt: main #Makefile
	./main -n 10 -m 7 -N 10 > $@

main: main.o qr.o make_test_matrix.o 

main.o: main.cpp make_test_matrix.hpp 

qr.o: qr.cpp qr.hpp matrix.hpp

make_test_matrix.o: make_test_matrix.cpp make_test_matrix.hpp

clean:
	rm -f *.o main main2 Out.txt out *.times err *.svg *.log
