#include"matrix.hpp"
#include"EVD.hpp"
#include"random_symmetric_matrix.hpp"
#include<string>

//Code for part C: The only purpose is to time the scaling of the Jacobi EVD algorithm.
int main(int argc, char *argv[]){
    int N = 10; // Default number for square matrix
        for (int i = 0; i < argc; ++i) {
        std::string arg = argv[i];
        if(arg == "-N" && (i+1) < argc){
            N = std::stoi(argv[i+1]);
        }
    }
    pp::matrix A(N,N);
    random_symmetric_matrix(A);
    //std::cout << "Entering jacobi\n";
    auto [V,D] = pp::EVD::jacobi(A);

    return 0;
}