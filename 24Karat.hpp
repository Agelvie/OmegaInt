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

class OmegaInt
{
	private:
		// Number of pieces the number is split into
	u64 TOTALFIELDS;
		// Pieces that comprice the number
	u64* NUMBERS;
		// Sing, is it positive?
	bool isPOSITIVE;
		// Copy function
	void _copy(OmegaInt const & other)

	public:
	// Construction and Deletion
		// Empty
	OmegaInt();
		// From a number represented in a string
	OmegaInt(string num);
		// Number of fields and sing setted all to zero
	OmegaInt(u64 fields, bool pos);
		// Number of fields and sing setted all to a value
	OmegaInt(u64 fields, u64* nums, bool pos);
		// Copy constructor
	OmegaInt(OmegaInt const & other);
		// Destructor
	~OmegaInt();

	// Assingment Operator
	OmegaInt const & operator= (OmegaInt const & other);

	// Getters
		// Returns the number of fields in the OmegaInt
	unsigned fields() const;
		// Returns the sing of the OmegaInt
	bool sing() const;

	// Setter
		// Changes the sing of the OmegaInt
	void changeSing();

	// Getter and Setter? Make private?
	u64 operator [] (const unsigned i) const;

	// Comparison Operators
	friend bool operator == (const OmegaInt &A, const OmegaInt &B);
	friend bool operator != (const OmegaInt &A, const OmegaInt &B);
	friend bool operator >  (const OmegaInt &A, const OmegaInt &B);
	friend bool operator >= (const OmegaInt &A, const OmegaInt &B);
	friend bool operator <  (const OmegaInt &A, const OmegaInt &B);
	friend bool operator <= (const OmegaInt &A, const OmegaInt &B);

	// Arithmetic Operators
	OmegaInt operator + (OmegaInt const & other) const;
	OmegaInt operator - (OmegaInt const & other) const;
	OmegaInt operator * (OmegaInt const & other) const;
	OmegaInt operator / (OmegaInt const & other) const;

	// Output Methods
	void print();
	friend std::ostream& operator<<(std::ostream & os, const OmegaInt & A);
};