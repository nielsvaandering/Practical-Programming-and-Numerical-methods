#include"matrix.hpp"
#include"qr.hpp"
#include"fit.hpp"
#include<vector>
#include<functional>
#include<iostream>
#include<cmath>
#include <fstream>

//We wiull use the data from the exercise, and fit it with the lsfit function.
int main(){
    //We have to create a vector with the function we use for the fit, a vector with the measurement times, and a vector with the data
    pp::vector time = {1, 2, 3, 4, 6, 9, 10, 13, 15};
    pp::vector activity = {117, 100, 88, 72, 53, 29.5, 25.2, 15.2, 11.1};
    pp::vector uncertainty = {6, 5, 4, 4, 4, 3, 3, 2, 2};

    //We will fit with an exponential alpha exp[lambda t], so we do the usual way and with the log, so we can rewrite it to ln[alpha] - lambda t
    //We therefore have to take the logarithm of activity, and Delta ln(y) = Delta y / y, so we also have to change the uncertainty
    pp::vector y(activity.size());
    for(int i = 0;i<y.size();i++){y[i] = std::log(activity[i]);}
    pp::vector dy(uncertainty.size());
    for(int i = 0; i< dy.size();i++){dy[i] = uncertainty[i] / activity[i];}

    //Defining a function for the fit
    std::vector<std::function<double(double)>> fs {
	[](double z) { return (1.0 + 0 * z) ;}, //It was complaining about unused variable, so just multiplied it by 0
	[](double z) { return z; },
    };

    //Performing the fit
    pp::vector c = lsfit(fs, time, y, dy);
    
    //Output the function as f(t) = exp(c[0]) exp(c[1] * t)
    std::ofstream outfile("Fit_result.txt");
    outfile << "alpha = " << std::exp(c[0]) << "\n";
    outfile << "lambda = " << -1* c[1] << "\n";
    outfile << "f(x) = alpha * exp(-lambda * x)" ;
    outfile.close();

    //Output of the datapoint for plotting
    std::cout << "#Datapoints\n";
    for(int i=0;i<time.size();i++){
        std::cout << time[i] << " " << activity[i] << " " << uncertainty[i] << "\n";
    }

    std::cout << "\n#Best fit: f(x) = " << std::exp(c[0]) << " * exp(" << c[1] << " * x)\n";
    std::cout << "#The halflife is ln(2) / lamba = " << std::log(2) / (-1* c[1]) << "\n";
    std::cout << "#From google: halflife 224Ra = 3,6316 days, so it is a bit off.\n";



    return 0;
}