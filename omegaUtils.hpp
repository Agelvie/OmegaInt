#include "24Karat.hpp"

#pragma once

namespace OmegaUtils
{
	template < typename T, typename G > OmegaInt GCD ( T A, G B );
}

template <typename T, typename G>
OmegaInt OmegaUtils::GCD( T arg0, G arg1 )
{
	OmegaInt A(arg0);
	OmegaInt B(arg1);

	if ( B == 0 ) 	   { return A; }
	else if ( A < B )  { return OmegaUtils::GCD( B, A ); }
	else			   { return OmegaUtils::GCD( B, A % B ); }
}