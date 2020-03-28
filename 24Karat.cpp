#include "24Karat.hpp"
	//@TODO -- check that every field has less digits than MAXDIGITS


megaInt::megaInt(){};

megaInt::megaInt(std::string num)
{
	long i = 0, j;
	// cout << MAXDIGITS << endl;

	// calculate the number of fields required to hold that number
	TOTALFIELDS = num.size() / MAXDIGITS;
	if (num.size() % MAXDIGITS != 0){ TOTALFIELDS++; }
	// the divition was not exact and there is the need for another field
	// cout << TOTALFIELDS << endl;

	NUMBERS = (u64*) calloc( TOTALFIELDS, sizeof(u64) );

	// check for a negative sing
	if ( num.find('-') == string::npos ) { POSITIVE = true; }
	else { POSITIVE = false; }

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

megaInt::megaInt(u64 fields, bool pos)
{
	// calculate the number of fields required to hold that number
	TOTALFIELDS = fields;

	NUMBERS = (u64*) calloc( TOTALFIELDS, sizeof(u64) );

	POSITIVE = pos;
};

megaInt::megaInt(u64 fields, u64* nums, bool pos)
{
	// calculate the number of fields required to hold that number
	TOTALFIELDS = fields;

	NUMBERS = (u64*) calloc( TOTALFIELDS, sizeof(u64) );

	POSITIVE = pos;

	for (int i = 0; i < fields; ++i)
	{
		NUMBERS[i] = nums[i];
	}
};

megaInt::~megaInt(){ free(NUMBERS); NUMBERS = nullptr; };

void print()
{
	for (int i = 0; i < TOTALFIELDS; ++i)
	{
		cout << NUMBERS[i] << endl;
	}
	for (int i = 0; i < TOTALFIELDS; ++i)
	{
		cout << NUMBERS[TOTALFIELDS - i - 1];
	}
	cout << endl;

	for (int i = TOTALFIELDS - 1; i >= 0; --i)
	{
		cout << NUMBERS[i];
	}
	cout << endl;
}

long fields(){ return TOTALFIELDS; }
bool sing(){ return POSITIVE; }
u64 operator [] (long i){ return NUMBERS[i]; }


megaInt megaInt::operator + (megaInt const & other) const
{
	long top;
	bool sing;

	// Determine size and sing resulting from the operation
	top = this->fields() > other.fields() ? this->fields() : top = other.fields();
	sing = this->fields() > other.fields()? this.sing() :
		   this->fields() < other.fields()? other.fields() :
		   this->fields() == other.fields()? other[fields() -1] > (*this)[fields() -1] ? other.fields() : this.sing() ;
	
	megaInt* RESULT = new megaInt(top,sing);

	for (long i = 0; i < top; ++i)
	{
		RESULT[i] = this.sing() == other.sing() ? (*this)[i] + other[i] : (*this)[i] - other[i];
	}

	return RESULT;
}


std::ostream& operator<<(std::ostream & os, const Game & A)
{
	os << POSITIVE? : '' : '-';
	for (unsigned i = TOTALFIELDS - 1; i >= 0; --i)
	{
		os << NUMBERS[i];
	}
	
	return os;
}
