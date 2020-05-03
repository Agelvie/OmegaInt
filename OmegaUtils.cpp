#include "OmegaUtils.hpp"



namespace OmegaUtils
{
	void swap( OmegaInt &A, OmegaInt &B )
	{
		OmegaInt X(A);
		A = B;
		B = X;
	}

	OmegaInt& min( OmegaInt &A, OmegaInt &B )
		{ return A < B ? A : B; }

	OmegaInt& max( OmegaInt &A, OmegaInt &B )
		{ return A > B ? A : B; }
}
