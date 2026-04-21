#pragma once
#include"matrix.hpp"
#include<functional>
#include"qr.hpp"
#include<cmath>
#include <algorithm> //for std::max
#include<tuple>

namespace pp{

    matrix Jacobian(std::function<vector(vector)> f, vector x, vector dx, vector fx);

    std::tuple<vector, vector> root_finding(std::function<vector(vector)> f,vector x0, vector dx = {std::nan("")}, double acc = 0.01, double alpha_min = 1.0 / 128.0, int max_iterations = 10000);

}//pp

