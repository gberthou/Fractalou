#ifndef FRACTALVIEW_CONSOLE_H
#define FRACTALVIEW_CONSOLE_H

#include "FractalView.h"

class FractalViewConsole : public FractalView
{
	public:
		FractalViewConsole(const Fractal *fractal, unsigned int width, unsigned int height);
		virtual ~FractalViewConsole();

		virtual void Display(void) const;

	protected:
		// Returns the "ascii-art" character corresponding to the given iteration ratio
		static char GetCharacter(double ratio);

		unsigned int width;
		unsigned int height;
};

#endif

