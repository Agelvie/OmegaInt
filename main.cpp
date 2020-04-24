#include <iostream>
#include <cmath>
#include <limits>
#include "24Karat.hpp"
#include "OmegaUtils.hpp"

// #define _ cin.get();
typedef unsigned long long u64;
using std::cout;
using std::endl;

void testC(std::string message, bool pass)
{
	static unsigned i = 0;
	cout << (pass? "\033[1;32mPASS\033[0m" : "\033[1;31mFAIL\033[0m");
	cout << "\tTEST " << i++ << ": " << message << endl;
}

bool compare(string A, string B)
{
	if (A.size() != B.size()){ return false; }

	for (unsigned i = 0; i < A.size(); ++i)
	{
		if (A[i] != B[i]){ return false; }
	}

	return true;
}

int main(int argc, char const *argv[])
{
	cout << "MAXDIGITS: " << MAXDIGITS << endl;
	cout << "MAXFIELDVALUE: " << MAXFIELDVALUE << endl;
	cout << "ALLOWED: " << ALLOWED << endl;
	cout << "ARGC: " << argc << endl;

	// OmegaInt X("12345678901234567890");
	OmegaInt X("1234");
	// cout << "X = " << X << endl;

	OmegaInt Y("456");
	// cout << "Y = "<< Y << endl;

	OmegaInt Z("-986");
	// cout << "Z = " << Z << endl;

	OmegaInt A(0);
	// cout << "A = " << A << endl;

	for (int i = 1; i < argc; ++i)
	{
		if (compare(argv[i],"=") or argc == 1)
		{
			A = 1;
			testC("Int Assignation '='", A == 1);

			A = "0002";
			testC("String Assignation (with removal of leading zeros) '='", A == 2);
			testC("Equal Int'=='", A == 2);
			testC("Equal String'=='", A == "2");
		}

		if (compare(argv[i],"+") or argc == 1)
		{
			A = X + Y;
			testC("Addition '+'", A == (X + Y) );
			testC("Test add zero", (A + 0) == A);
			
			A = 3; A += OmegaInt(1);
			testC("Operator +=", A == 4);
			testC("Addition '+' ++", (OmegaInt(27) + OmegaInt(7)) == 34 );
			testC("Addition '+' +-", (OmegaInt(27) + OmegaInt(-7)) == 20 );
			testC("Addition '+' -+", (OmegaInt(-27) + OmegaInt(7)) == -20 );
			testC("Addition '+' --", (OmegaInt(-27) + OmegaInt(-7)) == -34 );
		}

		if (compare(argv[i],"-") or argc == 1)
		{
			A = 3; A -= 1;
			testC("Operator -=", A == 2);
			testC("Subtraction '-'", (OmegaInt(27) - OmegaInt(7)) == 20 );

			A = (OmegaInt(101) - OmegaInt(98));
			testC("Subtraction '-' and Maintenance", A == 3 and A.fields() == 1 );
			testC("Test substract zero", (A - 0) == A);
			testC("Test X - X", (X - X) == 0);

			A = 1; testC("Test 1 - 1", (A - 1) == 0);
			A = 0; testC("Test 0 - 1", (A - 1) == -1);
			A = 2; testC("Test 2 - 3", (A - 3) == -1);

			while(A > 0){ A -= 1; }
			testC("Test while(A > 0)", A == 0);

			testC("Subtraction '-' ++", (OmegaInt(27) - OmegaInt(7)) == 20 );
			testC("Subtraction '-' +-", (OmegaInt(27) - OmegaInt(-7)) == 34 );
			testC("Subtraction '-' -+", (OmegaInt(-27) - OmegaInt(7)) == -34 );
			testC("Subtraction '-' --", (OmegaInt(-27) - OmegaInt(-7)) == -20 );
		}
		
		if (compare(argv[i],"x") or argc == 1)
		{
			testC("1 Digit Multiplication", OmegaInt(2) * OmegaInt(2) == 4);

			testC("+ * + Multiplication", OmegaInt(12345) * OmegaInt(6789) == 83810205);
			testC("- * + Multiplication", OmegaInt(-12345) * OmegaInt(6789) == -83810205);
			testC("+ * - Multiplication", OmegaInt(12345) * OmegaInt(-6789) == -83810205);
			testC("- * - Multiplication", OmegaInt(-12345) * OmegaInt(-6789) == 83810205);
			testC("5 Digit Multiplication", OmegaInt(12345) * OmegaInt(6789) == 83810205);

			testC("16 Digit Multiplication", OmegaInt("1092384710293847") * OmegaInt("1092384710293847") 
																== "1193304355283772039845086059409");

			testC("64 Digit Multiplication", OmegaInt("3141592653589793238462643383279502884197169399375105820974944592") 
										   * OmegaInt("2718281828459045235360287471352662497757247093699959574966967627") 
													== "8539734222673567065463550869546574495034888535765114961879601127067743044893204848617875072216249073013374895871952806582723184");

			testC( "212 Digit Multiplication", OmegaInt("27182818284590452353602829837409234659812834692837659238476574713526624977534972470345936999595749669676271238410298409234875923831415926535897932384626433832795028842837491328478321971987369399375105820974944592") 
												* OmegaInt("27182818284590452353602829837409234659812834692837659238476574713526624977534972470345936999595749669676271238410298409234875923831415926535897932384626433832795028842837491328478321971987369399375105820974944592") 
											== "738905609893065022723040306338812103403690869683176224646524075329403239381000705130240528793667901575103384514255161480205215799687383613757095682703930175950904351659328420371856756618493649480324118217553822251088493797632925153114551664381475270521027369906603232527693994952884709313387584104310591674284595556118512001880922214682100257256821788916821002367137392684790030227970848898031312651967598223967837470046464");

			testC( "Power Operator ^" , (OmegaInt(3)^OmegaInt(3)) == 27 );
			testC( "Power Operator ^" , (OmegaInt(12)^OmegaInt(12)) == "8916100448256" );
		}

		if (compare(argv[i],"/") or argc == 1)
		{
			testC("Divition Operator '/' ",  OmegaInt(10) / OmegaInt(2) == 5);

			testC("Divition Operator Removing Tail zeros '/' ",  OmegaInt(10000000000) 
																/ OmegaInt(2000000000) == 5);

			testC("Divition Operator 8 Digits '/' ",  OmegaInt("12345678") / OmegaInt("12345") == "1000");

			testC("Divition Operator 14 Digits '/' ",  OmegaInt("33698323079548") / OmegaInt("398457209") == "84572");

			testC("Divition Operator 16 Digits '/' ",  OmegaInt("1193304355283772039845086059409") 
													/ OmegaInt("1092384710293847") == "1092384710293847");

			testC("Divition Operator 16 Digits '/' ",  OmegaInt("5671245623433698323079548") 
													 / OmegaInt("1092384710293847") == "5191619371");
			testC("Divition Operator 16 Digits '/' ",  OmegaInt("5671245623433698323079548") 
													 / OmegaInt("1092384710293847") == "5191619371");

			testC("Divition Operator Single word denominator '/' ",  OmegaInt("56712456234336983") 
																	/ OmegaInt("134") == "423227285330873");

			testC("Reminder Operator '%' ",  OmegaInt(11) % OmegaInt(2) == 1);
			// testC("Reminder Operator '%' ",  OmegaInt(-11) % OmegaInt(2) == 1);
		}

		if (compare(argv[i],"utils") or argc == 1)
		{
			testC("String Consrtuctor with 0 -> OmegaInt(\"0\") ", OmegaInt("0") == 0);
			A = OmegaInt(MAXFIELDVALUE - 1) + 1;
			testC("Maintenance Giving", A == MAXFIELDVALUE and A.fields() == 2);

			A = OmegaInt(MAXFIELDVALUE) - 1;
			testC("Maintenance Taking", A == MAXFIELDVALUE-1 and A.fields() == 1);
			A = -1;
			testC("Test abs", A.abs() == 1);
			A = 12345678;
			testC("Test num of digits positive", A.digits() == 8);
			testC("Consrtuctor: Templated", OmegaInt(-12) == -12);
			testC("Friend Operators (int)", -12 + OmegaInt(-4) == -16);
			testC("Friend Operators (int)", -12 + OmegaInt(4) == -8);
			testC("Friend Operators (string)", "-12" + OmegaInt(4) == -8);

			testC("Is even?", OmegaInt("123456789012345678901234567890").even());
			testC("Is odd?", !( OmegaInt("123456789012345678901234567890").odd() ));
			A = "123456789012345678901234567890120394872403976418273468746592853476";
			testC("Is odd/even LARGE value", A.odd() != A.even() );
			A = "-1";
			testC("Is odd/even small value", A.odd() != A.even() );


			testC("GCD", OmegaUtils::GCD( 10, 5) == 5 );
			testC("GCD", OmegaUtils::GCD( 19231*5, 19237*5) == 5 );
			testC("GCD", OmegaUtils::GCD( 253209919*5, 253209923*5) == 5 );
			testC("GCD", OmegaUtils::GCD( 9012983, 2389470 ) == 1 );

			testC("lcm", OmegaUtils::lcm( 12, 15 ) == 60 );
			testC("lcm", OmegaUtils::lcm( 9012983, 2389470 ) == 21536252489010 );
			X = "70293487502938475023984750239876";
			Y = "23984787216548758649586932847653";
			A = OmegaUtils::GCD(X,Y);
			testC("lcm LARGE", OmegaUtils::lcm( X, Y ) == (X * Y) / A );
			
			// testC("Test e10^i function", OmegaInt(1234)._e10(3) == 1234000);
			// testC("Test _split_from(i)", OmegaInt(12345)._split_from(2) == 123);
			// testC("Test _split_to(i)", OmegaInt(12345)._split_to(2) == 45);

		}

		if (compare(argv[i],"bool") or argc == 1)
		{
			testC("Operator >", OmegaInt(3) > OmegaInt(2));
			testC("Operator ==", OmegaInt(3) == OmegaInt(3));
			A = X > Y? X: Y;
			testC("Test ternary operator '?'", A == X);
		}

	}

	return 0;
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
