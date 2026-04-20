#include"Root_finding.hpp"
#include<iostream>
#include<functional>
#include"matrix.hpp"
#include <stdexcept>
#include"qr.hpp"


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

    auto [Extremum_Him, func_val_Him] = pp::root::root_finding(Himmelblau, pp::vector{0.0, 0.0});
    auto [Extremum_Him2, func_val_Him2] = pp::root::root_finding(Himmelblau, pp::vector{-3.0, 3.0});
    auto [Extremum_Ros, func_val_Ros] = pp::root::root_finding(Rosenbrock, pp::vector{0.0, 0.0});

    std::cout << "For the Rosenbrock function, It found extremum at (x,y) (should be (a,a^2) according to wikipedia, and I used) a = "<< a << " :\n" ;
    Extremum_Ros.print();
    std::cout << "\nFor the Himmelblau function, It found extremum at (x,y): \n";
    Extremum_Him.print(); 
    std::cout << "This is the local maximum according to wikipedia. I will also find 1 of the 3 local minima by using a different starting point (x,y):\n";
    Extremum_Him2.print();


    return 0;
}
