#include <iostream>
#include <cmath>
#include <limits>

#pragma once

#define _ cin.get();

typedef unsigned long long u64;

// Maximum number of digits a field can have. (System depedent)
const unsigned MAXDIGITS = floor(std::numeric_limits<u64>::digits * log10(2) / 2);

using std::cout;
using std::endl;
using std::string;

class megaInt
{
	private:
		// Number of pieces the number is split into
	u64 TOTALFIELDS;
		// Pieces that comprice the number
	u64* NUMBERS;
		// Sing, is it positive?
	bool isPOSITIVE;

	public:
	// Construction and Deletion
		// Empty
	megaInt();
		// From a number represented in a string
	megaInt(string num);
		// Number of fields and sing setted all to zero
	megaInt(u64 fields, bool pos);
		// Number of fields and sing setted all to a value
	megaInt(u64 fields, u64* nums, bool pos);
		// Copy constructor
	megaInt(megaInt const & other);
		// Destructor
	~megaInt();

	// Assingment Operator
	megaInt const & operator= (megaInt const & other);

	// Getters
		// Returns the number of fields in the megaInt
	long fields();
		// Returns the sing of the megaInt
	bool sing();

	// Setter
		// Changes the sing of the megaInt
	void changeSing();

	// Getter and Setter? Make private?
	u64 operator [] (unsigned i);

	// Comparison Operators
	friend bool operator == (const megaInt &A, const megaInt &B);
    friend bool operator != (const megaInt &A, const megaInt &B);
    friend bool operator >  (const megaInt &A, const megaInt &B);
    friend bool operator >= (const megaInt &A, const megaInt &B);
    friend bool operator <  (const megaInt &A, const megaInt &B);
    friend bool operator <= (const megaInt &A, const megaInt &B);

    // Arithmetic Operators
	megaInt operator + (megaInt const & other) const;
	megaInt operator - (megaInt const & other) const;
	megaInt operator * (megaInt const & other) const;
	megaInt operator / (megaInt const & other) const;

	// Output Methods
	void print();
    friend std::ostream& operator<<(std::ostream & os, const megaInt & A);
};