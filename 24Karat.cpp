#include "24Karat.hpp"
	//@TODO -- check that every field has less digits than MAXDIGITS
	//@TODO -- if top fields are only zeros -> erase
	//@TODO -- allocate new memory if final field is aproaching it's limit

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
	// cout << MAXDIGITS << endl;

	// calculate the number of fields required to hold that number
	TOTALFIELDS = num.size() / MAXDIGITS;
	if (num.size() % MAXDIGITS != 0){ TOTALFIELDS++; }
	// the divition was not exact and there is the need for another field
	// cout << TOTALFIELDS << endl;

	// NUMBERS = new u64[TOTALFIELDS] ;
	NUMBERS = (u64*) calloc( TOTALFIELDS, sizeof(u64) );

	// check for a negative sing
	isPOSITIVE = num.find('-') == string::npos;

	j = MAXDIGITS;
	if ( j >= num.size() ){ j = num.size(); }
	// little endian
	while(num.size() > 0)
	{
		NUMBERS[i] = atoll( (num.substr(num.size() - j, num.size())).data() );
		num.erase(num.size() - j, num.size());
		if ( j >= num.size() ){ j = num.size(); }
		i++;
	}
	// cout << "DONE" << endl;
};

	// Number of fields and sing setted all to zero
OmegaInt::OmegaInt(u64 fields, bool pos)
{
	// calculate the number of fields required to hold that number
	TOTALFIELDS = fields;

	NUMBERS = (u64*) calloc( TOTALFIELDS, sizeof(u64) );

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
OmegaInt::OmegaInt const & operator= (OmegaInt const & other)
{
	if (this != &other) { _copy(other); }
    return *this;
};

void OmegaInt::_copy(OmegaInt const & other)
{
	delete[] NUMBERS;

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

// Setter
	// Changes the sing of the OmegaInt
void OmegaInt::changeSing(){ isPOSITIVE = !isPOSITIVE };

// Getter and Setter? Make private?
u64 OmegaInt::operator [] (const unsigned i) const { return NUMBERS[i]; }

// Comparison Operators
friend bool operator == (const OmegaInt &A, const OmegaInt &B)
{
	if (A.sing() != B.sing()){ return false }





};
friend bool operator != (const OmegaInt &A, const OmegaInt &B);
friend bool operator >  (const OmegaInt &A, const OmegaInt &B);
friend bool operator >= (const OmegaInt &A, const OmegaInt &B);
friend bool operator <  (const OmegaInt &A, const OmegaInt &B);
friend bool operator <= (const OmegaInt &A, const OmegaInt &B);



void OmegaInt::print()
{
	for (unsigned i = 0; i < TOTALFIELDS; ++i)
	{
		cout << NUMBERS[i] << endl;
	}
	for (unsigned i = 0; i < TOTALFIELDS; ++i)
	{
		cout << NUMBERS[TOTALFIELDS - i - 1];
	}
	cout << endl;

	for (unsigned i = TOTALFIELDS - 1; i >= 0; --i)
	{
		cout << NUMBERS[i];
	}
	cout << endl;
}



OmegaInt OmegaInt::operator + (OmegaInt const & other) const
{
	long top;
	bool sing;
	OmegaInt* RESULT = new OmegaInt(top,sing);

	// Determine size and sing resulting from the operation
	top = this->fields() > other.fields() ? this->fields() : top = other.fields();

	sing = this->fields() >  other.fields() ? this->sing()   :
		   this->fields() <  other.fields() ? other.fields() :
		   this->fields() == other.fields() ? other[other.fields() -1] > (*this)[fields() -1] ? other.fields() : this -> sing();


	for (long i = 0; i < top; ++i)
	{
		RESULT[i] = this.sing() == other.sing() ? (*this)[i] + other[i] : (*this)[i] - other[i];
	}

	return RESULT;
}


std::ostream& OmegaInt::operator<<(std::ostream & os, const Game & A)
{
	os << isPOSITIVE? : '' : '-';
	for (unsigned i = TOTALFIELDS - 1; i >= 0; --i)
	{
		os << NUMBERS[i];
	}
	
	return os;
}


/*

	// Arithmetic Operators
	OmegaInt operator + (OmegaInt const & other) const;
	OmegaInt operator - (OmegaInt const & other) const;
	OmegaInt operator * (OmegaInt const & other) const;
	OmegaInt operator / (OmegaInt const & other) const;

	// Output Methods
	void print();
	friend std::ostream& operator<<(std::ostream & os, const OmegaInt & A);*/