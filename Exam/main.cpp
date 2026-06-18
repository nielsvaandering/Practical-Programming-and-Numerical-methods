#include"adaptive3.hpp"
#include<iostream>
#include<functional>
#include<cmath>
#include<limits>
#include<vector>
#include<fstream>

int main(){
    //Part A: Implement an adaptive division-by-three integrator and test it on functions from the homework "recursive adaptive integration"
    //The functions from homework will all integrated over the interval [0,1]. I also keep track over the number of function evaluations
    int eval_sqrtx = 0, eval_over_sqrtx = 0, eval_sqrt1_xx = 0, eval_lnx_sqrtx = 0; 
    std::function<double(double)> sqrt_x = [&eval_sqrtx](double x) {eval_sqrtx++; return std::sqrt(x);}; //  2/3
    std::function<double(double)> over_sqrt_x = [&eval_over_sqrtx](double x) {eval_over_sqrtx++; return 1.0 / std::sqrt(x);};//  2
    std::function<double(double)> sqrt_1_xx = [&eval_sqrt1_xx](double x) {eval_sqrt1_xx++; return std::sqrt( 1 - std::pow(x,2) );};// pi/4
    std::function<double(double)> lnx_sqrtx = [&eval_lnx_sqrtx](double x) {eval_lnx_sqrtx++;return std::log(x) / std::sqrt(x);};//  -4

    auto [int_sqrtx, err_sqrtx] = adaptive3(sqrt_x, 0, 1);
    auto [int_over_sqrtx, err_over_sqrtx] = adaptive3(over_sqrt_x, 0, 1);
    auto [int_sqrt1_xx, err_sqrt1_xx] = adaptive3(sqrt_1_xx, 0, 1);
    auto [int_lnx_sqrtx, err_lnx_sqrtx] = adaptive3(lnx_sqrtx, 0, 1);

    std::cout << "Checking the recursive adaptive integrator with subdevision into 3 subinertvals and the error estimation of the integral on some basic functions from the homework on recursive adaptive integration\n";
    std::cout << "∫_0^1 dx √(x) = 2/3, and the integrators returns: " << int_sqrtx << " with estimated error " << err_sqrtx << ". It used " << eval_sqrtx << " evaluations of the integrand.\n";
    std::cout << "to check accuracy; |result - exact| < acc + |exact| * eps  => " << std::abs(int_sqrtx - 2.0/3.0) << " < " << 0.001 + std::abs(int_sqrtx) * 0.001 << "\n";
    auto[hw_sqrtx, hw_steps_sqrtx, hw_err_sqrtx] = Recursive_open_integrator(sqrt_x, 0, 1);
    std::cout << "The integrator from the Homework did it in " << hw_steps_sqrtx << " evaluations.\n\n";

    std::cout << "∫_0^1 dx 1/√(x) = 2, and the integrators returns: " << int_over_sqrtx << " with estimated error " << err_over_sqrtx << ". It used " << eval_over_sqrtx << " evaluations of the integrand.\n";
    std::cout << "to check accuracy; |result - exact| < acc + |exact| * eps  => " << std::abs(int_over_sqrtx - 2) << " < " << 0.001 + std::abs(int_over_sqrtx) * 0.001 << "\n";
    std::cout << "Note: It evaluates the integrand eventually as infinity, it hits machine precision for the interval width and triggers the max_depth notification.\n";
    auto[hw_over_sqrtx, hw_steps_over_sqrtx, hw_err_over_sqrtx] = Recursive_open_integrator(over_sqrt_x, 0, 1);
    std::cout << "The integrator from the Homework did it in " << hw_steps_over_sqrtx << " evaluations.\n\n";

    std::cout << "∫_0^1 dx √(1-x²) = π/4, and the integrators returns: " << int_sqrt1_xx << " with estimated error " << err_sqrt1_xx << ". It used " << eval_sqrt1_xx << " evaluations of the integrand.\n";
    std::cout << "to check accuracy; |result - exact| < acc + |exact| * eps  => " << std::abs(int_sqrt1_xx - M_PI / 4) << " < " << 0.001 + std::abs(int_sqrt1_xx) * 0.001 << "\n";
    auto[hw_sqrt1_xx, hw_steps_sqrt1_xx, hw_err_sqrt1_xx] = Recursive_open_integrator(sqrt_1_xx, 0, 1);
    std::cout << "The integrator from the Homework did it in  " << hw_steps_sqrt1_xx << " evaluations.\n\n";

    std::cout << "∫_0^1 dx ln(x)/√(x) = -4, and the integrators returns: " << int_lnx_sqrtx << " with estimated error " << err_lnx_sqrtx << ". It used " << eval_lnx_sqrtx << " evaluations of the integrand.\n";
    std::cout << "to check accuracy; |result - exact| < acc + |exact| * eps  => " << std::abs(int_lnx_sqrtx + 4) << " < " << 0.001 + std::abs(int_lnx_sqrtx) * 0.001 << "\n";
    std::cout << "Note: It evaluates the integrand eventually as nan, it hits machine precision for the interval width and triggers the max_depth notification.\n";
    auto[hw_lnx_sqrtx, hw_steps_lnx_sqrtx, hw_err_lnx_sqrtx] = Recursive_open_integrator(lnx_sqrtx, 0, 1);
    std::cout << "The integrator from the Homework did it in " << hw_steps_lnx_sqrtx << " evaluations.\n\n\n";

    std::cout << "COMMENT: In 3 of the 4 cases, the adaptive recursive integrator with 3 sub-intervals uses less function evaluations then the integrator with 2 sub-intervals from the Homework.\n ";
    std::cout << "To compare both of them even more, I asked chatbot for some (finite) integrals to compare them even more. It came up with the following integrals:\n";
    int eval_sinx = 0, eval_expx = 0, eval_gaus = 0, eval_over_1x = 0 , eval_x3 = 0;
    std::function<double(double)> sinx = [&eval_sinx](double x){eval_sinx++; return std::sin(x);};
    std::function<double(double)> expx = [&eval_expx](double x){eval_expx++; return std::exp(x);};
    std::function<double(double)> gaus = [&eval_gaus](double x){eval_gaus++; return std::exp(-x*x);};
    std::function<double(double)> over_1x = [&eval_over_1x](double x){eval_over_1x++; return 1 / (1+x);};
    std::function<double(double)> x3 = [&eval_x3](double x){eval_x3++; return x*x*x;};

    auto test_sinx = adaptive3(sinx, 0, M_PI, 0.001, 0.001, 10); //= 2
    auto test_expx = adaptive3(expx, 0, 1); //=e - 1 = 1.7183
    auto test_gaus = adaptive3(gaus, 0, 1); // approx 0.7468
    auto test_over_1x = adaptive3(over_1x, 0, 1); // approx 0.693
    auto test_x3 = adaptive3(x3, 0, 1, 0.001, 0.001);

    std::cout << "∫_0^π dx sin(x) = 2, and integrator returns " << std::get<0>(test_sinx) << ". It used " << eval_sinx << " evaluations.\n";
    std::cout << "The homework integrator used " << std::get<1>(Recursive_open_integrator(sinx,0,M_PI)) << " evaluations\n\n"; 
    std::cout << "∫_0^1 dx exp(x) = 1.7183, and integrator returns " << std::get<0>(test_expx) << ". It used " << eval_expx << " evaluations.\n";
    std::cout << "The homework integrator used " << std::get<1>(Recursive_open_integrator(expx,0,1)) << " evaluations\n\n"; 
    std::cout << "∫_0^1 dx exp(-x^2) = 0.7468 , and integrator returns " << std::get<0>(test_gaus) << ". It used " << eval_gaus << " evaluations.\n";
    std::cout << "The homework integrator used " << std::get<1>(Recursive_open_integrator(gaus,0,1)) << " evaluations\n\n"; 
    std::cout << "∫_0^1 dx 1 / (1+x) = 0.693, and integrator returns " << std::get<0>(test_over_1x) << ". It used " << eval_over_1x << " evaluations.\n";
    std::cout << "The homework integrator used " << std::get<1>(Recursive_open_integrator(over_1x,0,1)) << " evaluations\n\n"; 
    std::cout << "∫_0^1 dx x^3 = 1/4, and integrator returns " << std::get<0>(test_x3) << ". It used " << eval_x3 << " evaluations.\n";
    std::cout << "The homework integrator used " << std::get<1>(Recursive_open_integrator(x3,0,1)) << " evaluations\n\n\n"; 
    



    //The Clenshaw–Curtis variable transformation
    //first reset the evaluations to the functions to 0
    std::cout << "CLENSHAW-CURTIS TRANSFORMATION:\n";
    eval_sqrtx = 0, eval_over_sqrtx = 0, eval_sqrt1_xx = 0, eval_lnx_sqrtx = 0; 
    auto [CC_sqrtx, err_cc_sqrtx] = Clenshaw_Curtis_integrator(sqrt_x, 0, 1);
    auto [CC_over_sqrtx, err_cc_over_sqrtx] = Clenshaw_Curtis_integrator(over_sqrt_x, 0, 1);
    auto [CC_sqrt1_xx, err_cc_sqrt1_xx] = Clenshaw_Curtis_integrator(sqrt_1_xx, 0, 1);
    auto [CC_lnx_sqrtx, err_cc_lnx_sqrtx] = Clenshaw_Curtis_integrator(lnx_sqrtx, 0, 1);

    std::cout << "With the Clenshaw-Curtis (CC) variable transformation:\n";
    std::cout << "∫_0^1 dx √(x) = 2/3, and the integrators returns: " << CC_sqrtx << ". It used " << eval_sqrtx << " evaluations of the integrand instead of the 15 evaluations without the transformation.\n";
    auto CC1 = CC_homework(sqrt_x, 0, 1);
    std::cout << "The homework integrator with the CC transformation used " << std::get<1>(CC1) << " evaluations.\n\n";

    std::cout << "∫_0^1 dx 1/√(x) = 2, and the integrators returns: " << CC_over_sqrtx << ". It used " << eval_over_sqrtx << " evaluations of the integrand instead of the 5357 evaluations without the transformation.\n";
    auto CC2 = CC_homework(over_sqrt_x, 0,1);
    std::cout << "The homework integrator with the CC transformation used " << std::get<1>(CC2) << " evaluations.\n\n";

    std::cout << "∫_0^1 dx √(1-x²) = π/4, and the integrators returns: " << CC_sqrt1_xx << ". It used " << eval_sqrt1_xx << " evaluations of the integrand instead of the 15 evaluations without the transformation.\n";
    auto CC3 = CC_homework(sqrt_1_xx, 0,1);
    std::cout << "The homework integrator with the CC transformation used " << std::get<1>(CC3) << " evaluations.\n\n";

    std::cout << "∫_0^1 dx ln(x)/√(x) = -4, and the integrators returns: " << CC_lnx_sqrtx << ". It used " << eval_lnx_sqrtx << " evaluations of the integrand instead of the 10705 evaluations without the transformation.\n";
    auto CC4 = CC_homework(lnx_sqrtx, 0,1);
    std::cout << "The homework integrator with the CC transformation used " << std::get<1>(CC4) << " evaluations.\n\n";

    std::cout << "COMMENT: This integrator with 3 sub-intervals outperforms the homework integrator when they both use the Clenshaw-Curtis transformation. \nInteresting to note: for the integrals which used 'few' function evaluations, the number of evaluations increased (a little). The integrals with 'a lot' of evaluations got a significant reduction in function evaluations.\n\n\n";



    //Let the integrator accept infinite limits
    std::cout << "Infinite limits on the integrals:\n";
    //I found it easier to make a new function, Integrate, which accepts all limits, transforms them according to page 12 of the lecture notes, and then calls the integrator.
    //Since the overall performance of the Clenshaw-Curtis transformation is better then the normal integrator, I let it call the Clenshaw-Curtis transformation, which calls the integrator
    //For testing, I asked AI some integrals with +- inf as boundary. It came with the following:
    int eval_1 = 0, eval_2 = 0, eval_3 = 0, eval_4 = 0;
    std::function<double(double)> exp_min_x = [&eval_1](double x){eval_1++; return std::exp(-x);};
    std::function<double(double)> over_xx = [&eval_2](double x){eval_2++; return 1.0 / (x*x);};
    std::function<double(double)> Gaus = [&eval_3](double x){eval_3++; return std::exp(-x*x);};
    std::function<double(double)> over_1_xx = [&eval_4](double x){eval_4++; return 1 / (1 + x*x) ;};

    auto R_exp_minx = Integrate(exp_min_x, 0); // = 1
    auto R_over_xx = Integrate(over_xx, 1); // = 1
    auto R_Gaus = Integrate(Gaus); // = sqrt(pi) = 1.7725
    auto R_over_1_xx = Integrate(over_1_xx); // = pi

    std::cout << "∫_0^inf dx exp(-x) = 1, and the integrator says: " << std::get<0>(R_exp_minx) << " with error " << std::get<1>(R_exp_minx) << ". It used " << eval_1 << " evaluations.\n";
    std::cout << "∫_^inf dx 1 / x^2 = 1, and the integrator says: " << std::get<0>(R_over_xx) << " with error " << std::get<1>(R_over_xx) << ". It used " << eval_2 << " evaluations.\n";
    std::cout << "∫_-inf^inf dx exp(-x^2) = √π = 1.7725, and the integrator says: " << std::get<0>(R_Gaus) << " with error " << std::get<1>(R_Gaus) << ". It used " << eval_3 << " evaluations.\n";
    std::cout << "∫_-inf^inf dx 1 / (1 + x^2) = π, and the integrator says: " << std::get<0>(R_over_1_xx) << " with error " << std::get<1>(R_over_1_xx) << ". It used " << eval_4 << " evaluations.\n";
    std::cout << "\nCOMMENT: To me, it looks like the integrator also handles infinity as a bound really well. The last thing to do is calculate erf(1) with as much precision as possible.\n";
    std::cout << "For the calculation of erf(1), I will make a plot of calculation erf(1) - online value erf(1) as function of acc (eps = 0). This plot can be found at Error_erf(1).svg.\n";

    
    //Calculation of erf(1). according to wolframalpha: erf(1) = 0.8427007929497148693412206350826092592960669979663029084599378978
    std::function<double(double,double)> erf = [&Gaus](double z, double acc){return (2 / std::sqrt(M_PI)) * std::get<0>(Integrate(Gaus, 0, z, acc, 0));};
    //values for acc. 1e-19 was the smallest value my computer could calculate in a reasonable time
    std::vector<double> acc {1, 1e-1, 1e-2, 1e-3, 1e-4, 1e-5, 1e-6, 1e-7, 1e-8, 1e-9, 1e-10, 1e-11, 1e-12, 1e-13, 1e-14, 1e-15, 1e-16, 1e-17, 1e-18, 1e-19};
    std::vector<double> erf1(acc.size());
    for(long unsigned int i = 0; i < acc.size(); i++){erf1[i] = erf(1, acc[i]);}
    std::ofstream outfile("erf1.txt");
        for(long unsigned int i = 0; i < acc.size(); i++){outfile << acc[i] << " " << std::abs(erf1[i] - 0.8427007929497148693412206350826092592960669979663029084599378978) << "\n";}
    outfile.close();

    std::cout << "When looking at  Error_erf1.svg, it looks like half the datapoints are missing. When having a closer look at erf1.txt, the difference between the calculated value of erf(1) and the found value of erf(1) (wolframalpha) goes to 0 (is 0 for acc= 1e-12).\n";
    std::cout << "I will also make a plot of erf(z) for acc = 1e-12 and plot erf(z) from gnuplot on top of it. The plot can be seen at Erf_z.svg";
    std::vector<double> z {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.3, 1.5, 1.8, 2, 2.2, 2.4, 2.5, 2.7, 2.9, 3};
    std::ofstream outfile2("erf_z.txt");
    for(long unsigned int i = 0; i < z.size(); i++){ outfile2 << z[i] << " " << erf(z[i], 1e-13) << "\n";} ; 
    outfile2.close();

    return 0;
}