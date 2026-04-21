#pragma once
#include<tuple>
#include<vector>
#include<functional>
#include"matrix.hpp"

std::tuple<pp::vector,pp::vector> rkstep23(
	std::function<pp::vector(double, pp::vector)> f, /* the f from dy/dx=f(x,y) */
	double x,                    /* the current value of the variable */
	pp::vector y,                /* the current value y(x) of the sought function */
	double h,                    /* the step to be taken */
    double alpha = 0.5,               /* The step in between. Should be between [0,1]. Take 0.5 for step halfway.*/
    double beta  = 0.5              /* Step in between for the cubic order. Should be between [0,1]*/
	);


std::tuple<pp::vector,pp::matrix> driver(
	std::function<pp::vector(double,pp::vector)> f,/* the f from dy/dx=f(x,y) */
	double a, double b,           /* initial-point,final-point */
	pp::vector yinit,                /* y(initial-point) */
	double h=0.125,              /* initial step-size */
    double alpha = 0.5,           /* The step in between. Should be between [0,1]. Take 0.5 for step halfway.*/
    double beta  = 0.5,             /* Step in between for the cubic order. Should be between [0,1]*/
	double acc=0.01,             /* absolute accuracy goal */
	double eps=0.01              /* relative accuracy goal */
);


