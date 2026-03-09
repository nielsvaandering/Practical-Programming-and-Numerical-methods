#include<iostream>
#include<fstream>
#include"qr.hpp"
#include"matrix.hpp"
#include"make_test_matrix.hpp"
/*
The structure of the code:
-read in the dimensions of the matrix from terminal
-generate a random matrix A with specified dimensions
-call QR-factorisation on the matrix, and check the results
*/
int main(int argc, char *argv[]){
    //initializing a random matrix
    int n = 10; // Default number of rows
    int m = 7;  // Default number of columns

    for (int i = 0; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-n" && (i + 1) < argc) {
            n = std::stoi(argv[i + 1]); 
        } 
        else if (arg == "-m" && (i + 1) < argc) {
            m = std::stoi(argv[i + 1]); 
        }
    }
    pp::matrix A(n,m);
    generate_random_matrix(A);

    // For debugging
    /*
    A.print();
    std::cout<< "check\n";
    pp::vector tmp=A[0];
    std::cout << "calling dot..." << std::endl;
    std::cout << tmp.dot(tmp) << std::endl;

    std::cout << "calling QR_decomp..." << std::endl;
    */
    pp::QRResult result = pp::QR_decompose(A);
    //std::cout << "QR_decomp exited..." << std::endl;
    pp::matrix Q = result.Q;
    pp::matrix R = result.R;

    std::cout << "matrix Q:\n";
    Q.print();
    std::cout << "matrix R:\n";
    R.print();
    std::cout << "check that Q^T Q = 1 We see that the off-diagonal elements are of order 10^-16-10^-17. This has to do with machine precision.\n";
    pp::matrix QtQ = Q.transpose() * Q;
    QtQ.print();
    std::cout << "check that QR = A: First QR, then A. We can see that they are the same.\n";
    pp::matrix QR = Q * R;
    QR.print();
    A.print();

    return 0;
}


