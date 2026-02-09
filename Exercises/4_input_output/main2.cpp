#include<iostream>
#include<cmath>

int main(){
    // 2. Standard input stream
    std::cout << "2. Standard input stream \nx, sin(x), cos(x)\n";
    double x;
    while( std::cin >> x ){
	    std::cout << x <<" "<< std::sin(x) <<" "<< std::cos(x) << std::endl;
	}
    return 0;
}