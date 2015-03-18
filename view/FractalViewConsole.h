#ifndef FRACTALVIEW_CONSOLE_H
#define FRACTALVIEW_CONSOLE_H

#include "FractalView.h"

class FractalViewConsole : public FractalView
{
	public:
		FractalViewConsole(Fractal *fractal, unsigned int width, unsigned int height);
		virtual ~FractalViewConsole();

		virtual void Display(void) const;

	protected:
		unsigned int width;
		unsigned int height;
};

#endif

