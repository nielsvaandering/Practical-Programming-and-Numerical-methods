#include"matrix.hpp"
#include"neural_network.hpp"
#include<iostream>
#include<functional>
#include<cmath>

int main(){
    //Part A: Neural network
    std::cout << "Part A: Neural network\n";
    std::function<double(double)> g = [](double x){
        return std::cos(5*x - 1) * std::exp(-x*x);
    };
    pp::vector x, y;
    for(int i = 0; i<20;i++){
        x.push_back(-1 + i * 0.1);
        y.push_back(g(-1 + i * 0.1));
    };
    std::cout << "The datapoints to train the network are from f(x) = cos(5x-1)e^(-x^2). The trainingpoints are the following:\n";
    x.print("x = ");
    y.print("y = ");

    std::function<double(double)> Gaus_wave = [](double x){return x*std::exp(-x*x);};
    std::function<double(double)> Gaus = [](double x){return std::exp(-x*x);};
    std::function<double(double)> RELU = [](double x){
        if(x < 0){return 0.0;};
        return x;};


    pp::nn neural_network(4);//default is cos(5x)e^(-x^2)
    pp::nn neural_network_2(4, Gaus_wave);
    pp::nn neural_network_3(4, Gaus);
    pp::nn neural_network_4(4, RELU);
    std::cout << "\nMinimizing the cost function (training) for the traingsdata with default activation function (cos(5x)exp(-x^2)):\n";
    neural_network.train(x,y);
    std::cout << "\nMinimizing the cost function (training) for the traingsdata with Gaussian wavelet (x*e^(-x^2)):\n";
    neural_network_2.train(x,y);
    std::cout << "\nMinimizing the cost function (training) for the traingsdata with Gaus (e^(-x^2)):\n";
    neural_network_3.train(x,y);
    std::cout << "\nMinimizing the cost function (training) for the traingsdata with RELU (0: x< 0, x: x>0):\n";
    neural_network_4.train(x,y);

    //Testing the Gausian wavelet:
    pp::vector test;
    for(int i = 0; i < x.size();i++){
        test.push_back(neural_network_2.response(x[i]));
    }
    std::cout << "\nSince the Gaussian wavelet has the lowest cost function, I will print the output at the traingspoint, so we can compare with y\n";
    test.print("Gaussian wavelet at the trainingpoints = ");

    std::cout << "\nJust for fun, lets compare some inbetween points for all the different neural network to see how well they perform in between the traingsdata\n";
    std::cout << "Neural network with a wavelet:\n Test for x = 0.15, g(x) = " << g(0.15) << " and neural network says: " << neural_network.response(0.15) << "\n";
    std::cout << "Neural network with a wavelet:\n Test for x = 0.55, g(x) = " << g(0.55) << " and neural network says: " << neural_network.response(0.55) << "\n";
    std::cout << "Neural network with a wavelet:\n Test for x = 0.1, g(x) = " << g(0.1) << " and neural network says: " << neural_network.response(0.1) << "\n";

    std::cout << "\nNeural network with gausian wavelet:\n Test for x = 0.15, g(x) = " << g(0.15) << " and neural network says: " << neural_network_2.response(0.15) << "\n";
    std::cout << "Neural network with gausian wavelet:\n Test for x = 0.55, g(x) = " << g(0.55) << " and neural network says: " << neural_network_2.response(0.55) << "\n";
    std::cout << "Neural network with gaisian wavelet:\n Test for x = -0.45, g(x) = " << g(-0.45) << " and neural network says: " << neural_network_2.response(-0.45) << "\n";
    std::cout << "Neural network with gausian wavelet:\n Test for x = 0.789, g(x) = " << g(0.789) << " and neural network says: " << neural_network_2.response(0.789) << "\n";

    std::cout << "\nNeural network with gaus:\n Test for x = 0.15, g(x) = " << g(0.15) << " and neural network says: " << neural_network_3.response(0.15) << "\n";
    std::cout << "Neural network with gaus:\n Test for x = 0.55, g(x) = " << g(0.55) << " and neural network says: " << neural_network_3.response(0.55) << "\n";
    std::cout << "Neural network with gaus\n Test for x = -0.45, g(x) = " << g(-0.45) << " and neural network says: " << neural_network_3.response(-0.45) << "\n";
    std::cout << "Neural network with gaus\n Test for x = 0.789, g(x) = " << g(0.789) << " and neural network says: " << neural_network_3.response(0.789) << "\n";

    std::cout << "\nNeural network with RELU:\n Test for x = 0.15, g(x) = " << g(0.15) << " and neural network says: " << neural_network_4.response(0.15) << "\n";
    std::cout << "Neural network with RELU:\n Test for x = 0.55, g(x) = " << g(0.55) << " and neural network says: " << neural_network_4.response(0.55) << "\n";
    std::cout << "Neural network with RELU:\n Test for x = -0.45, g(x) = " << g(-0.45) << " and neural network says: " << neural_network_4.response(-0.45) << "\n";
    std::cout << "Neural network with RELU:\n Test for x = 0.789, g(x) = " << g(0.789) << " and neural network says: " << neural_network_4.response(0.789) << "\n";

    //PArt B: since gaussian wavelet is the best, on the test data, I will only do it for that network.
    std::cout << "\n\n#Part B: Derivative, second derivative\n#To see the plot, look at Derivative.svg\n";
    std::cout << "#In the plot, we can see that the first derivative is quite good. The second derivative follows the overall shape, but is not accurate.\n";
    std::cout << "#The data under here is what was used to make the plot. The first column is x, then f'(x) and as last f''(x)\n";
    for(double i = -1;i<=1;i+=0.0625 ){
        std::cout << i << " " << neural_network_2.derivative(i) << " " << neural_network_2.second_derivative(i) << "\n";
    }


    //Part C: Solving ODE with neural network
    /* For now, the ODE solver with a neural network doesn't really work, so i will comment it out and maybe have a look at it later.
    std::cout << "\n\nPart C: solving ODE with neural network.\n";

    //To test if the solution of the AI chatbot works, it wrote its own trial function:
    // Create network with 20 hidden neurons using tanh
    pp::nn network(10, [](double x) { return x*std::exp(-x*x); });

    // Solve: y'' + y = 0 with y(0) = 1, y'(0) = 0 on [0, π]
    auto ODE = [](double y_pp, double y_p, double y, double x) -> double {
        (void) y_p;  // unused
        (void) x;    // unused
        return y_pp + y;
    };

    network.solve_ODE_AI(
        ODE,           // Φ function
        0.0,           // a
        M_PI,          // b
        0.5,           // c (condition point)
        1.0,           // y(c) = 1
        1.0,           // y'(c) = 0
        5.0,           // alpha
        5.0,           // beta
        0.01,         // accuracy for integrator
        0.01,         // eps for integrator
        true           // use Clenshaw-Curtis
    );

    // Evaluate solution
    std::cout << "y(π/2) = " << network.response(M_PI/2) << "\n";
    std::cout << "y'(π/2) = " << network.derivative(M_PI/2) << "\n";
    */



    return 0;
}