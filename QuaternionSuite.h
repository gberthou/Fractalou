#ifndef QUATERNION_SUITE_H
#define QUATERNION_SUITE_H

#include <SFML/System.hpp>

#include "Quaternion.h"

class QuaternionSuite
{
	public:
		QuaternionSuite(sf::Uint32 id, const Quaternion &z0, const Quaternion &c);
		virtual ~QuaternionSuite() = 0;
		
		sf::Uint32 GetIterationNumber(sf::Uint32 iterationsMax, double limit);

	protected:
		virtual Quaternion compute(const Quaternion &z) = 0;
		
		Quaternion z0;
		Quaternion c;

	private:
		sf::Uint32 id;
};

#endif

