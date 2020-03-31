#include "24Karat.hpp"
	//@TODO -- check that every field is less than or equal to MAXFIELDVALUE
	//@TODO -- if top fields are only zeros -> erase
	//@TODO -- allocate new memory if final field is aproaching it's limit
	//@TODO -- template for interaction with primitives
	//@TODO -- template for assingment from string
	//@TODO -- implement *
	//@TODO -- implement /

	// Empty
OmegaInt::OmegaInt()
{
	TOTALFIELDS = 0;
	NUMBERS = NULL;
	isPOSITIVE = true;
};

// template<typename T>
// OmegaInt::OmegaInt(T foo)
// {
// 	isPOSITIVE = foo >= 0;
// 	u64 num = std::abs(foo);
// 	TOTALFIELDS = num / MAXFIELDVALUE;

// 	NUMBERS = (u64*) calloc( TOTALFIELDS, sizeof(u64) );

// 	for (unsigned i = 0; i < TOTALFIELDS; ++i)
// 	{
// 		NUMBERS[i] = num % MAXFIELDVALUE;
// 		cout << num % MAXFIELDVALUE << endl;
// 		num = (num - (num % MAXFIELDVALUE)) / MAXFIELDVALUE;
// 	}
// };

	// From a number represented in a string
OmegaInt::OmegaInt(std::string num)
{
	unsigned i = 0, j;
	while (num.find(' ') == 0){ num = num.substr(1,num.size()); }

	// check for a negative sing
	if (num.find('-') != string::npos)
	{
		isPOSITIVE = false;
		num = num.substr(1,num.size());
	}

	// calculate the number of fields required to hold that number
	TOTALFIELDS = num.size() / MAXDIGITS;
	// the divition was not exact and there is the need for another field
	if (num.size() % MAXDIGITS != 0){ TOTALFIELDS++; }

	// NUMBERS = new u64[TOTALFIELDS];
	NUMBERS = (u64*) calloc( TOTALFIELDS, sizeof(u64) );


	j = MAXDIGITS;
	// to prevent accessing memory that isn't there
	if ( j >= num.size() ){ j = num.size(); }
	// little endian
	while(num.size() > 0)
	{
		NUMBERS[i] = atoll( (num.substr(num.size() - j, num.size())).data() );
		num.erase(num.size() - j, num.size());
		if ( j >= num.size() ){ j = num.size(); }
		i++;
	}
};

OmegaInt::OmegaInt(char const* num) { *this = OmegaInt((std::string)num);}

	// Number of fields and sing setted all to zero
OmegaInt::OmegaInt(u64 fields, bool pos)
{
	// calculate the number of fields required to hold that number
	TOTALFIELDS = fields;

	NUMBERS = (u64*) calloc( TOTALFIELDS, sizeof(u64) );

	for (unsigned i = 0; i < TOTALFIELDS; ++i)
		{ NUMBERS[i] = 0; }

	isPOSITIVE = pos;
};

	// Number of fields and sing setted all to a value
OmegaInt::OmegaInt(u64 fields, u64* nums, bool pos)
{
	// calculate the number of fields required to hold that number
	TOTALFIELDS = fields;

	NUMBERS = (u64*) calloc( TOTALFIELDS, sizeof(u64) );

	isPOSITIVE = pos;

	for (unsigned i = 0; i < fields; ++i){ NUMBERS[i] = nums[i]; }
};

	// Copy constructor
OmegaInt::OmegaInt(OmegaInt const & other)
{
	NUMBERS = NULL;
	_copy(other);
};

	// Destructor
OmegaInt::~OmegaInt(){ free(NUMBERS); NUMBERS = NULL; };

	// Assingment Operator
OmegaInt const & OmegaInt::operator= (OmegaInt const & other)
{
	if (this != &other) { _copy(other); }
    return *this;
};

