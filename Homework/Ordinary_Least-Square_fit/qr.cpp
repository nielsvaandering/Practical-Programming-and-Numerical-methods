#include<iostream>
#include<vector>

#include"matrix.hpp"
#include"qr.hpp"

namespace pp {
    

std::pair<matrix, matrix> qr::QR_decompose(const matrix& A){
    int m = A.size2();

    matrix Q = A;
    matrix R(m,m);
    for(int i = 0; i < m; i++){
        R[i][i] = Q[i].norm();
        Q[i] /= R[i][i];
        for(int j = i+1; j<m;j++){
            R[i,j] =Q[i].dot(Q[j]);
            Q[j] -= R[j][i] * Q[i]; 
        }
    }
    return std::make_pair(Q, R);
}//QR_decomposition


//Function to solve Ax = b
// We do this by first decomposing A in QR, and then use back-substitution
vector qr::solve(const matrix& A, const vector& b){

    //First decompose A in QR
    auto [Q,R] = pp::qr::QR_decompose(A); 
    vector b_prime = Q.transpose() * b;

    //We rewrite QR x = b to R x = Q^-1 b, and we use that Q^-1 = Q^T. We then solve R X = b', where b'= Q^T b.
    //We then use backsubstitution to find x.
    vector x = pp::qr::backsubstitution(R,b_prime);
    return x;
} // solve

//So save computations, it is sometimes benificiary to call qr, and then do the other rotines with the QR input, instad of qr-decomposing every time
vector qr::solve_QR(const matrix & Q, const matrix& R, const vector& b){
    vector b_prime = Q.transpose() * b;
    //We rewrite QR x = b to R x = Q^-1 b, and we use that Q^-1 = Q^T. We then solve R X = b', where b'= Q^T b.
    //We then use backsubstitution to find x.
    vector x = pp::qr::backsubstitution(R,b_prime);
    return x;
}

//Input diagonal matrix R, and vector b. Output is vector x, which solves Rx = b.
vector qr::backsubstitution(const matrix& R, const vector& b){
    int n = R.rows();
    vector x(n);
    //Start with x_n, and use backwards substitution
    for(int i = n - 1; i >= 0; i--){
        x[i] = b[i];
        for(int j = i + 1; j < n; j++){x[i] -= R[j][i] * x[j];}
    x[i] /= R[i][i] ;
}
return x;
} // backsubstitution


//Calculate the determinant of a matrix using QR factorisation. det(A) = det(Q) * det(R).
// Since R is upper-triangle matrix, the determinant is the product of the diagonal
// Since Q consists of othogonal vectors, its determinant is +- 1, so we only need it for the sign
double qr::det(const matrix& A){
    //Decompose A is QR
    auto result = pp::qr::QR_decompose(A); 
//    const pp::matrix& Q = result.first; 
    const pp::matrix& R = result.second;

    //Calculate det(R)
    double det_R = 1;
    for(int i=0;i<R.columns();i++){
        det_R *= R[i][i];
    }

    //Figure out the sign from Q. I have to think about how to do that in a smart way.
    double det_Q = 1;
    return det_R * det_Q;
}


//Calculating A^-1 using QR factorisation. We use the fact that 
//A^-1 = R^-1 Q^-1, where Q^-1 = Q^T, and we can find R^-1 by backsubstitution
matrix qr::inverse(const matrix& A){
    auto [Q,R] = qr::QR_decompose(A);
    matrix R_inverse = qr::R_inverse(R);
    matrix A_inverse =  R_inverse * Q.transpose();
    return A_inverse;
}//inverse

//Special subroutine, since I sometimes only need to call this one (I already have R, and don't want to extra QR decompose R)
matrix qr::R_inverse(const matrix& R){
    int N = R.rows();
    matrix R_inverse(N,N);
    //Column i of R^-1 can be found by backsubstituion of R with unit vector e_i
    for(int i = 0; i < N; i++){
        vector e_i(N);
        e_i[i] = 1;
        R_inverse[i] = qr::backsubstitution(R,e_i); 
    }
    return R_inverse;
}

} // namespace pp
