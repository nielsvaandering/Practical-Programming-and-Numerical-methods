#include"spline.hpp"
#include"matrix.hpp" 
#include<cmath>
#include<iostream>
#include<fstream>


//Code for part B and C:
//I let y1 be the cosine of exercise A, y2 = const, y3: y[i] = x[i], y4: y[i] = x[i]^2
//For part C: I choose the function 3cos(x) - 2sin(2x) to test my cubic spline 
int main(){
 pp::vector x{0, 0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 5.5, 6, 6.5, 7, 7.5, 8, 8.5, 9};
    pp::vector y1(x.size());
    pp::vector y2(x.size());
    pp::vector y3(x.size());
    pp::vector y4(x.size());
    pp::vector exercise_C(x.size());

    for(int i = 0; i<y1.size(); i++){
        y1[i] = std::cos(x[i]);
        y2[i] = 1;
        y3[i] = x[i];
        y4[i] = x[i] * x[i];
        exercise_C[i] = 3 * std::cos(x[i]) - 2 * std::sin(2*x[i]);
    }

    std::cout << "#Datapoint vectors x and y1, y2, y3, y4, exercise_C\n";
    for(int i = 0;i<x.size();i++){
        std::cout << x[i] << " " << y1[i] << " " << y2[i] << " " << y3[i] << " " << y4[i]  << " " << exercise_C[i] << std::endl;
    }

    std::ofstream outfile("quadratic_interpolation.txt");
    outfile << "\n#Intrapolation points\n";
    //To test the intrapolation, I will do it for 5 points between each point in x

    pp::qspline cosine(x,y1);
    pp::qspline constant(x,y2);
    pp::qspline linear(x,y3);
    pp::qspline quadratic(x,y4);

    outfile << "#Quadratic interpolation. Output: z, y1, int y1, y2, int y2, y3, int y3, y4, int y4\n";
    for(int i = 0; i<x.size() - 1;i++){
        for(int j = 1; j < 5;j++){
            double dx = (x[i+1] - x[i])  / 5.0;
            double z = x[i] + j * dx;
            outfile << z << " " << cosine.eval(z) << " " << cosine.integ(z) << " " << constant.eval(z) << " " << constant.integ(z) << " " << linear.eval(z) << " " << linear.integ(z) << " " << quadratic.eval(z) << " " << quadratic.integ(z) << "\n";
        }
    }
    outfile.close();

    //to test cubic spline::
    pp::cubespline mycubespline(x,exercise_C);
    std::ofstream outfile2("cubic_interpolation.txt");
    for(int i = 0; i<x.size() - 1;i++){
        for(int j = 1; j < 5;j++){
            double dx = (x[i+1] - x[i])  / 5.0;
            double z = x[i] + j * dx;
            outfile2 << z << " " << mycubespline.eval(z) << " " << mycubespline.integ(z) << "\n";
        }
    }
    outfile2.close();
    return 0;
}
