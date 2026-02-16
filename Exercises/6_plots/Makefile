CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS = -lstdc++ -lm

All: 1_erf.svg 2_gamma.svg 3_lngamma.svg

1_erf.svg: test_data.txt
	echo '\
	set terminal svg background "white" ;\
	set output "$@" ;\
	set key right bottom ;\
	set tics out ;\
	set xlabel "x" ;\
	set ylabel "y" ;\
	plot [-5:5][-1.2:1.2] \
		"$<" index 0 using 1:2 with points title "erf approximation", \
		erf(x) title "exact erf(x)" with lines ;\
	' | tee log.erf.gpi | gnuplot

2_gamma.svg: test_data.txt
	echo '\
	set terminal svg background "white" ;\
	set output "$@" ;\
	set key right bottom ;\
	set tics out ;\
	set zero 0 ;\
	set xzeroaxis linetype -1 linecolor rgb "black" ;\
	set yzeroaxis linetype -1 linecolor rgb "black" ;\
	set format x "%g"  ;\
	set format y "%g" ;\
	set xtics axis ;\
	set ytics axis ;\
	set samples 4000 ;\
	set arrow from -4,graph(0,0) to -4,graph(1,1) nohead dt 2 lc rgb "blue" ;\
	set arrow from -3,graph(0,0) to -3,graph(1,1) nohead dt 2 lc rgb "blue" ;\
	set arrow from -2,graph(0,0) to -2,graph(1,1) nohead dt 2 lc rgb "blue" ;\
	set arrow from -1,graph(0,0) to -1,graph(1,1) nohead dt 2 lc rgb "blue" ;\
	set arrow from 0,graph(0,0) to 0,graph(1,1) nohead dt 2 lc rgb "blue" ;\
	plot [-5:5][-5:5] \
		"$<" index 1 using 1:2 with points title "gamma approximation", \
		gamma(x) title "gamma(x)" with lines lc rgb "red";\
	' | tee log.gamma.gpi | gnuplot
	
3_lngamma.svg: test_data.txt
	echo '\
	set terminal svg background "white" ;\
	set output "$@" ;\
	set key right bottom ;\
	set tics out ;\
	set zero 0 ;\
	set xzeroaxis linetype -1 linecolor rgb "black" ;\
	set yzeroaxis linetype -1 linecolor rgb "black" ;\
	set format x "%g"  ;\
	set format y "%g" ;\
	set xtics axis ;\
	set ytics axis ;\
	set samples 4000 ;\
	set arrow from -4,graph(0,0) to -4,graph(1,1) nohead dt 2 lc rgb "blue" ;\
	set arrow from -3,graph(0,0) to -3,graph(1,1) nohead dt 2 lc rgb "blue" ;\
	set arrow from -2,graph(0,0) to -2,graph(1,1) nohead dt 2 lc rgb "blue" ;\
	set arrow from -1,graph(0,0) to -1,graph(1,1) nohead dt 2 lc rgb "blue" ;\
	set arrow from 0,graph(0,0) to 0,graph(1,1) nohead dt 2 lc rgb "blue" ;\
	plot [0:5][-5:5] \
		"$<" index 2 using 1:2 with points title "lngamma approximation", \
		log(gamma(x)) title "log(gamma(x))" with lines lc rgb "red";\
	' | tee log.lngamma.gpi | gnuplot

test_data.txt: main Makefile
	./$< -xmin -5 -xmax 5 -dx 0.25 > $@ 2>log.txt

clean:
	rm *.txt [Ll]og* main *.svg 