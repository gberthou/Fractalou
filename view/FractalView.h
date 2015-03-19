#ifndef FRACTALVIEW_H
#define FRACTALVIEW_H

#include "../core/Fractal.h"

class FractalView
{
	public:
		FractalView(const Fractal *fractal);
		virtual ~FractalView();

		virtual void Display(void) const = 0;

	protected:
		const Fractal *fractal;
};

#endif

