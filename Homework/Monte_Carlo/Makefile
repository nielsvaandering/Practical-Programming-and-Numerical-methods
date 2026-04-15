CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS = -lstdc++ -lm -lpthread

all: Out.txt Error_area_circle.svg 

Error_area_circle.svg: area_circle.txt #Makefile
	echo '\
		set terminal svg background "white" ;\
		set output "$@" ;\
		set title "MC integration circle. The estimated error compared to acual error as function of N";\
		set logscale x ;\
		set xlabel "Number of evaluations (N)" ;\
		set ylabel "Error" ;\
		plot "$<" using 1:3 with linespoints title "Estimated error", \
		"$<" using 1:4 with linespoints title "Actual error"; \
		' | tee log.erf | gnuplot

Out.txt area_circle.txt: main
	./$< > $@

main: main.o MC.o 

main.o: main.cpp

MC.o: MC.hpp MC.cpp

clean:
	rm *.txt main *.o