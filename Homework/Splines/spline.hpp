#pragma once
#include"matrix.hpp"

namespace pp{
    int binsearch(vector x,double z){
        int lower = 0;
        int upper = x.size() - 1;
        assert(x[lower] < z && x[upper] > z);

        while((upper - lower) > 1){
            int middle = (lower + upper) / 2;
            if(x[middle] <= z){lower = middle;}
            else{upper = middle;}
        }
        return lower;
    };

    struct linear_spline{
    static double linspline(vector x, vector y, double z){
	int i = binsearch(x,z);
  	double dx=x[i+1]-x[i];
  	assert(dx>0);
  	double dy=y[i+1]-y[i];
  	return y[i]+dy/dx*(z-x[i]);
  	}

    //Calculates the integral from x[0] to z
    static double linintegral(vector &x, vector& y, double z){
        int index_z = binsearch(x,z);
        double integral = 0.0;

        //integral from point in x before z to z
        double dy = y[index_z + 1] - y[index_z];
        double dx = x[index_z + 1] - x[index_z];
        integral += y[index_z] * (z - x[index_z]) + 0.5* (dy / dx) * (z - x[index_z]) * (z - x[index_z]) ;
        //ingeral over the rest of the intervals in vector x
        for(int i = 0; i< index_z;i++){
            dx = x[i+1] - x[i];
            dy = y[i+1] - y[i];
            integral += y[i] * (x[i+1] - x[i]) + 0.5 * (dy / dx) * (x[i+1] - x[i]) * (x[i+1] - x[i]);
        }

        return integral;
    }

    };//linear_spline
    
    struct qspline{
	const int n;
	vector x,y,b,c;
	qspline(const vector& x, const vector& y)
		: n(x.size()), x(x), y(y), b(n-1), c(n-1)
	{// ctor
    // calculate b and c according to the lecture notes
        vector p(n-1);
        vector h(n-1);
        for(int i = 0; i < n-1;i++){
            p[i] = (y[i+1] - y[i]) / (x[i+1] - x[i]);
            h[i] = x[i + 1] - x[i];
        }
        //start with forward substitution with c_1 = 0
        c[0] = 0;
        for(int i = 1; i< n-1;i++){
            c[i] = (1 / h[i]) * (p[i] - p[i-1] - c[i-1] * h[i-1]);
        }
        //Now the backward substitution from 0.5* c_{n-1}
        c[n-2] /= 2;
        for(int i = n-3; i>=0;i--){
            c[i] = (1 / h[i]) * (p[i+1] - p[i] - c[i+1] * h[i+1]);
        }
        //calculation of b[i]
        for(int i = 0; i < n-1;i++){
            b[i] = p[i] - c[i] * h[i];
        }

	}

	int binsearch(double z){
        int lower = 0;
        int upper = x.size() - 1;
        assert(x[lower] < z && x[upper] > z);

        while((upper - lower) > 1){
            int middle = (lower + upper) / 2;
            if(x[middle] <= z){lower = middle;}
            else{upper = middle;}
        }
        return lower;
    };
    
	double eval(double z){
        int index_z = binsearch(z);
        //Evaluate the interpolation polynomial
        return y[index_z] +  b[index_z] * (z - x[index_z]) + c[index_z] * (z - x[index_z]) * (z-x[index_z]);
    }
	double deriv(double z){
        int index_z = binsearch(z);
        return b[index_z] + 2 * c[index_z] * (z - x[index_z]);
    }

	double integ(double z){
        int index_z = binsearch(z);
        double integral = 0;
        for(int i = 0; i < index_z;i++){
            double dx = x[i+1] - x[i];
            integral += y[i] * dx + b[i] * dx*dx / 2 + c[i] * dx*dx*dx /3;
        }
        //Also add the last interval
        double dx = z - x[index_z];
        integral += y[index_z] * dx + b[index_z] * dx*dx / 2 + c[index_z] * dx*dx*dx / 3;
        return integral;
    }
};

struct cubespline{
	const int n;
	vector x,y,b,c,d;
	cubespline(const vector& x, const vector& y)
		: n(x.size()), x(x), y(y), b(n), c(n-1), d(n-1)
	{// ctor
    // calculate b, c and d according to the lecture notes
        vector p(n-1);
        vector h(n-1);
        for(int i = 0; i < n-1;i++){
            p[i] = (y[i+1] - y[i]) / (x[i+1] - x[i]);
            h[i] = x[i + 1] - x[i];
        }

        //following the lecture notes, with D the diagonal, Q the above diagonal
        pp::vector D(n);
        pp::vector Q(n-1);
        pp::vector B(n);

        D[0] = 2;
        Q[0] = 1;
        B[0] = 3*p[0];
        for(int i = 1; i < n-1;i++){
            D[i] = 2* (h[i-1] / h[i]) + 2;
            Q[i] = h[i-1] / h[i];
            B[i] = 3 * (p[i-1] + p[i] * h[i-1] / h[i]);
        }
        D[n-1] = 2;
        B[n-1] = 3*p[n-2];

        //One run of Gauss elimination
        for(int i = 1; i < n;i++){
            D[i] -= Q[i-1] / D[i-1];
            B[i] -= B[i - 1] / D[i-1];
        } 

        //One run of backsubstitution
        b[n-1] = B[n-1] / D[n-1];
        for(int i = n-2; i>=0;i--){
            b[i] = (B[i] - Q[i]*b[i+1]) / D[i];
        }

        //Solving the c_i and d_i coefficients
        for(int i = 0; i < n-1;i++){
            c[i] = (-2*b[i] - b[i+1] + 3*p[i]) / h[i];
            d[i] = (b[i] + b[i+1] - 2*p[i]) / (h[i]*h[i]);
        }
	}//ctor

	int binsearch(double z){
        int lower = 0;
        int upper = x.size() - 1;
        assert(x[lower] < z && x[upper] > z);

        while((upper - lower) > 1){
            int middle = (lower + upper) / 2;
            if(x[middle] <= z){lower = middle;}
            else{upper = middle;}
        }
        return lower;
    };
    
	double eval(double z){
        int index_z = binsearch(z);
        //Evaluate the interpolation polynomial
        double z_min_x = z - x[index_z];
        return y[index_z] +  b[index_z] * z_min_x + c[index_z] * z_min_x*z_min_x + d[index_z] * z_min_x*z_min_x*z_min_x;
    }

    double deriv(double z){
        int index_z = binsearch(z);
        return b[index_z] + 2 * c[index_z] * (z - x[index_z]) + 3* d[index_z]*(z - x[index_z]) * (z - x[index_z]);
    }

	double integ(double z){
        int index_z = binsearch(z);
        double integral = 0;
        for(int i = 0; i < index_z;i++){
            double dx = x[i+1] - x[i];
            integral += y[i] * dx + b[i] * dx*dx / 2 + c[i] * dx*dx*dx /3 + d[i] * dx*dx*dx*dx / 4;
        }
        //Also add the last interval
        double dx = z - x[index_z];
        integral += y[index_z] * dx + b[index_z] * dx*dx / 2 + c[index_z] * dx*dx*dx / 3 + d[index_z]*dx*dx*dx*dx / 4;
        return integral;
    }
};

}//namespace pp