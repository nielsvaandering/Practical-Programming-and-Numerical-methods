#include"matrix.hpp"
#include"EVD.hpp"
#include"random_symmetric_matrix.hpp"
#include"hydrogen_SE.hpp"
#include<iostream>
#include<string>
#include <fstream>

int main(int argc, char *argv[]){
    int N = 10; // Default number for square matrix
    double rmax = 10.0; //default for rmax hydrogen SE
    double dr = 0.1; //Default for dr in hydrogen SE


    for (int i = 0; i < argc; ++i) {
        std::string arg = argv[i];
        if(arg == "-N" && (i+1) < argc){
            N = std::stoi(argv[i+1]);
        }
        else if(arg == "-rmax" && (i+1) < argc){
            rmax = std::stod(argv[i+1]);
        }
        else if(arg == "-dr" && (i+1) < argc){
            dr = std::stod(argv[i+1]);
        }
    }



    pp::matrix A(N,N);
    random_symmetric_matrix(A);
    //std::cout << "Entering jacobi\n";
    auto [V,D] = pp::EVD::jacobi(A);
    //std::cout << "Exiting jacobi\n";
    std::cout << "Symmetric matrix A:";
    A.print();
    std::cout << "\nMatrix V with eigenvectors:";
    V.print();
    std::cout << "\nEigen values\n";
    D.print();

    //The checks we are asked to compute: V^T A V = D, V D V^T = A, V^T V = V V^T = 1
    pp::matrix VT_A_V = V.transpose() * A * V;

    //Note:it usually should be V^T D V, instead of V D V^T, but A is symmetric, so there is no difference.
    //Since I store the eigenvalues in a vector, instead of the complete diagonal matrix, I have to do the matrix multiplication explicitly
    //Since D is diagonal, V D multiplied column V[i] by the i'th dianonal element of D.
    pp::matrix VT_D_V = V ;
    for(int i = 0; i < N;i++){
        VT_D_V[i] *= D[i] ;
    }
    VT_D_V = VT_D_V *V.transpose();

    pp::matrix VT_V = V.transpose() * V;
    pp::matrix V_VT = V * V.transpose();

    std::cout << "\nCheck V^T A V = D:";
    VT_A_V.print();
    std::cout <<"\nWe can see that the diagonal is exactly the matrix D, and the off-diagonal elements are small (~10^-8-10^-15). \nCheck V^T D V = A:";
    VT_D_V.print();
    std::cout <<"\nComparing with matrix A (see top), we see that they are the same.\nCheck V^T V =  V V^T = 1 (output in that order) \nWe can see that for both the diagonal is 1, and the off-diagonal is of order ~10^-15";
    V_VT.print();
    VT_V.print();

    std::cout << "For part B, see .svg plots. To compare the wavefunctions, I googled 'veigenfunctions hydrogen s-wave radial SE', and compared it with the first result \n";
    //Printing the matrix where the columns are the eigenfunctions of the Hamiltonian for part B
    std::ofstream outfile("Wavefunctions.txt");
    auto [F,E] = hydrogen_SE(rmax, dr);
    //I would only want the first few eigenfunctions, so I will not use the F.print(). For plotting I also need the corresponding r for each value
    //std::cout << "For plotting first few eigenfunctions of the hydrogen s-wave hamiltonian. output: r, f_1, f_2, f_3\n\n";
    for(int i = 0; i<F.rows(); i++){
        outfile << (i+1)*dr << " " << F[i,0] / std::sqrt(dr) << " " << F[i,1] / std::sqrt(dr)<< " " << F[i,2] / std::sqrt(dr) << "\n";
    }
    outfile.close();

    return 0;
}