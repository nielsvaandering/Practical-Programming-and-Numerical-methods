#include "integration.hpp"

double Recursive_open_integrator(std::function<double(double)> f, double a, double b, double acc, double eps, int max_depth ,double f2, double f3)
{
    double h = b - a;
    if(std::isnan(f2) || std::isnan(f3)){ //For first call, we dont have points to reuse
        f2 = f(a + 2.0 * h / 6.0);
        f3 = f(a + 4.0 * h / 6.0);
    }
    double f1 = f(a + h / 6.0);
    double f4 = f(a + 5.0 * h / 6.0);

    double Q = (2.0 * f1 + f2 + f3 + 2.0 * f4)* h / 6.0; //higher order rule
    double q = (f1 + f2 + f3 + f4) * h / 4; //lower order rule
    
    double err = std::abs(Q - q);
    double tol = acc + eps * std::abs(Q);

    if(err < tol) return Q;
    else return Recursive_open_integrator(f, a, (a + b) / 2, acc / std::sqrt(2), eps, max_depth - 1, f1, f2) + Recursive_open_integrator(f, (a + b) / 2, b, acc / std::sqrt(2), eps, max_depth - 1, f3, f4);

}