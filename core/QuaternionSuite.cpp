#include "QuaternionSuite.h"

QuaternionSuite::QuaternionSuite(sf::Uint32 aid, const Quaternion &az0):
	z0(az0),
	id(aid)
{
}

QuaternionSuite::~QuaternionSuite()
{
}
	
sf::Uint32 QuaternionSuite::ComputeIterationNumber(sf::Uint32 iterationsMax, double limit) const
{
	sf::Uint32 iterations;
	Quaternion z = z0;
	
	for(iterations = 0; iterations < iterationsMax && z.Length2() < limit; ++iterations)
		z = compute(z);

	return iterations;
}

sf::Uint32 QuaternionSuite::GetId(void) const
{
	return id;
}

