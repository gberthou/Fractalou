#include "QuaternionSuite.h"

QuaternionSuite::QuaternionSuite(sf::Uint32 aid, const Quaternion &az0):
	z0(az0),
	id(aid),
	iterationNumber(0)
{
}
	
void QuaternionSuite::SetIterationNumber(sf::Uint32 value)
{
	iterationNumber = value;
}

sf::Uint32 QuaternionSuite::GetIterationNumber(void) const
{
	return iterationNumber;
}

sf::Uint32 QuaternionSuite::ComputeIterationNumber(sf::Uint32 iterationsMax, double limit)
{
	sf::Uint32 iterations;
	Quaternion z = z0;
	
	for(iterations = 0; iterations < iterationsMax && z.Length2() < limit; ++iterations)
		z = compute(z);

	return iterations;
}

