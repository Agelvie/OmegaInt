#include <iostream>
#include <cmath>
#include <cstdlib>
#include <limits>
#include <iomanip>
#include <type_traits>

#pragma once

#define _ std::cin.get();

typedef unsigned long long u64;

// Maximum number of digits a field can have. (System depedent)
// const unsigned MAXDIGITS = floor(std::numeric_limits<u64>::digits * log10(2) / 2);
const unsigned MAXDIGITS = 2; // for testing purposes

// Maximum value that a field can have. (System depedent), values are strictly less than
const u64 MAXFIELDVALUE = pow(10,MAXDIGITS);
// #define MAXFIELDVALUE (pow(10,MAXDIGITS) - 1);

using std::cout;
using std::endl;
using std::string;

class OmegaInt
{
	private:
		// Number of pieces the number is split into
	u64 TOTALFIELDS;
		// Pieces that comprice the number
	u64* NUMBERS = NULL;
		// Sing, is it positive?
	bool isPOSITIVE;
		// Absolute value, returns the whole object
	OmegaInt abs() const;
		// Copy function
	void _copy(OmegaInt const & other);
		// Addition function
	OmegaInt _add(OmegaInt const & other) const;
		// Subtraction function
	OmegaInt _subtract(OmegaInt const & other) const;

	public:
	// Construction and Deletion
		// Empty
	OmegaInt();
		// From a number represented in a string
	// OmegaInt(string num);
		// From a primitive number
	template <typename T>
	OmegaInt(T num);
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
		// set field 'i' to a value
	void set (const unsigned i, u64 value);


	// Getter
	u64 operator [] (const unsigned i) const;

	// Comparison Operators
	bool operator == (OmegaInt const &other) const;
	bool operator != (const OmegaInt &other) const;
	bool operator >  (const OmegaInt &other) const;
	bool operator >= (const OmegaInt &other) const;
	bool operator <= (const OmegaInt &other) const;
	bool operator <  (const OmegaInt &other) const;

	// Arithmetic Operators
	OmegaInt operator + (OmegaInt const & other) const;
	OmegaInt operator - (OmegaInt const & other) const;
	OmegaInt operator * (OmegaInt const & other) const;
	OmegaInt operator / (OmegaInt const & other) const;

	// Output Methods
	void print();
	friend std::ostream& operator<<(std::ostream & os, const OmegaInt & A);
};