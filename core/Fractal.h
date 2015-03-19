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

		void CreatePart(const SuiteCollection &suites);
		
		// ComputeResults: Used by the slave
		void ComputeResults(void);
		
		void BuildResult(ResultCollection &result) const;

		FractalPartCollection GetParts(void) const;

	private:
		FractalPartCollection parts;
};

#endif

