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

//quasi-random number generator I found on wikipedia:
//Take random r_i [0;0.5]. Then let s_i = s_(i-1) + 0.5 + r_i mod 1
struct QRNG{
    long seed;
    double s0;
    long a, c, m;
    lcg random;
    QRNG(long seed, double s0 = 0, long a = 1664525, long c = 1013904223, long m = 1L<<32)
        : seed(seed), s0(s0), a(a), c(c), m(m), random(seed) {}


    double next(){
        s0 = std::fmod((s0 + 0.5 + random.uniform(0.0,0.5)), 1);
        return s0;
    }

    double uniform(double x, double y){
        return (next() * (y - x)) + x;
    }

};//QRNG


std::tuple<double,double> plain_MC(std::function<double(std::vector<double>)> f, std::vector<double> a, std::vector<double> b, int N);

std::tuple<double,double> Quasi_Random_MC(std::function<double(std::vector<double>)> f, std::vector<double> a, std::vector<double> b, int N);

}//namespace MC