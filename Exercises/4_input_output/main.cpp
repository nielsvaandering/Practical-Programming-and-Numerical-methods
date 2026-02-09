#include<iostream>
#include<vector>
#include<cmath>

//It was annoying to input 1 and 2 at the same time, so I made them in a seperate file, with seperate output
int main (int argc, char* argv[]) {
    // 1. Command-line
	std::vector<double> numbers;
	for(int i=0;i<argc;++i){
		std::string arg=argv[i];
		if(arg=="-n" && i+1<argc)
			numbers.push_back(std::stod(argv[i+1]));
	}
    std::cout << "I made the output for 2 and 3 in an other file\n";
    std::cout << "1. Command-line\nnumber, sine, cosine\n";
    for(auto n: numbers)
	    std::cout << n <<" "<< std::sin(n) <<" "<< std::cos(n) <<"\n";

return 0;
}