#ifndef FRACTALPART_H
#define FRACTALPART_H

#include <vector>

#include <SFML/System.hpp>

#include "QuaternionSuite.h"

class FractalPart
{
	public:
		FractalPart();
		FractalPart(const std::vector<QuaternionSuite *> &suites);
		virtual ~FractalPart();

		void AddSuite(QuaternionSuite *suite);

	private:
		std::vector<QuaternionSuite *> suites;
};

#endif

