#include<iostream>
#include<fstream>
#include"qr.hpp"
#include"matrix.hpp"
#include"make_test_matrix.hpp"
/*
The structure of the code:
-read in the dimensions of the matrix from terminal
-generate a random matrix A with specified dimensions
-call all functions related to QR-factorisation on the matrix, and check the results
*/
int main(int argc, char *argv[]){
    //initializing a random matrix
    int n = 10; // Default number of rows
    int m = 7;  // Default number of columns
    int N = 10; // Default number for square matrix

    for (int i = 0; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-n" && (i + 1) < argc) {
            n = std::stoi(argv[i + 1]); 
        } 
        else if (arg == "-m" && (i + 1) < argc) {
            m = std::stoi(argv[i + 1]); 
        }
        else if(arg == "-N" && (i+1) < argc){
            N = std::stoi(argv[i+1]);
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
    auto [Q,R] = pp::qr::QR_decompose(A);  
    //std::cout << "QR_decomp exited..." << std::endl;

    std::cout << "matrix Q:\n";
    Q.print();
    std::cout << "matrix R:\n";
    R.print();
    std::cout << "check that Q^T Q = 1. We see that the off-diagonal elements are of order 10^-16-10^-17. This has to do with machine precision.\n";
    pp::matrix QtQ = Q.transpose() * Q;
    QtQ.print();
    std::cout << "check that QR = A: First QR, then A. We can see that they are the same.\n";
    pp::matrix QR = Q * R;
    QR.print();
    A.print();

    //I will use B in my code, but to be consistent with the question, think of it as a square matrix A of dimension N x N.
    //We start by solving Ax = b
    pp::matrix B(N,N);
    generate_random_matrix(B);

    // Doing a little bit complicated to generate a vector b. A vector is just a matrix of dimension Nx1,
    // So I generate a random Nx1 matrix, but I need to enter a vector for b and not a matrix.
    pp::matrix c(N,1);
    generate_random_matrix(c);
    pp::vector& b = c[0];
    
    //Check function for solving Ax = b
    //std::cout << "entering backsubstitution\n";
    pp::vector x = pp::qr::solve(B,b);
    //std::cout << "Exiting backsubstitution\n"; 
    std::cout << "\n\nSolving Ax = b:\nMatrix A: \n";
    B.print();
    std::cout << "vector b:\n";
    b.print();
    std::cout << "Solution x:\n";
    x.print();
    std::cout << "Check for Ax:\n";
    (B * x).print();

    //Calculation of the determinant:
    double det_B = pp::qr::det(B);
    std::cout << "Calculating the Determinant of the previous matrix:\n" << det_B << "\n";

    //Calculating the inverse:
    std::cout << "Calculating the inverse of the previous matrix:\n";
    pp::matrix B_inverse = pp::qr::inverse(B);
    B_inverse.print();
    std::cout << "Checking the inverse by calculating A A^-1:\n";
    pp::matrix BB_inverse = B * B_inverse;
    BB_inverse.print();
    std::cout <<"We can see that the diagonal is 1, and the off-diagonal is of order 10^-14, due to round-off errors/machine precision\n";

    return 0;
}


