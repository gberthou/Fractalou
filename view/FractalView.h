#ifndef FRACTALVIEW_H
#define FRACTALVIEW_H

#include "Fractal.h"

class FractalView
{
	public:
		FractalView(Fractal *fractal);
		virtual ~FractalView();

	protected:
		Fractal *fractal;
};

#endif

