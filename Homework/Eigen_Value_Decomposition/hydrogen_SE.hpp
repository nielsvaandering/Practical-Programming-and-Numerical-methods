#pragma once
#include"matrix.hpp"
#include"EVD.hpp"

//Input r_max, and delta_r. Output matrix with eigenvectors (the wavefunctions), and vector with eigenvalues (corresponding energies)
std::pair<pp::matrix, pp::vector> hydrogen_SE(double r_max, double dr) ;