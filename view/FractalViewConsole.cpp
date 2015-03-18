#include <iostream>

#include "FractalViewConsole.h"

FractalViewConsole::FractalViewConsole(Fractal *f, unsigned int w, unsigned int h):
	FractalView(f),
	width(w),
	height(h)
{
}

FractalViewConsole::~FractalViewConsole()
{
}

void FractalViewConsole::Display(void) const
{
	ResultCollection result;
	fractal->BuildResult(result);

	std::cout << "There are " << result.size() << " results." << std::endl;
}

