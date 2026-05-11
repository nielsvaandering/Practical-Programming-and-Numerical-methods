#pragma once
#include<cmath>
#include"matrix.hpp"
#include"qr.hpp"
#include<functional>

namespace pp{
    //returns the gradient
    vector gradient(std::function<double(pp::vector&)> f, pp::vector& x);

    //returns the Hessian matrix (second derivatives)
    matrix Hessian(std::function<double(pp::vector&)> f, pp::vector& x);

    //Finds the (local) minimum for a function f using newtons method. Returns the location of the minimum, and the number of iterations it took
    std::tuple<pp::vector, int> Newton_minimizer(std::function<double(pp::vector&)> f, vector& x0, double acc = 0.001, int max_iterations = 10000);
}//pp

