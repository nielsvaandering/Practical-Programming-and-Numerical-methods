#include "minimization.hpp"

namespace pp{
vector gradient(std::function<double(pp::vector)> f, pp::vector& x)
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


matrix Hessian(std::function<double(pp::vector)> f, pp::vector& x)
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


std::tuple<pp::vector, int> Newton_minimizer(std::function<double(pp::vector)> f, vector x0, double acc, int max_iterations)
{
    int iterations = 0;
    double fx = f(x0);
    for(int i = 0; i < max_iterations; i++){
        iterations += 1;
        vector grad = gradient(f, x0);
        //debugging
        //std::cout << "-------------\n";
        //std:: cout << iterations << " "<< grad.norm() << " \n";
        //x0.print();
        //grad.print(); 
        if(grad.norm() < acc){return std::make_tuple(x0, iterations);};//found the (local) minimum

        //Local minimum not reached; Work to do
        matrix H = Hessian(f,x0);
	    //for(int i=0;i<H.size1();i++)H[i,i]+=1e-6; //Possible regularization
        vector dx = qr::solve(H, - grad);
	    if(dx.dot(grad) > 0) dx=-grad; //In case it is ill-defined and it want to make an uphill step
	    //std::cerr<<"dx.dot(grad)="<<dx.dot(grad)<<"\n";
        //for debugging
        //H.print();
        //dx.print();

        //backtracking linesearch
        double alpha  = 1;
        int max_depth_linesearch = 10; //Corresponds to alpha >= 2^-9 
        for(int j = 0; j < max_depth_linesearch; j++){
            double fz = f(x0 + alpha * dx); 
            //more debugging
            //std::cout << fz << " " << fx << "\n";
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



std::tuple<pp::vector, pp::matrix> grad_Hessian(std::function<double(pp::vector)> f, pp::vector& x)
{
    int n = x.size();
    matrix H(n,n);
    vector grad(n);
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
        double dxi = (1 + std::abs(x[i])) * std::pow(2,-17);
        double dxj = (1 + std::abs(x[i])) * std::pow(2,-17);

        x[i] += dxi;
        x[j] += dxj;
        double f_pp = f(x);
        x[j] -= 2*dxj;
        double f_pm = f(x);
        x[i] -= 2*dxi;
        x[j] += 2*dxj;
        double f_mp = f(x);
        x[j] -= 2* dxj;
        double f_mm = f(x);
        x[i] += dxi;
        x[j] += dxj;

        H[i,j] = (f_pp - f_pm - f_mp + f_mm) / ( 4 * dxi * dxj);
        H[j,i] = (f_pp - f_pm - f_mp + f_mm) / ( 4 * dxi * dxj);
        if(i == j){
            grad[i] = (f_pp - f_mm) / (4 * dxi); //According to the formula, / 2dxi, but when i = j, I make steps that are twice as large
        }
        }
    }
    return std::make_tuple(grad, H);
}// Hessian


std::tuple<pp::vector, int> Newton_min_central(std::function<double(pp::vector)> f, vector x, double acc, int max_iterations)
{
    int iterations = 0;
    double fx = f(x);
    double lambda = 0.001; //Levenberg regularization
    double lambda_max = 0.5;
    while(iterations < max_iterations){
        iterations += 1;
        auto[grad, H] = grad_Hessian(f, x);
        if(grad.norm() < acc){return std::make_tuple(x, iterations);};//found the (local) minimum

        //Local minimum not reached; Work to do
	    for(int i=0;i<H.size1();i++) {H[i,i] += lambda;} //regularization
        vector dx = qr::solve(H, - grad);
	    
        //Not sure if next line is necessary, since already using regularization
        if(dx.dot(grad) > 0) dx=-grad; //In case it is ill-defined and it want to make an uphill step
        double fz = f(x + dx);
        if(fz < fx || lambda >= lambda_max){
            //accept step
            fx = fz;
            x += dx;
            lambda /= 2;
        }
        else {
            lambda *= 2;
            iterations -= 1; //Since we dont do the next step, but it will do += 1 on the iterations
        }
    }
    return std::make_tuple(vector{std::nan("")}, max_iterations); //No minimum found within the iteration limit.
}//Newton with central difference


}//pp
