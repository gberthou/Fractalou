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

		// AddSuite: adds the given suite to the suite collection
		void AddSuite(QuaternionSuite *suite);

		void SetResults(const std::vector<sf::Uint32> &r);

		// BuildResult: adds all the results to the given collection
		void BuildResult(std::vector<sf::Uint32> &result) const;

	private:
		std::vector<QuaternionSuite *> suites;
		std::vector<sf::Uint32> results;
};

#endif

