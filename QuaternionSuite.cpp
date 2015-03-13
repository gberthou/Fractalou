#include "QuaternionSuite.h"

QuaternionSuite::QuaternionSuite(sf::Uint32 aid, const Quaternion &az0, const Quaternion &ac):
	z0(az0),
	c(ac),
	id(aid)
{
}
	
sf::Uint32 QuaternionSuite::GetIterationNumber(sf::Uint32 iterationsMax, double limit)
{
	sf::Uint32 iterations;
	Quaternion z = z0;
	
	for(iterations = 0; iterations < iterationsMax && z.Length2() < limit; ++iterations)
		z = compute(z) + c;

	return iterations;
}

