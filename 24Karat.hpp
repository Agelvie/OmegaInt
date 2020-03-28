#include <iostream>
#include <cmath>
#include <limits>

#define _ cin.get();
typedef unsigned long long u64;
using std::cout;
using std::endl;

class megaInt
{
	private:
	u64* NUMBERS;
	bool POSITIVE;
	u64 TOTALFIELDS;
	long MAXDIGITS;

	public:
	
	megaInt();
	megaInt(string num);
	megaInt(u64 fields, bool pos);
	megaInt(u64 fields, u64* nums, bool pos);
	~megaInt(){free(NUMBERS);

	void print();

	long fields();
	bool sing();
	u64 operator [] (long i);


	megaInt operator + (megaInt const & other) const;

	// An overloaded operator<<, allowing us to print the stack via `cout<<`:
    friend std::ostream& operator<<(std::ostream & os, const megaInt & A);
};