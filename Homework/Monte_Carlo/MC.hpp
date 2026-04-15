#pragma once
#include<functional>
#include<tuple>
#include<cmath>
#include<vector>

namespace MC{
struct lcg {
	long seed,a,c,m;
	lcg(long seed, long a = 1664525, long c = 1013904223, long m = 1L<<32)
        : seed(seed), a(a), c(c), m(m) {}

    double next() {
        seed = (a * seed + c) % m;
        return (double)seed/m;
    }

    //returns a random number between x and y
    double uniform(double x, double y){
        return (next() * (y - x)) + x;
    }
};//lcg


std::tuple<double,double> plain_MC(std::function<double(std::vector<double>)> f, std::vector<double> a, std::vector<double> b, int N);

}//namespace MC