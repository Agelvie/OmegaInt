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
	cout << "MAXDIGITS: " << MAXDIGITS << endl;
	cout << "MAXFIELDVALUE: " << MAXFIELDVALUE << endl;
	cout << "ALLOWED: " << ALLOWED << endl;

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

	A = OmegaInt(MAXFIELDVALUE - 1) + 1;
	testC("Maintenance Giving", A == MAXFIELDVALUE and A.fields() == 2);

	A = OmegaInt(MAXFIELDVALUE) - 1;
	testC("Maintenance Taking", A == MAXFIELDVALUE-1 and A.fields() == 1);

	testC("Operator >", OmegaInt(3) > OmegaInt(2));
	testC("Operator ==", OmegaInt(3) == OmegaInt(3));

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

	testC("Test X - X", (X - X) == 0);
	A = 1; testC("Test 1 - 1", (A - 1) == 0);
	A = 0; testC("Test 0 - 1", (A - 1) == -1);
	A = 2; testC("Test 2 - 3", (A - 3) == -1);

	while(A > 0){ A -= 1; }
	testC("Test while(A > 0)", A == 0);

	testC("String Consrtuctor with 0 -> OmegaInt(\"0\") ", OmegaInt("0") == 0);

	// for (int i = 0; i < 7; ++i)
	// {
	// 	cout << OmegaInt(1234)._split_from(i) << '\t' << OmegaInt(1234)._split_to(i) << endl;
	// }
	// for (int i = 0; i < 5; ++i)
	// {
	// 	cout << OmegaInt(1234)._e10(i) << endl;
	// }
	
	testC("1 Digit Multiplication", OmegaInt(2) * OmegaInt(2) == 4);

	testC("- * + Multiplication", OmegaInt(-12345) * OmegaInt(6789) == -83810205);
	testC("+ * - Multiplication", OmegaInt(12345) * OmegaInt(-6789) == -83810205);
	testC("- * - Multiplication", OmegaInt(-12345) * OmegaInt(-6789) == 83810205);

	testC("5 Digit Multiplication", OmegaInt(12345) * OmegaInt(6789) == 83810205);

	testC("16 Digit Multiplication", OmegaInt("1092384710293847") * OmegaInt("1092384710293847") 
																== "1193304355283772039845086059409");


	testC("64 Digit Multiplication", OmegaInt("3141592653589793238462643383279502884197169399375105820974944592") 
								   * OmegaInt("2718281828459045235360287471352662497757247093699959574966967627") 
== "8539734222673567065463550869546574495034888535765114961879601127067743044893204848617875072216249073013374895871952806582723184");

testC( "212 Digit Multiplication",
  OmegaInt("27182818284590452353602829837409234659812834692837659238476574713526624977534972470345936999595749669676271238410298409234875923831415926535897932384626433832795028842837491328478321971987369399375105820974944592") 
* OmegaInt("27182818284590452353602829837409234659812834692837659238476574713526624977534972470345936999595749669676271238410298409234875923831415926535897932384626433832795028842837491328478321971987369399375105820974944592") 
== "738905609893065022723040306338812103403690869683176224646524075329403239381000705130240528793667901575103384514255161480205215799687383613757095682703930175950904351659328420371856756618493649480324118217553822251088493797632925153114551664381475270521027369906603232527693994952884709313387584104310591674284595556118512001880922214682100257256821788916821002367137392684790030227970848898031312651967598223967837470046464");

testC("Addition '+' ++", (OmegaInt(27) + OmegaInt(7)) == 34 );
testC("Addition '+' +-", (OmegaInt(27) + OmegaInt(-7)) == 20 );
testC("Addition '+' -+", (OmegaInt(-27) + OmegaInt(7)) == -20 );
testC("Addition '+' --", (OmegaInt(-27) + OmegaInt(-7)) == -34 );

testC("Subtraction '-' ++", (OmegaInt(27) - OmegaInt(7)) == 20 );
testC("Subtraction '-' +-", (OmegaInt(27) - OmegaInt(-7)) == 34 );
testC("Subtraction '-' -+", (OmegaInt(-27) - OmegaInt(7)) == -34 );
testC("Subtraction '-' --", (OmegaInt(-27) - OmegaInt(-7)) == -20 );

testC("Consrtuctor: Templated", OmegaInt(-12) == -12);
testC("Friend Operators (int)", -12 + OmegaInt(-4) == -16);
testC("Friend Operators (int)", -12 + OmegaInt(4) == -8);
testC("Friend Operators (string)", "-12" + OmegaInt(4) == -8);

	return 0;
}