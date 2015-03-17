#ifndef FRACTAL_H
#define FRACTAL_H

#include <vector>

#include <SFML/System.hpp>

#include "FractalPart.h"

typedef std::vector<FractalPart*> FractalPartCollection;

class Fractal
{
	public:
		Fractal();
		virtual ~Fractal();

		void CreatePart(const std::vector<QuaternionSuite *> &suites);
		void BuildResult(std::vector<sf::Uint32> &result) const;

	private:
		FractalPartCollection parts;
};

#endif

