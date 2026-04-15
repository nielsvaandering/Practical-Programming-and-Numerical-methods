#include "MC.hpp"



std::tuple<double,double> MC::plain_MC(std::function<double(std::vector<double>)> f, std::vector<double> a, std::vector<double> b, int N)
{
    lcg random(1);

    double dim = a.size();
    double V = 1;
    for(int i =0; i < dim; i++){V *= (b[i] - a[i]);};
    double sum = 0.0;
    double sum2 = 0.0;

    //summing over N random samples
    for(int n = 0; n < N; n++){

    //making the random vector x in which we evaluate f(x)
    std::vector<double> x;
    for(int i = 0; i < dim; i++){
        x.push_back(random.uniform(a[i], b[i]));
    }


    //evaluating f(x)
    double fx = f(x);
    sum += fx;
    sum2 += fx * fx;
    }

    double mean = sum / N;
    double sigma = std::sqrt(sum2 / N - mean * mean);
    return std::make_tuple(mean * V, sigma * V / std::sqrt(N));
}

