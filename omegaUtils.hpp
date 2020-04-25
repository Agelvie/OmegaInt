#include "24Karat.hpp"

#pragma once

namespace OmegaUtils
{
	void swap( OmegaInt &A, OmegaInt &B );
	OmegaInt& min( OmegaInt &A, OmegaInt &B );
	OmegaInt& max( OmegaInt &A, OmegaInt &B );
	template < typename T, typename G > OmegaInt GCD ( T A, G B );
	template < typename T, typename G > OmegaInt lcm ( T A, G B );
}

template <typename T, typename G>
OmegaInt OmegaUtils::GCD( T arg0, G arg1 )
{
	OmegaInt A(arg0);
	OmegaInt B(arg1);
	OmegaInt C(0);

	if ( A < B ) { OmegaUtils::swap(A,B); }
	
	while (B != 0)
	{
		C = A % B;
		A = B;
		B = C;
	}

	return A;
}

template <typename T, typename G>
OmegaInt OmegaUtils::lcm( T arg0, G arg1 )
{
	OmegaInt A(arg0);
	OmegaInt B(arg1);

	if ( A == 0 or B == 0 ) { return 0; }
	if ( A < B ) { OmegaUtils::swap(A,B); }
	
	return (A * B) / OmegaUtils::GCD( A, B );
}