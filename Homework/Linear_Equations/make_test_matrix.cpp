#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include<random>
#include"matrix.hpp"
#include"make_test_matrix.hpp"

// void generate_random_matrix(int n, int m){
void generate_random_matrix(pp::matrix &A){
    int n = A.size1();
    int m = A.size2();
     // Set the seed for the random number generator
    unsigned seed = 123; // Choosing a fixed seed for reproducibility
    std::mt19937 generator(seed); // Initialize with the fixed seed

    // Distribution for generating random doubles between 1.0 and 100.0
    std::uniform_real_distribution<double> distribution(1.0, 100.0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            double randomNumber = distribution(generator); // Random value between 0 and 100
            A.set(i,j,randomNumber);

}
}
}
/*

    // Seed random number generator
    std::srand(static_cast<unsigned>(std::time(0)));

    // Output the dimensions
    std::cout << n << " " << m << std::endl; // Write dimensions to standard output

    // Generate and output the random matrix
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            double random_value = (static_cast<double>(rand()) / RAND_MAX) * 100; // Random value between 0 and 100
            std::cout << random_value << " "; // Write matrix value
        }
        std::cout << std::endl; // New line for the next row
        
    }
    
}

int main(int argc, char* argv[]) {
        // Default dimensions
    int n = 10; // Default number of rows
    int m = 7;  // Default number of columns

    // Process command-line arguments
    for (int i = 0; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-n" && (i + 1) < argc) {
            n = std::stoi(argv[i + 1]); // Convert string to int
        } 
        else if (arg == "-m" && (i + 1) < argc) {
            m = std::stoi(argv[i + 1]); // Convert string to int
        }
    }
    generate_random_matrix(n,m); 
    return 0;
}
    */