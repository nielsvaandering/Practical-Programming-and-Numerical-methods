#include"matrix.hpp"
#include"minimization.hpp"
#include<iostream>
#include<functional>
#include<fstream>

int main(){

    //Part A
    std::cout <<"Part A: Finding a (local) minimim for the rosenbrock's valley function and the Himmelblau's function\n";
    /* Some trouble shooting
    std::function<double(pp::vector)> test = [](const pp::vector& x){
	    double sum=0;
	    for(int i=0;i<x.size();i++) sum+=x[i]*x[i];
	    return sum;
    };

	pp::vector v {1.0,1.0};
    pp::gradient(test,v).print("test: gradient=");
    pp::Hessian(test,v).print("test: Hessian=");
    

    auto [point, nsteps] = pp::Newton_minimizer(test, pp::vector{2.0, 2.0});
    point.print("test minimum=");
    */

    std::function<double(pp::vector)> Rosenbrock = [](const pp::vector& x){
        if(x.size() != 2){throw std::invalid_argument("Rosenbrock: input vector must have length 2");};
        return std::pow((1 - x[0]),2) + 100 * std::pow(x[1] - std::pow(x[0],2),2);
    };

    std::function<double(pp::vector)> Himmelblau = [](const pp::vector& x){
        if(x.size() != 2){throw std::invalid_argument("Himmelblau: input vector must have length 2");};
        return std::pow(std::pow((x[0]),2) + x[1] - 11, 2) + std::pow(x[0] + std::pow(x[1],2) - 7, 2);
    };

    auto[min_ros, ros_iter] = pp::Newton_minimizer(Rosenbrock, pp::vector{0.0, 0.0});
    //auto[min_him, him_iter] = pp::Newton_minimizer(Himmelblau, pp::vector{-3.8, 4.0});
    auto[min_him, him_iter] = pp::Newton_minimizer(Himmelblau, pp::vector{0.0, 0.0});



    std::cout << "It found the following minimum for Rosenbrock function (which should be (1,1) according to wikipedia) in " << ros_iter << " steps:\n";
    min_ros.print("Local minimum Rosenbrock:");
    std::cout << "\nIt found a local minimum for Himmelblau function in " << him_iter << " steps at:\n";
    min_him.print();
    //std::cout << "H(min_him)="<<Himmelblau(min_him) <<"\n";
   //pp::gradient(Himmelblau,min_him).print("grad H(min_him)=");

    //Part B: Higgs boson
    std::cout << "\nPart B: Higgs bososn\n";
    //Reading in Higgs data
    pp::vector energy, signal, error;
    double x,y,z;
    while (std::cin >> x >> y >> z) {
        energy.push_back(x); signal.push_back(y); error.push_back(z);
    };

    //format for x: m, Gamma, A
    std::function<double(pp::vector)> deviation_higgs = [energy, signal, error](const pp::vector& x){
        double deviation = 0;
        double m = x[0];
        double Gamma = x[1];
        double A = x[2];

        for(int i = 0; i < energy.size();i++){
            double Breit_Wigner = A / ( std::pow(energy[i] - m ,2) + std::pow(Gamma ,2) / 4 );
            deviation += std::pow( (Breit_Wigner - signal[i]) / error[i] , 2);
        };
	    std::cerr<<"higgs: deviation="<<deviation<<"\n";
        return deviation;
    };

    auto[higgs_fit, higgs_iteration] = pp::Newton_minimizer(deviation_higgs, pp::vector{126, 2, 8});
    std::cout << "Fit parameters for Higgs boson: \n";
    std::cout << "m = " << higgs_fit[0] << ",\nGamma = " << higgs_fit[1] << ",\nA = " << higgs_fit[2] << "\n";
    std::cout << "It did the fit in " << higgs_iteration << " iterations\n";
    //pp::gradient(deviation_higgs,higgs_fit).print("grad deviation=");


    std::ofstream outfile("Fit_result.txt");
    outfile << "m = " << higgs_fit[0] <<"\n";
    outfile << "Gamma = " << higgs_fit[1] <<"\n";
    outfile << "A = " << higgs_fit[2] <<"\n";
    outfile << "f(x) = A / ((x - m)**2 + Gamma**2 / 4)\n";
    outfile.close();


    //Part C:
    std::cout << "\n\nPart C: Using central difference instead of forward difference\n";
    std::cout << "I will test this on the same functions as in A and B\n";

    auto[min_ros_central, ros_iter_central] = pp::Newton_min_central(Rosenbrock, pp::vector{0.0, 0.0});
    auto[min_him_central, him_iter_central] = pp::Newton_min_central(Himmelblau, pp::vector{0.0, 0.0});
    auto[higgs_fit_central, higgs_iteration_central] = pp::Newton_min_central(deviation_higgs, pp::vector{126, 2, 8});

    min_ros_central.print("Minimum Ros:");
    std::cout << "Found it in " << ros_iter_central << " Iterations\n";
    min_him_central.print("Minimum Him:");
    std::cout << "Found it in " << him_iter_central << " Iterations\n";    
    higgs_fit_central.print("Higgs fit (m, Gamma, A):");
    std::cout << "Found it in " << higgs_iteration_central << " Iterations\n";
    std::cout << "\nLooking at the result, the minimization of the Rosenbrock function is with less iterations, the Himmelblau function with more iterations, and the higgs fit is equal.\n";
    std::cout << "The advantage of the central difference is that we need less function evaluations for the same result\n";
    std::cout << "Footnote: setting lambda to 0 (so no regularization for the central difference) reduced the number of iterations in Rosenbrock to 3, but had no effect on the others.\n";


    return 0;
}
