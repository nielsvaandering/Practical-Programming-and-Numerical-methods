#include "integration.hpp"

std::tuple<double,int, double> Recursive_open_integrator(std::function<double(double)> f, double a, double b, double acc, double eps, int max_iterations, int evaluations ,double f2, double f3)
{
    if(max_iterations <= 0){throw std::runtime_error("Integral not converged within iteration limit!");}
    double h = b - a;
    if(std::isnan(f2) || std::isnan(f3)){ //For first call, we dont have points to reuse
        evaluations += 2;
        f2 = f(a + 2.0 * h / 6.0);
        f3 = f(a + 4.0 * h / 6.0);
    }
    evaluations += 2;
    double f1 = f(a + h / 6.0);
    double f4 = f(a + 5.0 * h / 6.0);

    double Q = (2.0 * f1 + f2 + f3 + 2.0 * f4)* h / 6.0; //higher order rule
    double q = (f1 + f2 + f3 + f4) * h / 4; //lower order rule
    
    double err = std::abs(Q - q);
    double tol = acc + eps * std::abs(Q);

    if(err < tol) return std::make_tuple(Q,evaluations, err);
    //Since we have to include a counter of evaluations, I have to split it up in left and right, instead of the beautifull code it was
    else{
        auto [int_left, eval_left, err_left] = Recursive_open_integrator(f, a, (a + b) / 2, acc/std::sqrt(2), eps, max_iterations-1, evaluations, f1, f2);
        auto [int_right, eval_right, err_right] = Recursive_open_integrator(f, (a + b) / 2, b, acc/std::sqrt(2), eps, max_iterations-1, eval_left, f3, f4);
        return std::make_tuple(int_left + int_right, eval_right, std::sqrt(std::pow(err_left,2) + std::pow(err_right,2)));
    };
}


//For this part, we just have to do the transformation, and then call the integrator from A
std::tuple<double, int, double> Clenshaw_Curtis_integrator(std::function<double(double)> f, double a, double b, double acc, double eps, int max_iterations){
    constexpr double PI = std::numbers::pi;

    std::function<double(double)> g = [f, a, b](double theta){
        return f( (a + b) / 2 + (b - a) / 2 * std::cos(theta)) * std::sin(theta) * (b - a) / 2; 
    };

    return Recursive_open_integrator(g, 0, PI, acc, eps, max_iterations, 0);
}

//The idea is to do a variable transformation (from page 12 in lecture notes), and then give that transformed function to Clenshaw_Curtis_integrator
std::tuple<double, int, double> Integral_infinity(std::function<double(double)> f, double a, double acc, double eps, int max_iterations)
{
    std::function<double(double)> g = [f,a](double t){
        return f(a + (1 - t) / t) / std::pow(t ,2 );
    };
    return Clenshaw_Curtis_integrator(g, 0, 1, acc, eps, max_iterations);
}
