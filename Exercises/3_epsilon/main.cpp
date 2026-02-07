#include<iostream>
#include<limits>
#include<cmath>
#include<iomanip>

// for part 3
bool approx(double a, double b, double acc = 1e-9, double eps = 1e-9) {
    double diff = std::abs(a - b);
    if (diff <= acc) return true;  // absolute tolerance
    double max_ab = std::max(std::abs(a), std::abs(b));
    return diff <= eps * max_ab;   // relative tolerance
}

int main(){
    // 1. Machine precision
float       f=1.0f; while((float)      (1.0f+f) != 1.0f){f/=2.0f;} f*=2.0f;
double      d=1.0d; while((double)     (1.0d+d) != 1.0d){d/=2.0d;} d*=2.0d;
long double l=1.0L; while((long double)(1.0L+l) != 1.0L){l/=2.0L;} l*=2.0L;
std:: cout << "Machine precision with the while loop: \n";
std::cout << "      float eps="<< f << "\n";
std::cout << "     double eps =" << d << "\n";
std::cout <<"long double eps= "<< l <<"\n \n";
std::cout << "Machine precision using limits \n";
std::cout << std::numeric_limits<float>::epsilon() << "\n";
std::cout << std::numeric_limits<double>::epsilon() << "\n";
std::cout << std::numeric_limits<long double>::epsilon() << "\n \n";

std:: cout << "Comment: Mchine precision for the while loop and with the limit are the same.\nComparing with 2^-52 for double, and 2^-23 for float:\n";
std::cout << "Double 2^-52: " << std::pow(2,-52) << "\n";
std::cout << "Float 2^-23: " << std::pow(2,-23) << "\n\n";


// 2. non-commutativity of addition
double epsilon=std::pow(2,-52);
double tiny=epsilon/2;
double a=1+tiny+tiny;
double b=tiny+tiny+1;
std:: cout << "2. non-commutativity of addition \n";
std::cout << "a==b ? " << (a==b ? "true":"false") << "\n";
std::cout << "a>1  ? " << (a>1  ? "true":"false") << "\n";
std::cout << "b>1  ? " << (b>1  ? "true":"false") << "\n";
std::cout << "Explanation (after consulting a chatbot): For a: we do (1 + tiny) + tiny, where the (1 + tiny) will evaluate to be 1, and then again 1 + tiny is 1, resulting in 1.\nFor b: we do (tiny + tiny) + 1, where (tiny + tiny) results in a non-zero value, and therefore adding 1 results in a value bigger then 1. \n \n";

std::cout << std::fixed << std::setprecision(17);
std::cout << "       tiny=" << tiny << "\n";
std::cout << "1+tiny+tiny=" << a << "\n";
std::cout << "tiny+tiny+1=" << b << "\n\n";

//3. Comparing doubles: introduction
std::cout << "3. Comparing doubles\n";
double d1 = 0.1+0.1+0.1+0.1+0.1+0.1+0.1+0.1;
double d2 = 8*0.1;
std::cout << "d1==d2? " << (d1==d2 ? "true":"false") << "\n"; 
std::cout << std::fixed << std::setprecision(17);
std::cout << "d1=" << d1 << "\n";
std::cout << "d2=" << d2 << "\n";

std::cout << "d1==d2? with bool approx: " << (approx(d1,d2)  ? "true" : "false" )<< "\n";
return 0;
}