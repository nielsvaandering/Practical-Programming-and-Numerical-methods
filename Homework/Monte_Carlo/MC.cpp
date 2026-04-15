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



//The code for Quasi-random MC is almost the same as plain MC. Just have to give it the other random number generator, and error estimateion is different
std::tuple<double,double> MC::Quasi_Random_MC(std::function<double(std::vector<double>)> f, std::vector<double> a, std::vector<double> b, int N)
{
    double dim = a.size();
    double V = 1;
    for(int i =0; i < dim; i++){V *= (b[i] - a[i]);};
    double sum = 0.0;
    double sum_for_error = 0.0;

    //Since I need the sequence in each coodinate, I need the dimension sequences.
    //doing it as I did before, giving the next random number to the next dimension messes up the sequences
    //chat gpt came up with this fix (next 3 lines)
    std::vector<QRNG> random;
    random.reserve(dim);
    for (size_t i = 0; i < dim; ++i) random.emplace_back(1 + i, 0.123 * (1 + i));

    std::vector<QRNG> random2;
    random2.reserve(dim);
    for (size_t i = dim; i < 2*dim; ++i) random2.emplace_back(1 + i, 0.347 * (1 + i));

    //summing over N quasi-random samples
    for(int n = 0; n < N; n++){

    //making the random vector x in which we evaluate f(x)
    std::vector<double> x;
    std::vector<double> x_for_error; //for error estimation
    for(int i = 0; i < dim; i++){
        x.push_back(random[i].uniform(a[i], b[i]));
        x_for_error.push_back(random2[i].uniform(a[i], b[i]));

    }

    //evaluating f(x)
    double fx = f(x);
    sum += fx;
    double fx_for_error = f(x_for_error);
    sum_for_error += fx_for_error;
    }

    double mean = sum / N;
    double mean_for_error = sum_for_error / N;
    //Not completely sure how to estimate the uncertainty. I found do |mean - mean_for_error| (conservative),
    //but also that devided by sqrt(2) (assuming independence with same variance). I will (for now) be conservative.
    double sigma = std::abs(mean - mean_for_error);
    return std::make_tuple(mean * V, sigma * V);
}


