#include "hydrogen_SE.hpp"
#include"EVD.hpp"


std::pair<pp::matrix, pp::vector> hydrogen_SE(double r_max, double dr)
{
    //We start by building the Hamiltional matrix H
    int npoints = (int)(r_max/dr)-1;
    pp::vector r(npoints);
    for(int i=0;i<npoints;i++){r[i]=dr*(i+1);}
    pp::matrix H(npoints,npoints);
    for(int i=0;i<npoints-1;i++){
        H[i,i]  =-2*(-0.5/dr/dr);
        H[i,i+1]= 1*(-0.5/dr/dr);
        H[i+1,i]= 1*(-0.5/dr/dr);
}
    H[npoints-1,npoints-1]=-2*(-0.5/dr/dr);
    for(int i=0;i<npoints;i++){H[i,i]+=-1/r[i];}

    //Calling EVD on H to find the eigenvectors (eigenfunctions), and corresponding eigenvalues (energies)
    auto [F,E] = pp::EVD::jacobi(H);

    return std::make_pair(F,E);
}