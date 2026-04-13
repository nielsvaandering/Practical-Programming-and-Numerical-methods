#pragma once
#include<functional>
#include<cmath>


//Integrator for Part A:
double Recursive_open_integrator(std::function<double(double)> f, double a, double b, double acc = 0.001, double eps = 0.001, int max_depth = 10000 ,double f2 = std::nan(""), double f3 = std::nan(""));