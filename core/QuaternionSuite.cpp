#include "QuaternionSuite.h"

QuaternionSuite::QuaternionSuite(sf::Uint32 aid, const Quaternion &az0, sf::Uint32 itMax, double alimit):
	z0(az0),
	iterationsMax(itMax),
	limit(alimit),
	id(aid)
{
}

QuaternionSuite::~QuaternionSuite()
{
}
	
sf::Uint32 QuaternionSuite::ComputeIterationNumber(void) const
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

sf::Uint32 QuaternionSuite::GetIterationsMax(void) const
{
	return iterationsMax;
}
