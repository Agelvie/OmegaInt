#include "OmegaUtils.hpp"

namespace OmegaUtils
{
	void swap( OmegaInt &A, OmegaInt &B )
	{
		OmegaInt X(A);
		A = B;
		B = X;
	}
}
