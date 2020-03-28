#include <iostream>
#include <cmath>
#include <limits>
#include "24Karat.hpp"

#define _ cin.get();
typedef unsigned long long u64;
using std::cout;
using std::endl;


void splitInt ( u64 num, u64 n, u64 &high, u64 &low )
{
	low = num; high = 0;

	for (u64 i = 0; i < n; ++i)
	{
		num = num / 10;
	}

	high = num;

	low  = low - ( high * (u64)exp( n * log(10) ) );
}

u64 karatsuba (u64 num1, u64 num2)
{
	u64 m, mHalf;
	u64 high1, low1, high2, low2, z0, z1, z2;

	if ( (num1 < 10) or (num2 < 10) )
	{
		return num1 * num2;
	}

	/* calculates the size of the numbers */
	m = num2;
	if (num1 < num2)
	{
		m = num1;
	}

	m = (u64)log10(m) + 1;
	mHalf = floor(m/2);

	/* split the digit sequences in the middle */
	splitInt( num1, mHalf, high1, low1 );
	splitInt( num2, mHalf, high2, low2 );

	/* 3 calls made to numbers approximately half the size */
	z0 = karatsuba( low1, low2 );
	z1 = karatsuba( (low1 + high1), (low2 + high2) );
	z2 = karatsuba( high1, high2 );

	//					10 ^ (mHalf * 2)										10 ^ mHalf	
	return ( z2 * (u64)exp( mHalf * 2 * log(10) ) ) + ( (z1 - z2 - z0) * (u64)exp( mHalf * log(10) ) ) + z0;
}

int main(int argc, char const *argv[])
{
	// u64 a = atoll(argv[1]), b = atoll(argv[2]);

	// splitInt(123456789, 5, a, b);
	// cout << a << ' ' << b << endl;

	// cout << a << 'x' << b << " = " << karatsuba(a,b) << endl;

		// cout << ((string) "Hello world").size() << endl;
		// cout << numeric_limits<unsigned long long>::digits << endl;
		// cout << numeric_limits<unsigned long long>::digits * log10(2) << endl;
		// cout << "ceil(19/7) = "<< 19/7 << " + " << (19%7 != 0) << endl;
		// cout << "ceil(18/2) = "<< 18/2 << " + " << (18%2 != 0) << endl;
		// string a = "Hello_World"; int i = 3;
		// while (a.size() > 0)
		// {
		// 	cout << a.size() << ' ' << a.substr(a.size() - i, a.size()) << endl;
		// 	a.erase(a.size() - i, a.size());
		// 	if ( i >= a.size() ){ i = a.size(); }
		// }

	megaInt X("12345678901234567890");
	X.print();

	return 0;
}

// procedure karatsuba(num1, num2)
//   if (num1 < 10) or (num2 < 10)
//     return num1*num2

//   /* calculates the size of the numbers */
//   m = min(size_base10(num1), size_base10(num2))
//   m2 = floor(m/2) 
//   /*m2 = ceil(m/2) will also work */

//   /* split the digit sequences in the middle */
//   high1, low1 = split_at(num1, m2)
//   high2, low2 = split_at(num2, m2)

//   /* 3 calls made to numbers approximately half the size */
//   z0 = karatsuba(low1, low2)
//   z1 = karatsuba((low1 + high1), (low2 + high2))
//   z2 = karatsuba(high1, high2)

//   return (z2 * 10 ^ (m2 * 2)) + ((z1 - z2 - z0) * 10 ^ m2) + z0

// 3141592653589793238462643383279502884197169399375105820974944592
// 2718281828459045235360287471352662497757247093699959574966967627