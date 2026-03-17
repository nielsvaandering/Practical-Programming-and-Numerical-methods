CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS = -lstdc++ -lm -lpthread

#To finish part B: plot some lowest energy wavefunctions, and do part C:

all: Eigenfunctions_Hydrogen_SE.svg Change_rmax.svg Change_dr.svg Scaling.svg Out.txt 

#For part C: I will do the scaling exercise, to see that the algorithm runs as O(n^3)
Scaling.svg: times.txt #Makefile
	echo '\
		set terminal svg background "white" ;\
		set output "$@" ;\
		set xlabel "N" ;\
		set ylabel "time" ;\
		a = 1;b = 1; c = 1; d = 1;\
		f(x) = a + b* x + c* x**2 + d * x**3;\
		fit f(x) "$<" using 1:2 via a,b,c,d ;\
		plot "$<" using 1:2 with linespoints title "Lowest energy for different dr values with fixed rmax = 10" ,\
		f(x) title "fit with a + b x + c x^2 + d x^3" ;\
		' | tee log.dr | gnuplot

#The wavefunctions do match really well with what I found on the internet by googling "eigenfunctions hydrogen s-wave radial SE".
Eigenfunctions_Hydrogen_SE.svg: Wavefunctions.txt
	echo '\
		set terminal svg background "white" ;\
		set output "$@" ;\
		set datafile missing "" ;\
		set xlabel "r" ;\
		set ylabel "Psi(r)" ;\
		plot "$<" using 1:2 with linespoints title "Psi_1(r)", \
		"$<" using 1:3 with linespoints title "Psi_2(r)", \
		"$<" using 1:4 with linespoints title "Psi_3(r)"; \
		' | tee log.rmax | gnuplot

Change_rmax.svg: data_rmax.txt #Makefile
	echo '\
		set terminal svg background "white" ;\
		set output "$@" ;\
		set xlabel "rmax" ;\
		set ylabel "lowest energy" ;\
		set style line 2 linetype 2 linewidth 2 linecolor rgb "red" ;\
		plot "$<" using 1:3 with linespoints title "Lowest energy for different rmax values with fixed dr = 0.1", \
		-0.5 with lines linestyle 2 title "Exact lowest energy" ;\
		' | tee log.rmax | gnuplot

Change_dr.svg: data_dr.txt #Makefile
	echo '\
		set terminal svg background "white" ;\
		set output "$@" ;\
		set xlabel "dr" ;\
		set ylabel "lowest energy" ;\
		set style line 2 linetype 2 linewidth 2 linecolor rgb "red" ;\
		plot "$<" using 2:3 with linespoints title "Lowest energy for different dr values with fixed rmax = 10" ,\
		-0.5 with lines linestyle 2 title "Exact lowest energy" ;\
		' | tee log.dr | gnuplot

times.txt : main3 #Makefile
	>$@
	for N in $$(seq 100 100 1400); do \
		time --format "$$N %e" --output $@ --append \
		./$< -N $$N ;\
	done

main3: main3.o EVD.o random_symmetric_matrix.o

main3.o: main3.cpp  


data_dr.txt: main2
	>$@
	for dr in $$(seq 0.01 0.01 1); do \
		./$< -rmax 10 -dr $$dr >> data_dr.txt ;\
	done

data_rmax.txt: main2
	>$@
	for rmax in $$(seq 0.2 0.1 5); do \
		./$< -rmax $$rmax -dr 0.1 >> data_rmax.txt ;\
	done



main2: main2.o hydrogen_SE.o EVD.o

main2.o: main2.cpp

#After seeing the convergence plots for dr and rmax, rmax = 3 and dr = 0.01 does converge the energy, but I noticed changing rmax changes the wavefunctions.
#To compare with the plot online I found by googeling "eigenfunctions hydrogen s-wave radial SE", I am taking rmax to be  40
Out.txt Wavefunctions.txt: main
	./$< -N 20 -dr 0.05 -rmax 40 > $@

main: main.o EVD.o random_symmetric_matrix.o hydrogen_SE.o

main.o: main.cpp

EVD.o: EVD.hpp EVD.cpp matrix.hpp

random_symmetric_matrix.o: random_symmetric_matrix.hpp random_symmetric_matrix.cpp matrix.hpp

hydrogen_SE.o: hydrogen_SE.hpp hydrogen_SE.cpp EVD.hpp

clean: 
	rm -f main *.o *.txt *.svg main2 log* main3 *.log


