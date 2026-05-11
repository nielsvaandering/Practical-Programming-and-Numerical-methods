#pragma once
#include<functional> 
#include<random>
#include<cmath>
#include<chrono>
#include<complex>
#include"matrix.hpp"
#include"minimization.hpp"
#include"integration.hpp"

//Nueral network with 1 input neuron, which is the idendity, 1 hidden layer with n neurons, and and output layer with 1 neuton, which sums op all inputs with the corresponding weights
namespace pp{
struct nn{
    int n; /* number of hidden neurons */
    std::function<double(double)> f; /* activation function */
    vector p; /* network parameters, {w_0,...,w_n-1, a_0,...,a_n-1, b_0,...,b_n-1} */
    //The idea do include the function this way is from chatbot
    nn(int n, std::function<double(double)> activation = [](double x){ return std::cos(5*x) * std::exp(- x * x) ; }) : n(n), f(std::move(activation)), p(3*n){} // constructor

    void set_a(int i,double z) { p[n+i]=z; }
    void set_b(int i,double z) { p[2*n+i]=z; }
    void set_w(int i,double z) { p[i]=z; }
    double get_a(int i) { return p[n+i]; }
    double get_b(int i) { return p[2*n+i]; }
    double get_w(int i) {return p[i]; }


    double response(double x){
        //the network response is: Fp(x) = ∑i f((x-ai)/bi)*wi, or Fp(x) = ∑i f((x-ai)*bi)*wi, so we dont have a problem when bi is small
        double sum = 0;
        for(int i = 0; i < n; i++){
            sum += f((x - get_a(i)) * get_b(i) ) * get_w(i);
        };
        return sum;
    }//response

    double derivative(double x){
        //I'm using the central difference.
        //I thought I had a mistake which I couldn't find (which turned out was not a mistake), so I asked Ai for help. It couldn't ind it (since there was no mistake), but it recommended using std::ldexp(1.0, -26) instead of std::exp(2,-26).
        double dx = (1 + std::abs(x)) * std::ldexp(1.0, -26);
        double sum  = 0.0;
        for(int i = 0; i<n;i++){
            double a = get_a(i), b = get_b(i), w = get_w(i);
            double fi_prime = (f((x + dx - a)*b)  - f((x - dx -  a)*b)) * w;
            sum += fi_prime;
        }
        return sum / (2*dx);
    }

    double second_derivative(double x){
        //I'm using the central difference, since I think that is easier for the second derivative
        double dx = (1 + std::abs(x)) * std::ldexp(1.0, -26);
        double sum  = 0.0;
        for(int i = 0;i<n;i++){
            double a = get_a(i), b = get_b(i), w = get_w(i);
            sum += ( f((x + dx - a)*b)  - 2*f((x - a)*b) + f((x - dx - a)*b) )*w;
        }
        return sum / (dx*dx);
    }

    //Expect the analytical anti-derivative of the activation function
    double anti_derivative(double x, std::function<double(double)> F){
        double sum = 0.0;
        for(int i = 0;i<n;i++){
            double a = get_a(i), b = get_b(i), w = get_w(i);
            if(b == 0){continue;};
            sum += F((x -a)*b) * w /b;
        }
        return sum;
    }

    void train(vector &x,vector &y){
      /* train the network to interpolate the given table {x,y} */
      //Training is done by minimizing the cost function
      //To include "this" in the capture to use response was asked to AI
      //Got those initial values from your example
    for(int i=0;i<n;i++){
		set_w(i,1);
		set_b(i,1);
		set_a(i,x[0]+(x[x.size()-1]-x[0])*(i+0.5)/n);
	}

      std::function<double(pp::vector&)> cost = [this, &x, &y](pp::vector& p){
        (void) p;
        int N = x.size();
        if(y.size() != N){throw std::invalid_argument("Training: traningsdata must have the same length");};

        double difference = 0;
        for(int i = 0; i < N; i++){
            difference += std::pow( this-> response(x[i]) - y[i] , 2);
        }
        return difference / x.size();};
        
        //Now let the minimizer minimize the cost function.
        //Since we pass p as a reference, we should be fine, and best_p is equal to p at that moment.
        auto[best_p, iterations] = pp::Newton_minimizer(cost, p);
        std::cout << "Minimization in "<< iterations << " iterations\n";
        std::cout << "Cost function after minimization is: " << cost(p) << "\n"; 
   }


   //To be honest, I was a bit lost how to let a neural network solve an ODE, so I carefully discussed it with Claude Haiku 4.5, and it came up with this
  /* The ODE solver with a neural network didn't really work, so I will comment it out. Maybe I will have a look at it later to try to fix it
   void solve_ODE_AI(
    std::function<double(double, double, double, double)> Phi,  // Φ(y'', y', y, x)
    double a, double b,           // domain [a, b]
    double c,                      // condition point
    double y_c, double y_prime_c,  // y(c) = y_c, y'(c) = y'_c
    double alpha = 1.0,            // weight for y condition
    double beta = 1.0,             // weight for y' condition  
    double acc = 0.001,            // accuracy for integrator
    double eps = 0.001,            // tolerance for integrator
    bool use_clenshaw = true       // use Clenshaw-Curtis (vs Recursive Open)
) {
    // Initialize network parameters spread over domain
    for(int i = 0; i < n; i++) {
        set_w(i, 1.0);
        set_b(i, 1.0);
        set_a(i, a + (b - a) * (i + 0.5) / n);
    }
    
    // Define the cost function
    std::function<double(pp::vector&)> cost = 
        [this, &Phi, a, b, c, y_c, y_prime_c, alpha, beta, acc, eps, use_clenshaw]
        (pp::vector& p_unused) -> double {
        
        (void) p_unused;  // Cost uses this->p directly
         static int call_count = 0;
        static auto start_time = std::chrono::high_resolution_clock::now();
        call_count++;
        
        // Define the integrand: Φ[F_p(x)]²
        // This captures 'this' so it uses current network parameters
        std::function<double(double)> integrand = [this, &Phi](double x) -> double {
            double y = this->response(x);
            double y_prime = this->derivative(x);
            double y_double_prime = this->second_derivative(x);
            
            double phi_val = Phi(y_double_prime, y_prime, y, x);
            return phi_val * phi_val;
        };
        
        // Compute physics loss using integrator
        double physics_loss;
        int num_evals;
        double error_est;
        
        if(use_clenshaw) {
            std::tie(physics_loss, num_evals, error_est) = 
                Clenshaw_Curtis_integrator(integrand, a, b, acc, eps);
        } else {
            std::tie(physics_loss, num_evals, error_est) = 
                Recursive_open_integrator(integrand, a, b, acc, eps);
        }
        
        // Boundary condition losses
        double y_at_c = this->response(c);
        double y_prime_at_c = this->derivative(c);
        
        double bc_loss = alpha * std::pow(y_at_c - y_c, 2)
                       + beta * std::pow(y_prime_at_c - y_prime_c, 2);
        
        if(call_count % 10 == 0) {  // Print every 10 calls
        auto elapsed = std::chrono::high_resolution_clock::now() - start_time;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        std::cout << "Call " << call_count << " | BC_Cost: " << bc_loss << " | physics_cost: " << physics_loss 
                  << " | Time: " << ms << "ms\n";
    }

        return physics_loss + bc_loss;
    };
    
    // Minimize cost function
    auto[best_p, iterations] = pp::Newton_minimizer(cost, p);
    
    std::cout << "ODE solver converged in " << iterations << " iterations\n";
    std::cout << "Final cost: " << cost(p) << "\n";
};//Train_ODE
*/


};//ann
}