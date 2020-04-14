#include <iostream>
#include <cmath>
#include <limits>
#include "24Karat.hpp"

// #define _ cin.get();
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

// template <typename T>
// void displayEqual( OmegaInt &A, T value )
// {}

void testC(std::string message, bool pass)
{
	static unsigned i = 0;
	cout << (pass? "\033[1;32mPASS\033[0m" : "\033[1;31mFAIL\033[0m");
	cout << "\tTEST " << i++ << ": " << message << endl;
}

void testC_Right(std::string message, bool pass)
{
	static unsigned i = 0;
	static int width = 80;

	std::ostringstream ss;

	ss << "TEST " << i++ << ": " << message << ' ';
	cout << ss.str();

	for (int i = 0; i < (int)(width - ss.str().size()); ++i)
		{ cout << '_'; }
	cout << (pass? "\033[1;32mPASS\033[0m" : "\033[1;31mFAIL\033[0m") << endl;
}

void test(std::string message, bool pass)
{
	static unsigned i = 0;
	cout << "TEST " << i++ << ":\t" << message << '\t';
	cout << (pass? "PASS" : "FAIL") << endl;
};

// int main(int argc, char const *argv[])
// void test();

int main()
{
	// OmegaInt X("12345678901234567890");
	OmegaInt X("1234");
	// cout << "X = " << X << endl;

	OmegaInt Y("456");
	// cout << "Y = "<< Y << endl;

	OmegaInt Z("-986");
	// cout << "Z = " << Z << endl;

	OmegaInt A(0);
	// cout << "A = " << A << endl;

	A = 1;
	// cout << "A = " << A << endl;
	testC("Int Assignation '='", A == 1);

	A = "0002";
	// cout << "A = " << A << endl;
	testC("String Assignation (with removal of leading zeros) '='", A == 2);

	testC("Equal Int'=='", A == 2);

	testC("Equal String'=='", A == "2");

	testC("Subtraction '-'", (OmegaInt(27) - OmegaInt(7)) == 20 );

	A = X + Y;
	testC("Addition '+'", A == (X + Y) );

	A = (OmegaInt(101) - OmegaInt(98));
	testC("Subtraction '-' and Maintenance", A == 3 and A.fields() == 1 );

	A = (OmegaInt(9999) + OmegaInt(1));
	testC("Maintenance", A == 10000 and A.fields() == 3);

	A = 3; A += OmegaInt(1);
	testC("Operator +=", A == 4);

	A = 3; A -= 1;
	testC("Operator -=", A == 2);

	A = X > Y? X: Y;
	testC("Test ternary operator '?'", A == X);

	testC("Test add zero", (A + 0) == A);
	testC("Test substract zero", (A - 0) == A);

	A = -1;
	testC("Test abs", A.abs() == 1);

	A = 12345678;
	testC("Test num of digits positive", A.digits() == 8);

	A = -12345678;
	testC("Test num of digits positive", A.digits() == 8);

	// cout << "(X - X)\n";
	// (X - X).debugPrint();
	// cout << "OmegaInt(0)\n";
	// (OmegaInt(0)).debugPrint();

	testC("Test X - X", (X - X) == 0);
	A = 1; testC("Test 1 - 1", (A - 1) == 0);
	A = 0; testC("Test 0 - 1", (A - 1) == -1);
	A = 2; testC("Test 2 - 3", (A - 3) == -1);

	while(A > 0){ A -= 1; }
	testC("Test while(A > 0)", A == 0);

	// cout << (OmegaInt(2) * OmegaInt(2)) << endl;

	cout << OmegaInt(1234567)._split_to(1) << endl;
	cout << OmegaInt(1234567)._split_to(2) << endl;
	cout << OmegaInt(1234567)._split_to(3) << endl;
	cout << OmegaInt(1234567)._split_to(4) << endl;
	cout << OmegaInt(1234567)._split_to(5) << endl;

	// testC("1 Digit Multiplication", OmegaInt(2) * OmegaInt(2) == 4);
	
	// testC("5 Digit Multiplication", OmegaInt(12345) * OmegaInt(67890) == 838102050);

	// testC("16 Digit Multiplication", OmegaInt("1092384710293847") * OmegaInt("1092384710293847") 
	// 															== "1193304355283772039845086059409");

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