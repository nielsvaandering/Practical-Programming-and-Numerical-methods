#include "ODE.hpp"
#include"matrix.hpp"
#include<cmath>

std::tuple<pp::vector, pp::vector> rkstep23(std::function<pp::vector(double, pp::vector)> f, double x, pp::vector y, double h, double alpha, double beta)
{
    pp::vector k0 = f(x, y);
    pp::vector k1 = f(x + alpha * h, y + k0 * alpha * h); 
    pp::vector k2 = f(x + beta * h, y + (beta - beta * beta / (2 * alpha)) * k0 * h + beta * beta / (2 * alpha) * k1 * h);
    pp::vector yh = y + (1 - 1 / (2 * alpha) - 1 / (3 * beta * beta) + 1 / (3 * alpha * beta)) * k0 * h + (1 / (2 * alpha) - 1 / (3 * alpha * beta)) * k1 * h + 1 / (3 * beta * beta) * k2 * h;
    pp::vector delta_y = (k2 - k1) * h;           
    return std::make_tuple(yh, delta_y);
}


std::tuple<pp::vector,pp::matrix> driver(std::function<pp::vector(double,pp::vector)> f, double a, double b, pp::vector yinit, double h, double alpha, double beta, double acc, double eps)
{
double x = a; 
pp::vector y(yinit);
pp::vector xlist; xlist.push_back(x);
pp::matrix ylist; ylist.push_back(y);

while(x < b){
	if(x + h > b) h = b - x;  /* last step should end at b */

	auto [yh,delta_y] = rkstep23(f,x,y,h, alpha, beta);
	double tolerance = (acc + eps * yh.norm()) * std::sqrt(h / (b - a));
	double local_error = delta_y.norm();
	if(local_error <= tolerance){
		x += h;
		y = yh;
		xlist.push_back(x);
		ylist.push_back(y);
	}
	h *= std::min(std::pow(tolerance / local_error, 0.25) * 0.95 , 2.0);
}

return std::make_tuple(xlist, ylist);
}