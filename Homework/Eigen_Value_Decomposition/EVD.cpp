#include"matrix.hpp"
#include"EVD.hpp"
#include<cmath>
#include<iostream>

namespace pp{
void EVD::timesJ(pp::matrix& A, int p, int q, double theta){
	double c=std::cos(theta), s=std::sin(theta);
	for(int i=0;i<A.size1();i++){
		double aip=A[i,p],aiq=A[i,q];
		A[i,p]=c*aip-s*aiq;
		A[i,q]=s*aip+c*aiq;
		}
}

void EVD::Jtimes(pp::matrix& A, int p, int q, double theta){
	double c=std::cos(theta),s=std::sin(theta);
	for(int j=0;j<A.size1();j++){
		double apj=A[p,j],aqj=A[q,j];
		A[p,j]= c*apj+s*aqj;
		A[q,j]=-s*apj+c*aqj;
		}
}

//Jacobi algorithm with sweeps. 
//It returns [diagonal matrix with eigenvalues, matrix with eigenvectors]
std::pair<pp::matrix, pp::vector> EVD::jacobi(matrix A){
    int n = A.rows();
    matrix V(n,n);
    V.setid();

    //std::cout << "Entering jacobi while loop\n";
    bool changed;
do{
	changed=false;
	for(int p=0;p<n-1;p++)
	for(int q=p+1;q<n;q++){
		double apq=A[p,q], app=A[p,p], aqq=A[q,q];
		double theta=0.5*std::atan2(2*apq,aqq-app);
		double c=std::cos(theta),s=std::sin(theta);
		double new_app=c*c*app-2*s*c*apq+s*s*aqq;
		double new_aqq=s*s*app+2*s*c*apq+c*c*aqq;
		if(new_app!=app || new_aqq!=aqq) // do rotation
			{
			changed=true;
			timesJ(A,p,q, theta); // A←A*J 
			Jtimes(A,p,q,-theta); // A←JT*A 
			timesJ(V,p,q, theta); // V←V*J
			}
	}
}while(changed);
    //std::cout << "Jacobi while loop done. Making vector with the diagonal (Eigenvalues)\n";
    pp::vector D(n);
    for(int i = 0; i<n;i++){D[i] = A[i][i];}

    return std::make_pair(V,D);
}

}//namespace pp