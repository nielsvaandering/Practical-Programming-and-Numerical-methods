#pragma once
#include"matrix.hpp"
#include<utility>

namespace pp{
struct EVD{
	static void timesJ(pp::matrix& A, int p, int q, double theta);
	static void Jtimes(pp::matrix& A, int p, int q, double theta);
	static std::pair<pp::matrix, pp::vector> jacobi(matrix A) ;
};
}//pp