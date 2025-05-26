#include <iostream>
#include <cmath>

unsigned long long num_of_solutions(int n, unsigned long long mod);

int main () {
	int n = 0;
	unsigned long long mod;

	std::cin >> n >> mod;
	std::cout << num_of_solutions(n, mod) << std::endl;

	return 0;
}

unsigned long long num_of_solutions(int n, unsigned long long mod){
	unsigned long long* p = new unsigned long long[n + 1]{0};


	p[0] = 1;

	for (int k = 1; k <= n; ++k)
	{
		for (int i = 0; (i + k) <= n; ++i)
		{
			p[i + k] += p[i];
		    p[i + k] %= mod;
		}
	}

	unsigned long long result = p[n];

	delete[] p;

	return result;
}
