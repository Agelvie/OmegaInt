#include <iostream>
#include <cmath>
#include <limits>

typedef unsigned long long u64;
const unsigned MAXDIGITS2 = floor(std::numeric_limits<u64>::digits * log10(2) / 2);

int main(int argc, char const *argv[])
{
	std::cout << MAXDIGITS2 << std::endl;

	return 0;
}