void OmegaInt::_copy(OmegaInt const & other)
{
	if (NUMBERS != NULL){ delete[] NUMBERS; }

	TOTALFIELDS = other.fields();
	isPOSITIVE = other.sing();
	
	NUMBERS = (u64*) calloc( TOTALFIELDS, sizeof(u64) );

	for (unsigned i = 0; i < TOTALFIELDS; ++i){ NUMBERS[i] = other[i]; }
}

// Getters
	// Returns the number of fields in the OmegaInt
unsigned OmegaInt::fields() const { return TOTALFIELDS; }

	// Returns the sing of the OmegaInt
bool OmegaInt::sing() const { return isPOSITIVE; }
	
	// Absolute value, returns the whole object
OmegaInt OmegaInt::abs() const
{
	OmegaInt A(*this);
	if ( ! A.isPOSITIVE ){ A.changeSing(); }
	return A;
};

// Setter
	// Changes the sing of the OmegaInt
void OmegaInt::changeSing(){ isPOSITIVE = !isPOSITIVE; };

// Getter and Setter? Make private?
u64 OmegaInt::operator [] (const unsigned i) const { return NUMBERS[i]; }

void OmegaInt::set (const unsigned i, u64 value) { NUMBERS[i] = value; }

// Comparison Operators
bool OmegaInt::operator == (const OmegaInt &other) const
{
	const OmegaInt A = *this;
	const OmegaInt& B = other;
	bool equalLength = A.fields() == B.fields();	// Different lenghts does NOT nesesarily mean
	bool isAlonger = A.fields() > B.fields();		// that they are different numbers
	unsigned min = isAlonger? B.fields(): A.fields();	// Pick the shortest one

	if (A.sing() != B.sing()){ return false; }

	for (unsigned i = 0; i < min; ++i)
		{ if (A[i] != B[i]){ return false; } }

	// If higher pieces of longest number are not zero return false
	if (!equalLength)
	{
		if (isAlonger)
		{ for (unsigned i = min; i < A.fields(); ++i) { if (A[i] != 0){ return false; } } }
		else
		{ for (unsigned i = min; i < B.fields(); ++i) { if (B[i] != 0){ return false; } } }
	}

	return true;
};

bool OmegaInt::operator != (const OmegaInt &other) const
{
	return !(*this == other);
};

bool OmegaInt::operator >  (const OmegaInt &other) const
{
	const OmegaInt A = *this;
	const OmegaInt& B = other;
	bool equalLength = A.fields() == B.fields();	// Different lenghts does NOT nesesarily mean
	bool isAlonger = A.fields() > B.fields();		// that they are different numbers
	unsigned min = isAlonger? B.fields() : A.fields();	// Pick the shortest one
	bool hasAgreaterABS;

	// A is possitive an B negative
	if (A.sing() and !B.sing()){ return true; }
	
	// A is negative an B positive
	if (!A.sing() and B.sing()){ return false; }

	if (!equalLength)
	{
		if (isAlonger)
		{ for (unsigned i = min; i < A.fields(); ++i) { if (A[i] != 0){ hasAgreaterABS = true; } } }
		else
		{ for (unsigned i = min; i < B.fields(); ++i) { if (B[i] != 0){ hasAgreaterABS = false; } } }
	}
	else
	{
		int i = min == 0? min : min - 1;
		bool done = false;
		while (!done and i >= 0)
		{
			if 		(A[i] > B[i]){ hasAgreaterABS = true; done = true; }
			else if (A[i] < B[i]){ hasAgreaterABS = false; done = true; }
			else 	{ i--; }
		}
	}

	return (A.sing() and B.sing())? hasAgreaterABS : !hasAgreaterABS;
};
bool OmegaInt::operator >= (const OmegaInt &other) const
{
	return (*this == other) or (*this > other);
};
bool OmegaInt::operator <  (const OmegaInt &other) const
{
	return !(*this == other) or (*this > other);
};
bool OmegaInt::operator <= (const OmegaInt &other) const
{
	return (*this == other) or (*this < other);
};

