#ifndef FRACTALPART_H
#define FRACTALPART_H

#include <map>

#include <SFML/System.hpp>

#include "QuaternionSuite.h"

class FractalPart
{
	public:
		FractalPart();
		virtual ~FractalPart();

	private:
		std::map<sf::Uint32, QuaternionSuite *> suites;
};

#endif

