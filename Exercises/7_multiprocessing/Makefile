CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS = -lstdc++ -lm -lpthread
TIME = time --format "$$nthreads %e %U" --append --output $@

#Once all the times are in, you want to comment Makefile in out.times and uncomment it here
Times.svg: out.times Makefile
	echo '\
		set terminal svg background "white" ;\
		set output "$@" ;\
		set xlabel "number of threads" ;\
		set ylabel "running time" ;\
		a = 1; b = 10 ;\
		f(x) = a + b / x ;\
		fit f(x) "$<" using 1:2 via a,b ;\
		plot "$<" using 1:2 with linespoints title "times", \
		f(x) title "fit with 1/n" ;\
		' | tee log.times | gnuplot


N = 1e9
out.times : main #Makefile
	>$@
	>log.main
	for nthreads in 1 2 3 4 5 6 7 8 9 10 11 12 13 14; \
		do $(TIME) ./main -threads $$nthreads -nterms $(N) >> log.main ;\
	done

clean: 
	rm -f *.log log* main out.times *.svg