OmegaInt OmegaInt::_add(OmegaInt const & other) const
{
	// ONLY returns positive OmegaInt's
	/* For simplicity alising ( this + other ) = ( A + B ) = RESULT */
	const OmegaInt A = *this;
	const OmegaInt& B = other;

	unsigned min = A.fields() > B.fields()? B.fields() : A.fields();
	unsigned Max = A.fields() > B.fields()? A.fields() : B.fields();
	
	OmegaInt RESULT( Max+1, true );

	for (unsigned i = 0; i < min; ++i)
		{ RESULT.set(i, A[i] + B[i]); }
	for (unsigned i = min; i < Max; ++i)
		{ RESULT.set(i, A.fields() > B.fields()? A[i] : B[i]); }

	return RESULT;
};

OmegaInt OmegaInt::_subtract(OmegaInt const & other) const
{
	bool carry = false;
	// returns OmegaInt's with APPROPRIATE given the operands
	/* For simplicity alising ( this - other ) = ( A - B ) = RESULT */
	OmegaInt A = *this;
	OmegaInt B = other;

	unsigned min = A.fields() > B.fields()? B.fields() : A.fields();
	unsigned Max = A.fields() > B.fields()? A.fields() : B.fields();
	
	OmegaInt RESULT( Max+1, true );

	if (B.abs() > A.abs())
	{
		OmegaInt C(A);
		A = B;
		B = C;
		RESULT.changeSing();
	}

	u64 temp;

	for (unsigned i = 0; i < min; ++i)
	{
		temp = (A[i] < B[i]? MAXFIELDVALUE : 0) + A[i] - B[i] - (carry? 1 : 0);
		carry = A[i] < B[i];

		RESULT.set(i, temp);
	}

	for (unsigned i = min; i < Max; ++i)
	{
		RESULT.set(i, A[i] - (carry? 1 : 0));
		carry = false;
	}

	return RESULT;
};

// Arithmetic Operators
OmegaInt OmegaInt::operator + (OmegaInt const & other) const
{
	OmegaInt RESULT;

	if      (  this->sing() and  other.sing() )  { RESULT = this->_add(other); }
	else if ( !this->sing() and  other.sing() )  { RESULT = other - *this; }
	else if (  this->sing() and !other.sing() )  { RESULT = *this - other; }
	else /* ( !this->sing() and !other.sing() )*/{ RESULT = this->_add(other); RESULT.changeSing(); }

	return RESULT;
};
OmegaInt OmegaInt::operator - (OmegaInt const & other) const
{
	OmegaInt RESULT;

	if      (  this->sing() and  other.sing() )  { RESULT = this->_subtract(other); }
	else if ( !this->sing() and  other.sing() )  { RESULT = this->_add(other); RESULT.changeSing(); }
	else if (  this->sing() and !other.sing() )  { RESULT = this->_add(other); }
	else /* ( !this->sing() and !other.sing() )*/{ RESULT = other._subtract(*this); }

	return RESULT;
};
OmegaInt OmegaInt::operator * (OmegaInt const & other) const
{
	return other;
};
OmegaInt OmegaInt::operator / (OmegaInt const & other) const
{
	return other;

};

// Prints the number as a string
std::string OmegaInt::toString() const
{
	std::ostringstream ss;

	if ( !this->isPOSITIVE ){ ss << '-';}
	for (unsigned i = 0; i < TOTALFIELDS; ++i)
	{
		if (i == 0)
		{ ss << NUMBERS[TOTALFIELDS - i - 1]; }
		else
		{ ss << std::setfill('0') << std::setw(MAXDIGITS) << NUMBERS[TOTALFIELDS - i - 1]; }
	}

	return ss.str();
}

// Output Methods
void OmegaInt::debugPrint()
{
	for (unsigned i = 0; i < TOTALFIELDS; ++i)
	{
		cout << std::setfill('0') << std::setw(MAXDIGITS) << NUMBERS[i] << endl;
	}

	cout << endl;
}

void OmegaInt::print()
{
	cout << this->toString() << endl;
}

std::ostream& operator<<(std::ostream & os, const OmegaInt & A)
{
	os << A.toString();
	return os;
}

