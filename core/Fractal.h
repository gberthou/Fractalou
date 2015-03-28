#ifndef FRACTAL_H
#define FRACTAL_H

#include <vector>

#include <SFML/System.hpp>

#include "FractalPart.h"

typedef std::vector<FractalPart*> FractalPartCollection;

class Fractal
{
	public:
		Fractal(sf::Uint32 id);
		virtual ~Fractal();

		void CreatePart(const SuiteCollection &suites);
		
		// ComputeResults: Used by the slave
		void ComputeResults(void);
		
		void BuildResult(ResultCollection &result) const;

		sf::Uint32 GetId(void) const;
		const FractalPartCollection &GetParts(void) const;

	private:
		sf::Uint32 id;
		FractalPartCollection parts;
};

#endif

