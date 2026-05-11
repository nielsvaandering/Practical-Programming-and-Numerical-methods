#include "minimization.hpp"

namespace pp{

vector gradient(std::function<double(pp::vector&)> f, pp::vector& x)
{
    int n = x.size();
    double fx = f(x);
    vector grad(n);
    for(int i = 0; i < n; i++){
        double dx = (1 + std::abs(x[i])) * std::pow(2,-26);//-26
        x[i] += dx;
        grad[i] = (f(x) - fx) / dx;
        x[i] -= dx;
    };
    return grad;
}//gradient


matrix Hessian(std::function<double(pp::vector&)> f, pp::vector& x)
{
    int n = x.size();
    matrix H(n,n);
    vector grad = gradient(f, x);
    for(int i = 0; i < n; i++){
        double dx = (1 + std::abs(x[i])) * std::pow(2,-13);//I've also tried 2^-17 (epsilon^1/3), but it didn't seem to make a difference
        x[i] += dx;
        vector dgrad = gradient(f, x) - grad;
        for(int j = 0; j < n; j++){
            H[i,j] = dgrad[j] / dx;
        };
        x[i] -= dx;
    }
    return H;
}// Hessian


std::tuple<pp::vector, int> Newton_minimizer(std::function<double(pp::vector&)> f, vector& x0, double acc, int max_iterations)
{
    int iterations = 0;
    double fx = f(x0);
    double lambda = 1;//For some reason, it converges really bad for lambda < 1. For lambda 0.2 it it okay-ish, for lambda = 0.1, it likes a straight line at 0 through the test points
    for(int i = 0; i < max_iterations; i++){
        iterations += 1;
        vector grad = gradient(f, x0);
        //debugging
        //std::cout << "-------------\n";
        //std:: cout << iterations << ", grad.norm =  "<< grad.norm() << " \n";
        //x0.print("x_0 = ");
        //grad.print("grad = "); 
        if(grad.norm() < acc){return std::make_tuple(x0, iterations);};//found the (local) minimum

        //Local minimum not reached; Work to do
        matrix H = Hessian(f,x0);
	    for(int i=0;i<H.size1();i++)H[i,i]+=lambda; //Possible regularization
        vector dx = qr::solve(H, - grad);
	    if(dx.dot(grad) > 0) dx=-grad; //In case it is ill-defined and it want to make an uphill step
	    //std::cerr<<"dx.dot(grad)="<<dx.dot(grad)<<"\n";
        //for debugging
        //H.print();
        //dx.print("dx = ");

        //backtracking linesearch
        double alpha  = 1;
        int max_depth_linesearch = 10; //Corresponds to alpha >= 2^-9 
        for(int j = 0; j < max_depth_linesearch; j++){
            vector new_x = x0 + alpha * dx;
            double fz = f(new_x); 
            //more debugging
            //std::cout << "fz = " << fz << ", fx = " << fx << "\n";
            if(fz < fx || j == max_depth_linesearch - 1){
                x0 += alpha * dx;
                fx = fz;
                break;
            }
            alpha /= 2;
        };
    }
    return std::make_tuple(vector{std::nan("")}, max_iterations);
}//Newton



} // pp


