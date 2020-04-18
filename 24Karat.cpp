#include "24Karat.hpp"
void bug()
{
	static unsigned i = 0;
	cout << i++;_
}
	//@TODO -- implement / and %
	//@TODO -- add an append method, maybe push_front and also push_back
	//@TODO -- implement bitwise operators
	//@TODO -- implement GCD
	//@TODO -- implement lcm

	// Empty
OmegaInt::OmegaInt()
{
	TOTALFIELDS = 0;
	NUMBERS = NULL;
	isPOSITIVE = true;
};

	// From a number represented in a string
OmegaInt::OmegaInt(std::string num)
{
	unsigned i = 0, j;
	// clean the num string
	while (num.find(' ') == 0){ num = num.substr(1,num.size()); }
	while (num.find('0') == 0){ num = num.substr(1,num.size()); }
	if (num.empty()){ num = "0"; }

	isPOSITIVE = true;
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
void OmegaInt::operator = (OmegaInt const & other)
	{ if (this != &other) { _copy(other); } };

void OmegaInt::operator = (std::string num)
	{ _copy(OmegaInt(num)); };

void OmegaInt::operator = (char const* num)
	{ _copy(OmegaInt(num)); };

	// Copy helper function
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
	
	// Absolute value, returns a positive copy of the object
OmegaInt OmegaInt::abs() const
{
	OmegaInt A(*this);
	if ( ! A.isPOSITIVE ){ A.changeSing(); }
	return A;
};
	// Returns the number of digits
u64 OmegaInt::digits() const
{
	return this->isPOSITIVE? (this->toString()).size() : (this->toString()).size()-1;
}

// Setter
	// Changes the sing of the OmegaInt
void OmegaInt::changeSing(){ isPOSITIVE = !isPOSITIVE; };

// Getter. Make private?
u64 OmegaInt::operator [] (const unsigned i) const { return NUMBERS[i]; }

void OmegaInt::set (const unsigned i, u64 value)
{
	if ( i > this->fields() ){ this->_reSize(i+1); } 
	NUMBERS[i] = value;
}

// Comparison Operators
bool OmegaInt::operator == (const OmegaInt &other) const
{
	const OmegaInt& A = *this;
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
	const OmegaInt& A = *this;
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
	const OmegaInt& A = *this;
	const OmegaInt& B = other;

	unsigned min = A.fields() > B.fields()? B.fields() : A.fields();
	unsigned Max = A.fields() > B.fields()? A.fields() : B.fields();

	// cout << Max << ' ' << min << endl;
	
	OmegaInt RESULT( Max+1, true );

	for (unsigned i = 0; i < min; ++i)
		{ /*cout << "min" << A[i] + B[i] << endl;*/ RESULT.set(i, A[i] + B[i]); }
	for (unsigned i = min; i < Max; ++i)
		{ /*cout << "MAX" << endl;*/ RESULT.set(i, A.fields() > B.fields()? A[i] : B[i]); }

	return RESULT;
};

OmegaInt OmegaInt::_subtract(OmegaInt const & other) const
{
	bool carry = false;
	// returns OmegaInt's with APPROPRIATE sing given the operands
	/* For simplicity alising ( this - other ) = ( A - B ) = RESULT */
	const OmegaInt& A = other.abs() > this->abs()? other : *this;
	const OmegaInt& B = other.abs() > this->abs()? *this : other;

	unsigned min = A.fields() > B.fields()? B.fields() : A.fields();
	unsigned Max = A.fields() > B.fields()? A.fields() : B.fields();
	
	OmegaInt RESULT( Max+1, true );

	if (other.abs() > this->abs())
		{ RESULT.changeSing(); }

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
	else if ( !this->sing() and  other.sing() )  { RESULT = other._subtract(*this); }
	else if (  this->sing() and !other.sing() )  { RESULT = this->_subtract(other); }
	else /* ( !this->sing() and !other.sing() )*/{ RESULT = this->_add(other); RESULT.changeSing(); }

	RESULT._maintenance();
	return RESULT;
};

OmegaInt OmegaInt::operator - (OmegaInt const & other) const
{
	OmegaInt RESULT;

	if      (  this->sing() and  other.sing() )  { RESULT = this->_subtract(other); }
	else if ( !this->sing() and  other.sing() )  { RESULT = this->_add(other); RESULT.changeSing(); }
	else if (  this->sing() and !other.sing() )  { RESULT = this->_add(other); }
	else /* ( !this->sing() and !other.sing() )*/{ RESULT = other._subtract(*this); }

	RESULT._maintenance();
	return RESULT;
};

	// split the OmegaInt from a certain digit
OmegaInt OmegaInt::_split_from(u64 split) const
{
	string temp = this->toString();
	if (split > temp.size()){ split = temp.size(); }
	temp = temp.substr(0, temp.size() - split);
	return OmegaInt( temp.empty()? "0" : temp );
}
	// split the OmegaInt to a certain digit
OmegaInt OmegaInt::_split_to(u64 split) const
{
	string temp = this->toString();
	if (split > temp.size()){ split = temp.size(); }
	temp = temp.substr(temp.size() - split, temp.size());
	return OmegaInt( temp.empty()? "0" : temp );
}
	
	// Multiplicating by a power of 10
OmegaInt OmegaInt::_e10(u64 power) const
{
	string temp = this->toString();
	// Add tailing zeros
	for (u64 i = 0; i < power; ++i)
		{ temp += '0'; }
	return OmegaInt(temp);
}

OmegaInt OmegaInt::_karatsuba(OmegaInt const & other) const
{
	// static long i = 0;
	// cout << i++ << endl;
	const OmegaInt& A = *this;
	const OmegaInt& B = other;
	// cout << A << '\t' << B << endl;
	if (A == 0 or B == 0){ return OmegaInt(0); }

	if (A.digits() < ALLOWED and B.digits() < ALLOWED )
	{
		return A.NUMBERS[0] * B.NUMBERS[0];
	}

	// calculates the size of the numbers
	u64 m2 = ceil((double)std::max( A.digits(), B.digits() ) / 2);

	// split the digit sequences in the middle
	OmegaInt A_high = A._split_from (m2);
	OmegaInt A_low  = A._split_to   (m2);
	OmegaInt B_high = B._split_from (m2);
	OmegaInt B_low  = B._split_to   (m2);

	// cout << m2 << endl;
	// cout << (A_high._e10(m2 )) << ' ' << (A_low) << 
	// '\t' << (B_high._e10(m2 )) << ' ' << (B_low) << endl;

	// 3 calls made to numbers approximately half the size
	OmegaInt z0 = A_low._karatsuba( B_low );
	OmegaInt z1 = ( A_low + A_high )._karatsuba( B_low + B_high );
	OmegaInt z2 = A_high._karatsuba( B_high );

	// cout << z2 << '\t' << (z2._e10(m2 * 2) ) << endl;
	// cout << z1 << '\t' << z1 - z2 - z0 << '\t' << ( (z1 - z2 - z0)._e10(m2) ) << endl;
	// cout << z0 << endl;

	OmegaInt RESULT = (z2._e10(m2 * 2));
	// cout << RESULT << endl;
	RESULT += ( (z1 - z2 - z0)._e10(m2) );
	// cout << RESULT << endl;
	RESULT += z0;
	// cout << RESULT << endl;
	// return RESULT;
	return (z2._e10(m2 * 2) ) + ( (z1 - z2 - z0)._e10(m2) ) + z0;
}

OmegaInt OmegaInt::operator * (OmegaInt const & other) const
{
	OmegaInt RESULT;
	const OmegaInt& A = *this;
	const OmegaInt& B = other;

	RESULT = A._karatsuba(B);
	if ( this->sing() != other.sing() ){ RESULT.changeSing(); }
	return RESULT;
};

u64 OmegaInt::_countTailZeros() const
{
	string A = this->toString();
	u64 i = 0;
	while( A[A.size()-i-1] == '0' ){ i++; }
	return i;
}

OmegaInt OmegaInt::_removeTailZeros() const
{
	string A = this->toString();
	while( A[A.size()-1] == '0' ){ A = A.substr(0, A.size() - 1); }
	return OmegaInt(A);
}

OmegaInt OmegaInt::_longDiv(OmegaInt const & other, DivReturn ret) const
{
	OmegaInt N = *this;
	OmegaInt D = other;

	u64 tenMultiples = std::min( N._countTailZeros(), D._countTailZeros() );
	if (tenMultiples > 0)
		{ N = N.RemovefromBack( tenMultiples ); D = D.RemovefromBack( tenMultiples ); }

	OmegaInt Q = 0, R = 0;

	if (D == 0){ std::cout << "WARNING: Divition by Zero" << std::endl; return OmegaInt(); }

	u64 total = N._numBits() - 1;

	for (long i = total; i >= 0; --i)
	{
		R = R << 1;
		// R = R * 2;
		R = (R[0] % 2 == 0 and N._checkBit(i) == 0)? R :
			(R[0] % 2 == 1 and N._checkBit(i) == 0)? R - 1 :
			(R[0] % 2 == 0 and N._checkBit(i) == 1)? R + 1 :
		  /*(R[0] % 2 == 1 and N._checkBit(i) == 1)?*/R;
		// bug();

		if (R >= D)
		{
			R -= D;
			Q._setBit(i);
		}
		cout << Q << ' ' << R << endl;
	}

	if (ret == Quotient) { return Q; }
	else				 { return R._e10(tenMultiples); }
}

OmegaInt OmegaInt::operator / (OmegaInt const & other) const
{
	OmegaInt RESULT;
	const OmegaInt& A = *this;
	const OmegaInt& B = other;
	DivReturn ret = Quotient;

	RESULT = A._longDiv(B, ret);
	if ( this->sing() != other.sing() ){ RESULT.changeSing(); }
	return RESULT;
};

OmegaInt OmegaInt::operator % (OmegaInt const & other) const
{
	OmegaInt RESULT;
	const OmegaInt& A = *this;
	const OmegaInt& B = other;
	DivReturn ret = Reminder;

	RESULT = A._longDiv(B, ret);
	return RESULT;
};

// Abbreviated Operators
void OmegaInt::operator += (OmegaInt const & other)
	{ *this = *this + other; }

void OmegaInt::operator -= (OmegaInt const & other)
	{ *this = *this - other; }

void OmegaInt::operator ++ () { *this += (OmegaInt(1)); }

void OmegaInt::operator -- () { *this -= (OmegaInt(1)); }

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
	cout << std::boolalpha << "isPOSITIVE: " << isPOSITIVE << endl;
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

void OmegaInt::_reSize(u64 newSize)
{
	if (newSize <= 0){ return; }
	// Make new Container
	u64* temp = (u64*) realloc( NUMBERS, sizeof(u64) * newSize );
	if (temp != NULL) { NUMBERS = temp; }
	else{ free (NUMBERS); puts ("Error (re)allocating memory"); exit (1); }
};

void OmegaInt::_maintenance()
{
	// Verify that everything is under MAXFIELDVALUE
	for (unsigned i = 0; i < TOTALFIELDS; ++i)
	{
		if ( NUMBERS[i] >= MAXFIELDVALUE )
		{
			NUMBERS[i] -= MAXFIELDVALUE;
			
			if( i + 1 < TOTALFIELDS )
			{
				NUMBERS[i+1]++;
			}
			else
			{
				this->_reSize( TOTALFIELDS+1 );
				// Add the carry
				NUMBERS[TOTALFIELDS]++;
				// Increase size of container
				TOTALFIELDS++;
			}
		}
	}

	// Verify that there are no leading zero fields
	bool isZero = NUMBERS[TOTALFIELDS - 1] == 0;
	unsigned i = 0, fieldsErasable = 0;
	while ( i < TOTALFIELDS - 1 and isZero )
	{
		isZero = NUMBERS[TOTALFIELDS - i - 1] == 0;
		fieldsErasable += isZero? 1 : 0;
		++i;
	}

	// if (fieldsErasable == TOTALFIELDS){ fieldsErasable--; }

	if (fieldsErasable > 0)
	{
		// Change the size of the container
		TOTALFIELDS -= fieldsErasable;
		// Resize to fit
		this->_reSize( TOTALFIELDS );
	}

	// Ensure that the zero is represented has positive
	if (TOTALFIELDS == 1 and NUMBERS[0] == 0){ isPOSITIVE = true; }
};


OmegaInt OmegaInt::eraseHeadDigits(u64 n) const
{
	string A = this->toString();
	A = A.substr(n, A.size());
	return OmegaInt(A);
}

OmegaInt OmegaInt::eraseTailDigits(u64 n) const
{
	string A = this->toString();
	A = A.substr(0, A.size() - n);
	return OmegaInt(A);
}

OmegaInt OmegaInt::prepend(u64 n) const
{
	string A = this->toString();
	A = A.substr(n, A.size());
	return OmegaInt(A);
}

OmegaInt OmegaInt::append(u64 n) const
{
	string A = this->toString();
	A = A.substr(0, A.size() - n);
	return OmegaInt(A);
}

void OmegaInt::_setBit(u64 n)
{
	u64 index = n / MAXBIT;
	n = (n % MAXBIT);
	NUMBERS[index] = NUMBERS[index] | (1ULL << n);
	_maintenance();
}

void OmegaInt::_clearBit(u64 n)
{
	u64 index = n / MAXBIT;
	n = (n % MAXBIT);
	NUMBERS[index] = NUMBERS[index] & ~(1ULL << n);
	_maintenance();
}

void OmegaInt::_flipBit(u64 n)
{
	u64 index = n / MAXBIT;
	n = (n % MAXBIT);
	NUMBERS[index] = NUMBERS[index] ^ 1ULL << n;
	_maintenance();
}

unsigned OmegaInt::_checkBit(u64 n)
{
	OmegaInt A = *this;
	// u64 index = n / MAXBIT;
	// n = (n % MAXBIT);
	// return (NUMBERS[index] >> n) & 1U;
	for (u64 i = 0; i < n; ++i)
	{
		for (u64 j = 0; j < A.TOTALFIELDS; ++j)
		{
			A.NUMBERS[j] /= 2;
		}
		A._maintenance();
	}

	return A.NUMBERS[0] % 2;
}

void OmegaInt::_changeBit(u64 n, unsigned x)
{
	u64 index = n / MAXBIT;
	n = (n % MAXBIT);
	NUMBERS[index] = (NUMBERS[index] & ~(1ULL << n)) | (x << n);
	_maintenance();
}

u64 OmegaInt::_numBits()
{
	u64 i = 0;
	u64 A = NUMBERS[TOTALFIELDS - 1];
	while(A > 0)
	{
		A = A >> 1;
		i++;
	}

	return i + (MAXBIT * (TOTALFIELDS - 1));
}

OmegaInt OmegaInt::operator << (u64 n)
{
	OmegaInt RESULT = *this;

	for (u64 i = 0; i < n; ++i)
	{
		for (u64 j = 0; j < TOTALFIELDS; ++j)
		{
			RESULT.NUMBERS[j] = RESULT.NUMBERS[j] * 2;
		}

		RESULT._maintenance();
	}

	return RESULT;
}