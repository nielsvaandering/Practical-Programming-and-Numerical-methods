#pragma once
#include"matrix.hpp"
#include <utility> 

namespace pp {
struct qr{

static std::pair<matrix, matrix> QR_decompose(const matrix& A);

static vector backsubstitution(const matrix& R, const vector& b);

static vector solve(const matrix& A, const vector& b);

static double det(const matrix& A);

static matrix inverse(const matrix& A);

};

} // namespace pp







