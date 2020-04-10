#include <iostream>
#include <cmath>
#include <cstdlib>
#include <limits>
#include <iomanip>
#include <type_traits>
#include <sstream>

#pragma once

#define _ std::cin.get();

typedef unsigned long long u64;

// Maximum number of digits a field can have. (System depedent)
// const unsigned MAXDIGITS = floor(std::numeric_limits<u64>::digits * log10(2) / 2);
// const unsigned MAXDIGITS = pow(10, floor(log10(std::numeric_limits<u64>::digits)));
// const unsigned ALLOWED = log10(MAXDIGITS) % 2 == 0? sqrt(MAXDIGITS) : sqrt(MAXDIGITS -1);
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
	
	// Maintenance routine
	void _maintenance();
	void _reSize(u64 newSize, u64* NUMBERS);

	public:
	// Construction and Deletion
		// Empty
	OmegaInt();

		// From a number represented in a string
	OmegaInt(std::string num);
	OmegaInt(char const* num);

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
	void operator += (OmegaInt const & other);
	void operator -= (OmegaInt const & other);


	// Output Methods
		// Prints the number as a string
	std::string toString() const;
	void debugPrint();
	void print();
	friend std::ostream& operator<<(std::ostream & os, const OmegaInt & A);

	// Templated Methods
	template < typename T>
	OmegaInt(T foo)
	{
		try
		{
			if(! std::is_arithmetic<T>::value){throw 1;}
		}
		catch(int e)
		{ cout << "Incorrect constructor, for pointer types the correct constructor is OmegaInt(u64 fields, u64* nums, bool pos);"; }
		isPOSITIVE = foo >= 0;
		u64 num = std::abs(foo);
		TOTALFIELDS = num != 0? floor( (log10(num) )/ MAXDIGITS ) + 1 : 1;

		NUMBERS = (u64*) calloc( TOTALFIELDS, sizeof(u64) );
		for (unsigned i = 0; i < TOTALFIELDS; ++i)
		{
			NUMBERS[i] = num % MAXFIELDVALUE;
			num = (num - (num % MAXFIELDVALUE)) / MAXFIELDVALUE;
		}
	};

	template < typename T>
	OmegaInt const & operator = (T num)
	{
		if (!std::is_integral<T>::value and !std::is_floating_point<T>::value)
			{ return * new OmegaInt(); }

		_copy(OmegaInt(num));
		return *this;
	};

	OmegaInt const & operator = (std::string num)
		{ _copy(OmegaInt(num)); return *this; };

	OmegaInt const & operator =(char const* num)
		{ _copy(OmegaInt(num)); return *this; };
	// lsdkfj
	template < typename T >
	bool operator == (T const num) const { return *this == (OmegaInt(num)); };
	
	template < typename T >
	bool operator >  (T num) const { return *this > (OmegaInt(num)); }

	template < typename T >
	OmegaInt operator + (T num) const { return *this + (OmegaInt(num)); }
	
	template < typename T >
	OmegaInt operator - (T num) const { return *this - (OmegaInt(num)); }

	template < typename T >
	OmegaInt operator * (T num) const { return *this * (OmegaInt(num)); }

	template < typename T >
	OmegaInt operator / (T num) const { return *this / (OmegaInt(num)); }

	template < typename T >
	void operator += (T num) { *this += (OmegaInt(num)); }

	template < typename T >
	void operator -= (T num) { *this -= (OmegaInt(num)); }
};