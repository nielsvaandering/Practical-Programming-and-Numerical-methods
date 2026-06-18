#pragma once
#include<functional>
#include<cmath> 
#include<stdexcept>
#include<tuple>
#include<iostream>
#include<limits>

//Adaptive recursive integrator with 3 sub-intervals
std::tuple<double,double> adaptive3(std::function<double(double)> integrand, double a, double b, double acc=1e-3,double eps=1e-3, int max_depth = 1000, double f2 = std::nan(""), int depth = 0);

std::tuple<double, double> Clenshaw_Curtis_integrator(std::function<double(double)> integrand, double a, double b, double acc = 1e-3, double eps=1e-3, int max_depth=1000);

//Integrator which accepts infinity as limits
std::tuple<double, double> Integrate(std::function<double(double)> integrand, double a = -1*std::numeric_limits<double>::infinity(), double b = std::numeric_limits<double>::infinity(), double acc = 1e-3, double eps = 1e-3, int max_depth = 1000);

//Integrators from homework for comparison.
std::tuple<double,int, double> Recursive_open_integrator(std::function<double(double)> f, double a, double b, double acc=1e-3, double eps=1e-3, int max_iterations=10000, int evaluations = 0 ,double f2 = std::nan(""), double f3 = std::nan(""));

std::tuple<double, int, double> CC_homework(std::function<double(double)> f, double a, double b, double acc=1e-3, double eps=1e-3, int max_iterations=10000);