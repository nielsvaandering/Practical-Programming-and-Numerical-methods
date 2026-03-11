#include<iostream>
#include<fstream>
#include"qr.hpp"
#include"matrix.hpp"
#include"make_test_matrix.hpp"

//This function is only to time the QR factorization for an NxN matrix. It is seperate, so we really time QR, and not the other implementations.

int main(int argc, char *argv[]){
    //initializing a random matrix
    int N = 10; // Default number for square matrix
    for (int i = 0; i < argc; ++i) {
        std::string arg = argv[i];
    if(arg == "-N" && (i+1) < argc){
        N = std::stoi(argv[i+1]);
    }
}
    //Fill the matrix with random values
    pp::matrix A(N,N);
    generate_random_matrix(A);

    auto [Q,R] = pp::qr::QR_decompose(A);
    //I dont want to print anything, since I filled a file up to 602 MB when timing it with N up to 2000
    /*
    std::cout << "Q:";
    Q.print();
    std::cout<<"R:";
    R.print();
    */

return 0;
}