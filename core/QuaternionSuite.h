#ifndef QUATERNION_SUITE_H
#define QUATERNION_SUITE_H

#include <SFML/System.hpp>

#include "Quaternion.h"

class QuaternionSuite
{
	public:
		QuaternionSuite(sf::Uint32 id, const Quaternion &z0);
		virtual ~QuaternionSuite();
		
		sf::Uint32 ComputeIterationNumber(sf::Uint32 iterationsMax, double limit) const;
		sf::Uint32 GetId(void) const;

	protected:
		virtual Quaternion compute(const Quaternion &z) const = 0;
		
		Quaternion z0;

	private:
		sf::Uint32 id;
};

#endif

