#include"MC.hpp"
#include<tuple>
#include<functional>
#include<iostream>
#include<cmath>
#include<fstream>


int main(){
    //Part A: plain Monte Carlor integration

    //To test the MC integration for the area of the unit circle, we define the unit circle in the rectangle as:
    std::function<double(std::vector<double>)> f = [](std::vector<double> x){
        if ((x[0] * x[0] + x[1] * x[1]) <= 1){
            return 1.0;
        }
        else return 0.0;
    };
    std::vector<double> a_circle{-1.0, -1.0};
    std::vector<double> b_circle{1.0, 1.0};

    std::vector<double> int_circle_list, error_circle_list, actual_error_circle;
    //just copied some of the first decimals of pi
    constexpr double PI = 3.1415926535897932384626433832795028841971693993751058209749445;

    //making the MC integration for the circle for different number of N, so we can see if the error scales as 1 / sqrt(N)
    std::vector<int> N_list{10,100,500,1000,5000,10000,50000,100000};
    for(int i = 0; i < int(N_list.size());i++){
        auto [int_circle, error_circle] = MC::plain_MC(f, a_circle, b_circle,N_list[i]);
        int_circle_list.push_back(int_circle);
        error_circle_list.push_back(error_circle);
        actual_error_circle.push_back(std::abs(int_circle - PI));
    }

    std::ofstream outfile("area_circle.txt");
    outfile << "#Values of the estimated error and actual error of the area of the unit circle as function of N\n";
    for(int n = 0; n < int(N_list.size()); n++){
        outfile << N_list[n] << " " << int_circle_list[n] << " " << error_circle_list[n] << " " << actual_error_circle[n] << "\n";
    }
    outfile.close();

    std::cout << "For error circle as function of N, see Error_area_circle.svg\n";
    std::cout << "For me (at least at the point of writing), the error doesn't look like 1 / sqrt(n) \nin the beginning, but from N~500, it looks like 1 / sqrt(N)\n";

    //Your function in the exercise
    std::function<double(std::vector<double>)> g = [](std::vector<double> x){
        return std::pow(1 - std::cos(x[0]) * std::cos(x[1]) * std::cos(x[2]),-1) / std::pow(PI,3);
    };
    std::vector<double> A_a_exercise{0,0,0};
    std::vector<double> A_b_exercise{PI,PI,PI};

    auto [int_A_exercise, estimated_error_A] = MC::plain_MC(g,A_a_exercise, A_b_exercise, 5000000);
    std::cout << "For yor try calculating this intregral with solution 1.3932039296856768591842462603255, my MC integrator gets: " << int_A_exercise << "\n";


    
    return 0;
}