CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS = -lstdc++ -lm -lpthread
TIME = time --format "$$nthreads %e %U" --append --output $@

Out.txt: main
	./main -n 10 -m 7 > $@

main: main.o qr.o make_test_matrix.o 
	$(CXX) -o main main.o qr.o make_test_matrix.o $(LDLIBS)

main.o: main.cpp make_test_matrix.hpp matrix.hpp qr.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

qr.o: qr.cpp matrix.hpp qr.hpp
	$(CXX) $(CXXFLAGS) -c qr.cpp -o qr.o

make_test_matrix.o: make_test_matrix.cpp make_test_matrix.hpp
	$(CXX) $(CXXFLAGS) -c make_test_matrix.cpp -o make_test_matrix.o

clean:
	rm -f *.o main Out.txt

#test_matrix.txt: make_test_matrix
#	./make_test_matrix -n 10 -m 8 > $@

#make_test_matrix: make_test_matrix.o 

#make_test_matrix.o: make_test_matrix.cpp




# Clean rule to remove generated files
#clean:
#	rm -f $(TARGET) *.o test_matrix.txt make_test_matrix


