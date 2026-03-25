#include"ODE.hpp"
#include"matrix.hpp"
#include<iostream> 
#include<numbers>

int main(){
    //Lets test some differential equations with my routine

    //u'' = -u
    //We have to rewrite this to u'= v, v'= -u to make it an ODE
    std::function<pp::vector(double, pp::vector)> f = [](double t, pp::vector y){
    (void)t; // using t without using it to prefent that error
    pp::vector components(2); //components: u and v
    components[0] = y[1];     // u' = v
    components[1] = -y[0];    // v' = -u
    return components;
    };
    pp::vector y_initial{1.0, 0.0};

    auto[t,y] = driver(f,0,10,y_initial);

    //For good plotting, I want columns with column 1: time (x-axis), column 2 all the corresponding first solutions, 
    //and in the second column all the solutions for the second thing

    pp::matrix yt = y.transpose();
    pp::matrix results;
    results.push_back(t);
    results.push_back(yt[0]);
    results.push_back(yt[1]);
    //std::cout << "# t   u' = v    v'= -u\n";
    results.print();

    // Solving the  scipy.integrate.odeint manual:
    std::function<pp::vector(double, pp::vector)> g = [](double t, pp::vector y2){
    (void)t; // using t without using it to prefent that error
    double b = 0.25;
    double c = 5.0;
    pp::vector components(2); //components: theta, omega
    components[0] = y2[1];     // theta'(t) = omega(t)
    components[1] = -b * y2[1] - c * std::sin(y2[0]);    // omega'(t) = -b*omega(t) - c*sin(theta(t))
    return components;
    };
    //In the example, they take initial condition:  theta(0) = pi - 0.1, and is initially at rest, so omega(0) = 0. 
    constexpr double PI = std::numbers::pi;
    pp::vector y2_initial{PI - 0.1, 0.0};

    auto[t2, example] = driver(g, 0, 10, y2_initial);
    //making plotting easier:
    pp::matrix example_plotting;
    example_plotting.push_back(t2);
    example_plotting.push_back(example.transpose()[0]);
    example_plotting.push_back(example.transpose()[1]);

    std::cout<< "\n#Datapoints for the example from scipy odeint: oscillator with friction\n#For me, the plots looks very similar\n";
    example_plotting.print();

    return 0;
}