#include "FractalView.h"

FractalView::FractalView(Fractal *afractal):
	fractal(afractal)
{
}

FractalView::~FractalView()
{
	if(fractal != 0)
		delete fractal;
}

