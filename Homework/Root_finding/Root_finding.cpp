#include "Root_finding.hpp"

namespace pp{
    //We apprixomate the jacobi matrix by finite distance
    matrix Jacobian(std::function<vector(vector)> f, vector x, vector dx, vector fx)
    {
        int n = x.size();
        matrix J(n, n);

        //Go over all columns
        for(int k = 0; k < n;k++){
            vector xk = x;
            xk[k] += dx[k];
            vector df = f(xk) - fx; 

            //For each columns, go over each row
            for(int i = 0; i < n; i++){
                J[i,k] = df[i] / dx[k];
            };
        };
        return J;
    }//Jacobian

std::tuple<vector, vector> root_finding(std::function<vector(vector)> f, vector x0, vector dx, double acc, double alpha_min, int max_iterations)
{
    vector fx = f(x0);
    if(std::isnan(dx[0])){
        dx[0] = std::max(std::abs(x0[0]), 1.0) * std::pow(2, -26);
        for(int k = 1; k < x0.size();k++){
            dx.push_back(std::max(std::abs(x0[k]), 1.0) * std::pow(2, -26));
        }
    };

    for(int i = 0; i < max_iterations;i++){
        if(fx.norm() < acc){return std::make_tuple(x0, fx);};
        matrix J = Jacobian(f, x0, dx, fx);
        vector Dx = qr::solve(J, -fx);//Newton's step
        double alpha = 1.0;
        while(true){//Linesearch
            vector z = x0 + alpha * Dx;
            vector fz = f(z);
            if(fz.norm() < (1 - alpha / 2) * fx.norm()){x0 = z; fx = fz;break;};
            if(alpha < alpha_min){x0 = z; fx = fz;break;};
            alpha /= 2;
        }
        }
        //If no root found in the number of itegations, I will return NaN
        return std::make_tuple(vector{std::nan("")}, fx);
}
}//pp