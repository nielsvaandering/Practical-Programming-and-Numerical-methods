#include"spline.hpp"
#include"matrix.hpp" 
#include<cmath>
#include<iostream>
#include<fstream>

int main(){
    //For part A: We test linear spline on {xi=0,0.5,1,…,9; yi=cos(xi)},
    pp::vector x{0, 0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 5.5, 6, 6.5, 7, 7.5, 8, 8.5, 9};
    pp::vector y(x.size());
    for(int i = 0; i<y.size(); i++){
        y[i] = std::cos(x[i]);
    }
    std::cout << "#Datapoint vectors x and y\n";
    for(int i = 0;i<x.size();i++){
        std::cout << x[i] << " " << y[i] << std::endl;
    }
    std::cout << std::endl;

    std::ofstream outfile("linear_interpolation.txt");
    outfile << "\n#Intrapolation points\n";
    //To test the intrapolation, I will do it for 10 points between each point in x
    for(int i = 0; i<x.size() - 1;i++){
        for(int j = 1; j < 10;j++){
            double dx = (x[i+1] - x[i])  / 10.0;
            double z = x[i] + j * dx;
            double intrapolate = pp::linear_spline::linspline(x,y,z);
            double integral = pp::linear_spline::linintegral(x,y,z);
            outfile << z << " " << intrapolate << " " << integral << "\n";
        }
    }
    outfile.close();

    return 0;
}