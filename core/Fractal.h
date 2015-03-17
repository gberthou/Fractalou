#ifndef FRACTAL_H
#define FRACTAL_H

#include <vector>

#include "FractalPart.h"

class Fractal
{
	public:
		Fractal();
		virtual ~Fractal();

		void CreatePart(const std::vector<QuaternionSuite *> &suites);

	private:
		std::vector<FractalPart *> parts;
};

#endif

