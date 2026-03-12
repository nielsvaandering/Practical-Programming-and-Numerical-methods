#include"matrix.hpp"
#include"EVD.hpp"
#include"hydrogen_SE.hpp"
#include<iostream>
#include<string>

//Code for part B: hydrogen SE
int main(int argc, char *argv[]){
    double rmax = 10.0; //default for rmax hydrogen SE
    double dr = 0.1; //Default for dr in hydrogen SE

    for (int i = 0; i < argc; ++i) {
        std::string arg = argv[i];
        if(arg == "-rmax" && (i+1) < argc){
            rmax = std::stod(argv[i+1]);
        }
        else if(arg == "-dr" && (i+1) < argc){
            dr = std::stod(argv[i+1]);
        }
    }

    auto [F,E] = hydrogen_SE(rmax, dr);
    //The lowest energy is the first eiegnvalue, so to make a nice plot I will output rmax  dr  E[0], So I can use them for plotting
    std::cout << rmax << " " << dr << " " << E[0] << "\n";

    //according to the internet, the lowest energy for hydrogen s-wave in Hartree units is -0.5


    return 0;
}