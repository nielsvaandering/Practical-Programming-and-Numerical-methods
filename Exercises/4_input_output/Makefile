CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS = -lstdc++ -lm

all : Out1.txt Out2.txt Out3.txt

Out1.txt: main
	./main -n 1 -n 2 -n 3 -n 4 -n 5 > Out.txt

Out2.txt: main2 input.txt
	./main2 < input.txt > Out2.txt

Out3.txt: main3 input.txt
	./main3 --input input.txt --output Out3.txt

clean: 
	rm -f main main2 main3 Out.txt Out2.txt Out3.txt