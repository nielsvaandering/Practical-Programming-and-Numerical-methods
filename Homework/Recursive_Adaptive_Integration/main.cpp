#include<functional>
#include<cmath>
#include<iostream>
#include<numbers>
#include<vector>
#include<fstream>
#include<tuple>
#include"integration.hpp"


//implementation on the error function
double my_erf(double z, double acc = 0.001, double eps = 0.001){
    constexpr double PI = std::numbers::pi;
    if(z < 0){return -1 * my_erf(-1 * z);};
    if(z <= 1){
        std::function<double(double)> integrand = [](double x){return std::exp(-1 * std::pow(x,2));};
        auto [integral,evaluations, err] = Recursive_open_integrator(integrand, 0, z, acc, eps);
        return (2.0 / std::sqrt(PI)) *  integral;
    };
    if(z > 1){
        std::function<double(double)> integrand = [z](double t){return std::exp(-1 * std::pow( z + (1 - t) / t,2)) / std::pow(t,2) ;};
        auto [integral,evaluations, err] = Recursive_open_integrator(integrand, 0, 1, acc, eps);
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
    auto [result_1,evaluations1, err1] = Recursive_open_integrator(test1, 0, 1);
    //std::cout << "Test2\n";
    auto [result_2,evaluations2, err2] = Recursive_open_integrator(test2, 0, 1);
    //std::cout << "Test3\n";
    auto [result_3,evaluations3, err3] = Recursive_open_integrator(test3, 0, 1);
    //std::cout << "Test4\n";
    auto [result_4,evaluations4, err4] = Recursive_open_integrator(test4, 0, 1);

    std::cout << "Part A: basic integrator\n";
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




    //Part B
    auto [int_B1, evaluations_B1, err_B1] = Clenshaw_Curtis_integrator(test2, 0, 1);
    auto [int_B2, evaluations_B2, err_B2] = Clenshaw_Curtis_integrator(test4, 0, 1);

    std::cout << "\nPart B: Clenshaw Curtis integrator and integrator to infinity\n";
    std::cout<< "Check Clenshaw curtis integrator:\n";
    std::cout<<"int_[0,1] 1 / sqrt(x) = 2, and integrator says: " << int_B1 << " And got it in " << evaluations1 << " evaluations instead of " << evaluations2 << " from A\n";
    std::cout<<"int_[0,1] log(x) / sqrt(x) = -4, and integrator says: " << int_B2 << " And got it in " << evaluations2 << " evaluations instead of " << evaluations4 << " from A\n";
    std::cout<< "I also run the python-code to get their evaluations (compare_evaluations_integrand.py), but I had to run in elsewhere, since I have no python in this environment. \nIt took 231 and 315 evaluations respectively, so my code outperformed scipy in the first case, but scipy outperformed me by a lot in the second case\n";

    //integrator that accept infinity as upper bound:
    //I asked chatgpt model 5 to come up with some function to test an numerical integrator with upperbound infinity, and these are the first suggestions:
    std::function<double(double)> infinity1 = [](double x) {return std::exp(-1 * x);}; //[0,infty] = 1
    std::function<double(double)> infinity2 = [](double x) {return std::exp(-1* std::pow(x,2));};//[0,infty] = sqrt(pi) / 2
    std::function<double(double)> infinity3 = [](double x) {return 1 / (1 + std::pow(x,2));};//[0,infty] = pi / 2

    auto [int_inf1, eval_inf1, err_inf1] = Integral_infinity(infinity1,0);
    auto [int_inf2, eval_inf2, err_inf2] = Integral_infinity(infinity2,0);
    auto [int_inf3, eval_inf3, err_inf3] = Integral_infinity(infinity3,0);

    std::cout << "\nIntegrator to infinity:\n";
    std::cout <<"int_[0,infty] e^(-x) = 1, and integrator says: " << int_inf1 <<" with " << eval_inf1 << " evaluations. Python did it in 75 evaluations\n";
    std::cout <<"int_[0,infty] e^(-x^2) = sqrt(pi)/2, and integrator says: " << int_inf2 <<" with " << eval_inf2 << " evaluations. Python did it in 75 evaluations\n";
    std::cout <<"int_[0,infty] 1 / (1 + x^2) = pi / 2, and integrator says: " << int_inf3 <<" with " << eval_inf3 << " evaluations. Python did it in 15 evaluations\n";
    std::cout <<"By comparing the number of evaluations with python, my code needed less evaluations for the first 2, but more for the last one. \nIn all 3 cases the number of evaluations was in the same order of magnitude\n";

    //Part C: error estimation investigation
    constexpr double PI = std::numbers::pi;
    std::cout << "\nPart C: Error estimate\n";
    std::cout << "I don't know what you call difficult integrals, but I would count the integrals from part B\n";
    std::cout << "For int_[0,1] 1 / sqrt(x): The estimated error is " << err_B1 << " while the true error is " << std::abs(2 - int_B1) << "\n";
    std::cout << "For int_[0,1] log(x) / sqrt(x): The estimated error is " << err_B2 << " while the true error is " << std::abs(-4 - int_B2) << "\n";
    std::cout << "For int_[0,infty] e^(-x): The estimated error is " << err_inf1 << " while the true error is " << std::abs(1 - int_inf1) << "\n";
    std::cout << "For int_[0,infty] e^(-x^2): The estimated error is " << err_inf2 << " while the true error is " << std::abs(0.5 * std::sqrt(PI) - int_inf2) << "\n";
    std::cout << "For int_[0,infty] 1 / (1 + x^2): The estimated error is " << err_inf3 << " while the true error is " << std::abs(PI / 2 - int_inf3) << "\n";
    std::cout << "We see that (except e^(-x)), the estimated error is much lower then the true error\n";
    

    return 0;
}
