#include "adaptive3.hpp"

std::tuple<double,double> adaptive3(std::function<double(double)> integrand, double a, double b, double acc, double eps, int max_depth, double f2, int depth){
    //Booleans for error notifications. I use then to only send the notification once per integral. Otherwise the whole screen gets spammed with notifications
    static bool notification = false;
    static bool notification_2 = false;
    static bool notification3 = false;

    //Instead of throwing an error, I will just let it return the found result (the return statement can be found later).
    //if(max_depth == depth){throw std::runtime_error("Integral not converged within depthlimit!");}
    if(max_depth == depth && notification == false){notification = true; std::cerr << "Integral did not converge within the maximum number of steps, so the result may not be accurate\n";}
    
    double h = b - a;
    //If h <= 0, we went under machine precision in the interval, so we might as well return 0 for this interval, since it hs width 0
    if(h <= 0){
        if(notification3 == false){notification3 = true; std::cerr << "Went under machine precision, got b - a = " << h << "\n";}
        return std::make_tuple(0,0);};

    //For first call, we dont have the point we can reuse
    if(std::isnan(f2)){f2 = integrand(a + h / 2.0);}

    //Evaluate the function at the missing points; {1/6, 5/6}
    double f1 = integrand(a + h / 6.0);
    double f3 = integrand(a + 5.0 * h / 6.0);

    //Instead of throwing an error when the evaluation of the function is inf or nan, I will set that part of the integral to 0 and display a message
    //When experimenting with integrals, it looked like it only throws this message/error when it dives really deep and is within (a few) machine epsilon of the singulatiry of the function.
    //I think it is therefore relative save to set it to 0, since it has very limited width.
    //if(std::isinf(f1) || std::isinf(f3) || std::isnan(f1) || std::isnan(f3)){throw std::runtime_error("Integrand evaluated as infinity!");}
    if(std::isinf(f1) || std::isinf(f3) || std::isnan(f1) || std::isnan(f3)){
        if(notification_2 == false){notification_2 = true; std::cerr << "Integrand evaluated as +-infinity or +-nan. This was neglected and the result might therefore not be correct.\n";};
        return std::make_tuple(0,0);}

    
    //Estimate of the integral according to the higher and lower order rule as described in README
    double Q = (3 * f1 + 2 * f2 + 3 * f3)* h / 8.0; //higher order rule
    double q = (f1 + f2 + f3) * h / 3.0; //lower order rule

    //error estimate
    double err = std::abs(Q - q);
    double tol = acc + eps * std::abs(Q);

    //If error low enough (or if we reached max_depth), we can return the integral
    if(err < tol || max_depth == depth){return std::make_tuple(Q, err);}
    
    //Otherwise, we have to subdevide our intervalt
    else{
        //Reason for acc -> acc / sqrt(3); for the 2 intervals, we did acc / sqrt(2). We assume the errors to be independent, so
        // total error = sqrt( acc_1/sqrt(3))^2 + acc_2/sqrt(3))^2 + acc_3/sqrt(3)^2 ) = sqrt( 3 * acc^2 / 3) = acc
        auto [left_interval, err_left] = adaptive3(integrand, a, a + ((b - a) / 3.0), acc / std::sqrt(3), eps, max_depth, f1, depth +1);
        auto [middle_interval, err_middle] = adaptive3(integrand, a + ((b - a) / 3.0),  a + 2 * ((b - a) / 3.0), acc / std::sqrt(3), eps, max_depth, f2, depth +1);
        auto [right_interval, err_right] = adaptive3(integrand, a + 2 * ((b - a) / 3.0), b, acc / std::sqrt(3), eps, max_depth, f3, depth+1);
        
        //Reset the possibility to send error notifications
        if(depth == 0){notification = false; notification_2 = false; notification3 = false;};
        return std::make_tuple(left_interval + middle_interval + right_interval, std::sqrt(err_left*err_left + err_middle*err_middle + err_right*err_right));
    }
}

//Do the Clenshaw-Curtis transformation as described on page 11 of the corresponding lecture notes, and call the integrator
std::tuple<double, double> Clenshaw_Curtis_integrator(std::function<double(double)> integrand, double a, double b, double acc, double eps, int max_depth){
    std::function<double(double)> g = [integrand, a, b](double theta){
        return integrand( (a + b) / 2 + (b - a) / 2 * std::cos(theta)) * std::sin(theta) * (b - a) / 2; 
    };
    return adaptive3(g, 0, M_PI, acc, eps, max_depth);
}

//Integrator which accepts all bounds on the integral, also infinity. When the bound is infinity, I use the transformations on page 12 on the lecture notes
//and then call the Clenshaw-Curtis transformation (since outperforms the normal integrator in general)
std::tuple<double, double> Integrate(std::function<double(double)> integrand, double a, double b, double acc, double eps, int max_depth){
    if(std::isinf(a)){
        //∫_-inf^inf
        if(std::isinf(b)){
            std::function<double(double)> transform = [&integrand](double x){return integrand(x / (1 - x*x)) * ((1 + x*x) / std::pow(1 - x*x,2));};
            return Clenshaw_Curtis_integrator(transform, -1, 1, acc, eps, max_depth);
        }
        //∫_-inf^b
        else{
            std::function<double(double)> transform = [&integrand, &b](double x){return integrand(b - (1 - x) / (x*x)) / (x*x) ;};
            return Clenshaw_Curtis_integrator(transform, 0, 1, acc, eps, max_depth);
        }
    }
    //∫_a^inf
    if(std::isinf(b)){
        std::function<double(double)> transform = [&integrand, &a](double x){return integrand(a + (1 - x) / x) / (x*x) ;};
        return Clenshaw_Curtis_integrator(transform, 0, 1, acc, eps, max_depth);
    }
    //∫_a^b
    else{return Clenshaw_Curtis_integrator(integrand, a, b, acc, eps, max_depth);};
}






//The integrator from Homework where we split interval in 2
std::tuple<double,int, double> Recursive_open_integrator(std::function<double(double)> f, double a, double b, double acc, double eps, int max_iterations, int evaluations ,double f2, double f3){
    if(max_iterations <= 0){std::runtime_error("Integral not converged within iteration limit!");}
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

//Clenshaw-Curtis transformation for the homework integrator
std::tuple<double, int, double> CC_homework(std::function<double(double)> f, double a, double b, double acc, double eps, int max_iterations){
    std::function<double(double)> g = [f, a, b](double theta){
        return f( (a + b) / 2 + (b - a) / 2 * std::cos(theta)) * std::sin(theta) * (b - a) / 2; 
    };

    return Recursive_open_integrator(g, 0, M_PI, acc, eps, max_iterations);
}