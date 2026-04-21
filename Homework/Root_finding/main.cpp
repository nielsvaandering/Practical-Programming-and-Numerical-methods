#include"Root_finding.hpp"
#include<iostream>
#include<functional>
#include"matrix.hpp"
#include <stdexcept>
#include"qr.hpp"
#include"ODE.hpp"
#include<fstream>


int main(){
    //Part A: testing my root-finding routine on the extremums of the Rosenbrock's valley funcition and finding the minimums of the Himmelblau's function
    std::cout << "Part A:\n";

    //The derivative of the Rosenbrock function
    //In function 1, I have the derivative of the Rosenbrock function with respect to x, and the second one with respect to y
    double a  = 1;
    double b = 100;
    std::function<pp::vector(const pp::vector&)> Rosenbrock = [a, b](const pp::vector& x){
        pp::vector g(2); //Holds the derivatives of the Rosenbrock function
        if(x.size() != 2){throw std::invalid_argument("Rosenbrock: input vector must have length 2");}
        g[0] = -2 * a + 2 * x[0] + b * (-4 * x[1] * x[0] + 4 * std::pow(x[0],3));
        g[1] = b*( 2 * x[1]  - 2 * std::pow(x[0],2));
        return g;
    };

    //Derivatives of Himmelblau function
    std::function<pp::vector(pp::vector)> Himmelblau = [](const pp::vector& x){
        pp::vector g(2); //Holds the derivatives of the Himmelblau function
        if(x.size() != 2){throw std::invalid_argument("Himmelblau: input vector must have length 2");}
        g[0] = 2 * (std::pow(x[0],2) + x[1] - 11) * 2 * x[0] + 2 * (x[0] + std::pow(x[1],2) - 7);
        g[1] = 2 * (std::pow(x[0],2) + x[1] - 11) + 2 * (x[0] + std::pow(x[1],2) - 7) * 2 * x[1];
        return g;
    };

    auto [Extremum_Him, func_val_Him] = pp::root_finding(Himmelblau, pp::vector{0.0, 0.0});
    auto [Extremum_Him2, func_val_Him2] = pp::root_finding(Himmelblau, pp::vector{-3.0, 3.0});
    auto [Extremum_Ros, func_val_Ros] = pp::root_finding(Rosenbrock, pp::vector{0.0, 0.0});

    std::cout << "For the Rosenbrock function, It found extremum at (x,y) (should be (a,a^2) according to wikipedia, and I used) a = "<< a << " :\n" ;
    Extremum_Ros.print();
    std::cout << "\nFor the Himmelblau function, It found extremum at (x,y): \n";
    Extremum_Him.print(); 
    std::cout << "This is the local maximum according to wikipedia. I will also find 1 of the 3 local minima by using a different starting point (x,y):\n";
    Extremum_Him2.print();

    //Part B
    std::cout << "Part B:Bound state of hydrogen atom\n";

    double rmin = std::pow(2,-10);
    double rmax = 10.0;
    double acc_ODE = 0.01;
    double eps_ODE = 0.01;
    //We have to define out function a bit weird. In the function is now the ODE solver from earlier
    std::function<pp::vector(pp::vector)> F_E_rmax = [&rmin, &rmax, &acc_ODE, &eps_ODE](const pp::vector& x){
        //Our function for the ODE solver
        double E = x[0];
        std::function<pp::vector(double,pp::vector)> S_wave_hydrogen = [E, rmin] (double r, const pp::vector& y){
            if (r <= 0.0) r = rmin;
            return pp::vector{y[1],-2 * (E + 1 / r) * y[0]};
        };
        //Do the ODE solver
        auto [r_values, result_ODE] = driver(S_wave_hydrogen, rmin, rmax, pp::vector{0.0, 1.0}, 0.125, 0.5, 0.5, acc_ODE, eps_ODE);
        //std::cout << result_ODE[result_ODE.rows() -1, result_ODE.columns() -1] << "\n";
        pp::vector function_rmax {result_ODE[1, result_ODE.columns() -1]};
        //function_rmax.print();
        //return the function value at rmax, which is the last column of the returned matrix
        return function_rmax; 
    };

    auto [E_hydrogen, func_val_hydrogen] = pp::root_finding(F_E_rmax, pp::vector{-1.0});
    std::cout << "The lowest root for the schoot method for the hydrogen wavefunction is E =";
    E_hydrogen.print();
    std::cout << "For the convergence for different rmin, rmax, acc, eps (in the ODE), see the .svg files\n";
    std::cout << "For some reason I cannot explain, there is a very good conergence for rmax = 5, and for eps = 0.1\n";
    //To get the corresponding wavefunction, we have to solve the ODE again with the correct/found energy
    
    std::cout << "\n\n\n#Values for the s-wave function for hydrogen";
    double E = E_hydrogen[0];
    std::function<pp::vector(double,pp::vector)> S_wave_hydrogen = [E, rmin] (double r, const pp::vector& y){
        if (r <= 0.0) r = rmin;
        return pp::vector{y[1],-2 * (E + 1 / r) * y[0]};
    };
    auto [r_values, result_ODE] = driver(S_wave_hydrogen, rmin, rmax, pp::vector{0.0, 1.0});
    //Since the objects aren't to big, I'm not concerned about optimizing this. I just optimize to make it as easy as possible for myself for plotting
    pp::matrix result;
    result.push_back(r_values);
    result.push_back(result_ODE.transpose()[0]);
    result.push_back(result_ODE.transpose()[1]);
    result.print();
    
    //To investigate the convergence for different rmin, rmax, acc and eps for ODE, I will do 4 loops over some values

    pp::vector rmin_test {std::pow(2,-30), std::pow(2,-20), std::pow(2,-10), std::pow(2,-5), 0.01, 0.1, 1};
    pp::vector rmax_test {1, 2, 5, 8, 10, 15, 20};
    pp::vector acc_test {0.000001, 0.00001, 0.0001, 0.001, 0.01, 0.1, 1};
    pp::vector eps_test {0.000001, 0.00001, 0.0001, 0.001, 0.01, 0.1, 1};
    //I think with this scale, rmin, acc and eps can all go in 1 plot, and rmax will be seperate
    pp::matrix test_results;

    pp::vector conv_rmin;
    for(int i = 0; i < 7; i++){
        rmin = rmin_test[i];
        auto [E_hydrogen_test, func_val_hydrogen_test] = pp::root_finding(F_E_rmax, pp::vector{-1.0});
        conv_rmin.push_back(std::abs(E_hydrogen_test[0] + 0.5));
    }
    rmin = std::pow(2,-10);//set back to good value for the other tests
    test_results.push_back(rmin_test);
    test_results.push_back(conv_rmin);

    pp::vector conv_rmax;
    for(int i = 0; i < 7; i++){
        rmax = rmax_test[i];
        auto [E_hydrogen_test, func_val_hydrogen_test] = pp::root_finding(F_E_rmax, pp::vector{-1.0});
        conv_rmax.push_back(std::abs(E_hydrogen_test[0] + 0.5));
    }
    rmax = 10.0;
    test_results.push_back(rmax_test);
    test_results.push_back(conv_rmax);

    pp::vector conv_acc;
    for(int i = 0; i < 7; i++){
        acc_ODE = acc_test[i];
        auto [E_hydrogen_test, func_val_hydrogen_test] = pp::root_finding(F_E_rmax, pp::vector{-1.0});
        conv_acc.push_back(std::abs(E_hydrogen_test[0] + 0.5));
    }
    acc_ODE = 0.01;
    test_results.push_back(acc_test);
    test_results.push_back(conv_acc);

    pp::vector conv_eps;
    for(int i = 0; i < 7; i++){
        eps_ODE = eps_test[i];
        auto [E_hydrogen_test, func_val_hydrogen_test] = pp::root_finding(F_E_rmax, pp::vector{-1.0});
        conv_eps.push_back(std::abs(E_hydrogen_test[0] + 0.5));
    }
    eps_ODE = 0.01;
    test_results.push_back(eps_test);
    test_results.push_back(conv_eps);

    std::cout << "\n\n\n#Testing convergence: data: rmin, error, rmax, error, acc, error, eps, error\n";
    test_results.print();

    return 0;
}


