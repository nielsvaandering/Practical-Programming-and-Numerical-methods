#include"matrix.hpp"
#include"minimization.hpp"
#include<iostream>
#include<functional>

int main(){
    //Part A
    std::cout <<"Part A: Finding a (local) minimim for the rosenbrock's valley function and the Himmelblau's function\n";

    std::function<double(pp::vector)> Rosenbrock = [](const pp::vector& x){
        if(x.size() != 2){throw std::invalid_argument("Rosenbrock: input vector must have length 2");};
        return std::pow((1 - x[0]),2) + 100 * std::pow(x[1] - std::pow(x[0],2),2);
    };

    std::function<double(pp::vector)> Himmelblau = [](const pp::vector& x){
        if(x.size() != 2){throw std::invalid_argument("Himmelblau: input vector must have length 2");};
        return std::pow(std::pow((x[0]),2) + x[1] - 11, 2) + std::pow(x[0] + std::pow(x[1],2) - 7, 2);
    };

    auto[min_ros, ros_iter] = pp::Newton_minimizer(Rosenbrock, pp::vector{0.0, 0.0});
    auto[min_him, him_iter] = pp::Newton_minimizer(Himmelblau, pp::vector{-4.0, 6.0});


    std::cout << "It found the following minimum for Rosenbrock function (which should be (1,1) according to wikipedia) in " << ros_iter << " steps:\n";
    min_ros.print();
    std::cout << "\nIt found a local minimum for Himmelblau function in " << him_iter << " steps at:\n";
    min_him.print();


    return 0;
}