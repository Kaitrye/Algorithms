#include <iostream>
#include <fstream>
#include <iomanip>

double fast_sum_two (double& t, double a, double b)
{
	double s = a + b;
	double bs = s - a;
	double as = s - bs;
	t = (a - as) + (b - bs);

	return s;
}

int main(int argc, char* argv[]){
	
	if (argc < 2)
	{
		return -1;
	}

	std::ifstream inFile(argv[1]);

	if (!inFile.is_open ())
	{
		return -2;
	}

	size_t N;
	inFile >> N; 

	double sum = 0.0; // rounded sum.
	double cs = 0.0; // sum of errors.
	double c; // current error.

	double num;
	for (size_t i = 0; i < N; ++i)
	{
		inFile >> num;
		
		sum = fast_sum_two (c, sum, num);
		cs += c;
	}

	std::cout << std::scientific << std::setprecision(std::numeric_limits<double>::max_digits10) << sum + cs << "\n";

	inFile.close();

	return 0;
}
