#pragma once
#include"matrix.hpp"

namespace pp {

struct QRResult {
    matrix Q;
    matrix R;

    QRResult(int rows, int cols) : Q(rows, cols), R(cols, cols) {}
};

QRResult QR_decompose(const matrix& A);

} // namespace pp







