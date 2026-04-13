#include<functional>
#include<cmath>
#include<iostream>
#include<numbers>
#include<vector>
#include<fstream>
#include"integration.hpp"


//implementation on the error function
double my_erf(double z, double acc = 0.001, double eps = 0.001){
    constexpr double PI = std::numbers::pi;
    if(z < 0){return -1 * my_erf(-1 * z);};
    if(z <= 1){
        std::function<double(double)> integrand = [](double x){return std::exp(-1 * std::pow(x,2));};
        double integral = Recursive_open_integrator(integrand, 0, z, acc, eps);
        return (2.0 / std::sqrt(PI)) *  integral;
    };
    if(z > 1){
        std::function<double(double)> integrand = [z](double t){return std::exp(-1 * std::pow( z + (1 - t) / t,2)) / std::pow(t,2) ;};
        double integral = Recursive_open_integrator(integrand, 0, 1, acc, eps);
        return 1 - ((2.0 / std::sqrt(PI)) * integral);
    };
    return 0.0;
}



int main(){
    //Part A: Test the integrator for some integrals
    std::function<double(double)> test1 = [](double x) {return std::sqrt(x);};
    std::function<double(double)> test2 = [](double x) {return 1.0 / std::sqrt(x);};
    std::function<double(double)> test3 = [](double x) {return std::sqrt( 1 - std::pow(x,2) );};
    std::function<double(double)> test4 = [](double x) {return std::log(x) / std::sqrt(x);};

    //We will integrate all 4 testfunction from [0,1], and compare with the "real" result
    //std::cout << "test1\n";
    double result_1 = Recursive_open_integrator(test1, 0, 1);
    //std::cout << "Test2\n";
    double result_2 = Recursive_open_integrator(test2, 0, 1);
    //std::cout << "Test3\n";
    double result_3 = Recursive_open_integrator(test3, 0, 1);
    //std::cout << "Test4\n";
    double result_4 = Recursive_open_integrator(test4, 0, 1);

    std::cout << "int_[0,1] sqrt(x) = 2/3, and the integrator gives: " << result_1 << "\n"; 
    std::cout << "int_[0,1] 1 / sqrt(x) = 2, and the integrator gives: " << result_2 << "\n"; 
    std::cout << "int_[0,1] sqrt(1 - x^2) =  pi / 4 (error in exercise. In the exercise it says pi / 2), and the integrator gives: " << result_3 << "\n";
    std::cout << "int_[0,1] log(x) / sqrt(x) = -4, and the integrator gives: " << result_4 << "\n"; 

    std::cout <<"\nOn the test functions, the integrator is very close and we can get it closer by giving it a lower acc/eps\n";


    //Testing the error function
    //Making a short list with x values
    std::vector<double> x_list;
    for(double x = -2; x<2; x += 0.125){
        x_list.push_back(x);
    }

    std::ofstream outfile("error_function.txt");
    outfile << "#Values for plotting the error function and comparing with std::erf(z)\n";
    for(double z : x_list){
        outfile << z << "  " << my_erf(z, 0.001, 0.001) << "  " << std::erf(z) << "\n";
    }
    outfile.close();

    std::vector<double> acc_list{0.1, 0.01, 0.001, 0.0001, 0.00001};
    std::ofstream outfile2("erf1.txt");
    outfile2 << "#Given acc and error with tabulated value of erf(1)\n";
    for(double acc : acc_list){
        outfile2 << acc << "  " << std::abs(my_erf(1, acc, 0.0) - 0.84270079294971486934) << "\n";
    }
    outfile2.close();



    return 0;
}
