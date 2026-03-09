#include<iostream>
#include<vector>

#include"matrix.hpp"
#include"qr.hpp"

namespace pp {

QRResult QR_decompose(const matrix& A) {
    int n = A.size1();
    int m = A.size2();

    QRResult Re(n, m);

    Re.Q = A;

    for(int i = 0; i< m; i++){
	    Re.R[i][i] = Re.Q[i].norm();
	    Re.Q[i] /= Re.R[i][i];
        for(int j = i+1; j<m;j++){
		    Re.R[i,j] = Re.Q[i].dot(Re.Q[j]);
            Re.Q[j] -= Re.R[j][i] * Re.Q[i];
        }
    }

    return Re;
}
}









