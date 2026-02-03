#include<iostream>
#include<cmath>
#include<numbers> 
#include"sfuns.hpp"


int main() {
    // Some basic calculations for the first part
    std::cout << "Part 1: basic calculations\n";
    double sqrt2 = std::sqrt(2.0);
    std::cout << "sqrt(2) = " << sqrt2 << std::endl;

    double two_power_1_5 = std::pow(2.0, 1.0 / 5.0);
    std::cout << "2^(1/5) = " << two_power_1_5 << std::endl;

    constexpr double PI = std::numbers::pi; 
    constexpr double E = std::numbers::e;
    double e_power_pi = std::pow(E, PI);
    double pi_power_e = std::pow(PI, E);
    std::cout << "e^pi = " << e_power_pi << std::endl;
    std::cout << "pi^e = " << pi_power_e << std::endl;
    std::cout << "\n";


    // Calculating first 10 values of fgamma, and compare it with std::tgamma
    std::cout << "2. First 10 values for the Gamma function in the Sterling approximation \n";
    for(double x=1; x<=10;x+=1){ 
        std::cout << "fgamma(" << x << ") = " << sfuns::fgamma(x) << "\t tgamma(" << x << ") = " << std::tgamma(x) << "\n";
    }
    std::cout << "\n";

    // Calculating first 10 values of lngamma, and compare it with std::lgamma
    std::cout << "3. The logarithm of the gamma function \n";
    for(double x=1; x<=10;x+=1){ 
        std::cout << "lngamma(" << x << ") = " << sfuns::lngamma(x) << "\t lgamma(" << x << ") = " << std::lgamma(x) << "\n";
    }
    std::cout << "Comment on the results: The first 2 values are slightly off, since it calculates the logarithm of 1 to be -1.09e-08, instead of 0 \n";
    return 0;
}


