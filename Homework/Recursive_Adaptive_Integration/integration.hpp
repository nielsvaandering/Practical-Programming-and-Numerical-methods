#pragma once
#include<functional>
#include<cmath>
#include<utility>
#include<tuple>


//Integrator for Part A:
std::pair<double,int> Recursive_open_integrator(std::function<double(double)> f, double a, double b, double acc = 0.001, double eps = 0.001, int max_iterations = 10000 , int evaluations = 0 ,double f2 = std::nan(""), double f3 = std::nan(""));

//Integrator part B
std::pair<double, int> Clenshaw_Curtis_integrator(std::function<double(double)> f, double a, double b, double acc = 0.001, double eps = 0.001, int max_iterations = 10000);

//Part B for integral to infinity
//Assume that the upper limit is infinity, so integrate from a to infinity
std::pair<double, int> Integral_infinity(std::function<double(double)> f, double a, double acc = 0.001, double eps = 0.001, int max_iterations = 10000);