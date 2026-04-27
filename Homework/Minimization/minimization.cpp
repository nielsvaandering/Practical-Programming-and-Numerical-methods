#include "minimization.hpp"

namespace pp{
vector gradient(std::function<double(pp::vector)> f, pp::vector& x, double fx)
{
    int n = x.size();
    vector grad(n);
    for(int i = 0; i < n; i++){
        double dx = (1 + std::abs(x[i])) * std::pow(2,-26);
        x[i] += dx;
        grad[i] = (f(x) - fx) / dx;
        x[i] -= dx;
    };
    return grad;
}//gradient


matrix Hessian(std::function<double(pp::vector)> f, pp::vector& x, double fx)
{
    int n = x.size();
    matrix H;
    vector grad = gradient(f, x, fx);
    for(int i = 0; i < n; i++){
        double dx = (1 + std::abs(x[i])) * std::pow(2,-13);
        x[i] += dx;
        fx = f(x);
        vector dgrad = gradient(f, x, fx) - grad;
        H.push_back(dgrad / dx);
        x[i] -= dx;
    }
    return H;
}// Hessian


std::tuple<pp::vector, int> Newton_minimizer(std::function<double(pp::vector)> f, vector x0, double acc, int max_iterations)
{
    int iterations = 0;
    double fx = f(x0);
    for(int i = 0; i < max_iterations; i++){
        iterations += 1;
        vector grad = gradient(f, x0, fx);
        //debugging
        //std::cout << "-------------\n";
        //std:: cout << iterations << " "<< grad.norm() << " \n";
        //x0.print();
        //grad.print(); 
        if(grad.norm() < acc){return std::make_tuple(x0, iterations);};//found the (local) minimum

        //Local minimum not reached; Work to do
        matrix H = Hessian(f,x0, fx);
        vector dx = qr::solve(H, grad);
        //for debugging
        //H.print();
        //dx.print();

        //backtracking linesearch
        double alpha  = 1;
        int max_depth_linesearch = 10; //Corresponds to alpha >= 2^-9 
        for(int j = 0; j < max_depth_linesearch; j++){
            double fz = f(x0 - alpha * dx); 
            //more debugging
            //std::cout << fz << " " << fx << "\n";
            if(fz < fx || j == max_depth_linesearch - 1){
                x0 -= alpha * dx;
                fx = fz;
                break;
            }
            alpha /= 2;
        };
    }
    return std::make_tuple(vector{std::nan("")}, max_iterations);
}//Newton


}//pp