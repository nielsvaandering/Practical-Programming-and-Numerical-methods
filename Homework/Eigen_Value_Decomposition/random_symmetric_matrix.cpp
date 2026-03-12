#include "random_symmetric_matrix.hpp"
#include"matrix.hpp"
#include<random>


void random_symmetric_matrix(pp::matrix &A)
{
    int n = A.rows();
    unsigned seed = 123; // Choosing a fixed seed for reproducibility
    std::mt19937 generator(seed); // Initialize with the fixed seed
    std::uniform_real_distribution<double> distribution(1.0, 10.0);

    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            double randomNumber = distribution(generator); // Random value between 0 and 100
            A.set(i,j,randomNumber);
            A.set(j,i,randomNumber);

}
}
}
