#include "QS_Julia.h"

QS_Julia::QS_Julia(sf::Uint32 aid, const Quaternion &az0, const Quaternion &ac, sf::Uint32 itMax, double alimit):
	QuaternionSuite(aid, az0, itMax, alimit),
	c(ac)
{
}

QS_Julia::~QS_Julia()
{
}

Quaternion QS_Julia::compute(const Quaternion &z) const
{
	return z * z + c;
}

