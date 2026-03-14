#include "fit.hpp"
#include"matrix.hpp"
#include"qr.hpp"
#include<vector>
#include<functional>
#include<utility>

//Input: Vector with functions for the fit, vector with x-values, vector with measured values, and vector with the errors on the measured values
//The output is a vector of the c_i values what should go in front of f_i, to minimize chi^2
std::pair<pp::vector,pp::matrix> lsfit(const std::vector<std::function<double(double)>>& fs, const pp::vector& x, const pp::vector& y, const pp::vector& dy)
{
    //I follow the lecture notes, and all we have to do is build a matrix A, where A_{ik} = f_k(x_i) / Delta y_i, a vector b where b_i = y_i / Delta y_i,
    //and then call the solve(A,b) function from QR-factorisation (homework linear equations). The output vector contains the c_i values corresponding to f_i

    //Build matrix A
    int n = y.size();
    int m = fs.size();
    pp::matrix A(n,m);
    for(int i = 0; i < n;i++){
        for(int j = 0; j< m;j++){
            A.set(i,j,fs[j](x[i]) / dy[i]);
        }
    }
    auto [Q,R] = pp::qr::QR_decompose(A);

    //Build vector b:
    pp::vector b(n);
    for(int i = 0;i<n;i++){
        b[i] = y[i] / dy[i];
    }

    pp::vector c = pp::qr::solve_QR(Q,R,b);

    //The covariance matrix is given by (A^T A)^-1 (lecture notes).
    //This can be rewritten to R^-1 (R^-1)^T
    pp::matrix R_inv = pp::qr::R_inverse(R);
    pp::matrix Cov = R_inv * R_inv.transpose();

    return std::make_pair(c,Cov);
}