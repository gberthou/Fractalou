#ifndef QUATERNION_SUITE_H
#define QUATERNION_SUITE_H

#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include "Quaternion.h"

class QuaternionSuite
{
	public:
		QuaternionSuite();
		QuaternionSuite(sf::Uint32 id, const Quaternion &z0, sf::Uint32 iterationsMax, double limit);
		virtual ~QuaternionSuite();
		
		sf::Uint32 ComputeIterationNumber(void) const;
		sf::Uint32 GetId(void) const;
		sf::Uint32 GetIterationsMax(void) const;

		virtual void Serialize(sf::Packet&) = 0;
		virtual void DeSerialize(sf::Packet&) = 0;

	protected:
		virtual Quaternion compute(const Quaternion &z) const = 0;
		
		Quaternion z0;
		sf::Uint32 iterationsMax;
		double limit;
		sf::Uint32 id;
};

#endif

