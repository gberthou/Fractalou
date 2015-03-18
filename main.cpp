#include <iostream>
#include <vector>

#include "Fractal.h"
#include "fractals/QS_Julia.h"
#include "FractalViewConsole.h"

void testJuliaLocal(void)
{
	const unsigned int W = 80;
	const unsigned int H = 42;

	const Quaternion C(-0.835, -0.232, 0, 0);
	
	sf::Uint32 id = 0;
	SuiteCollection suites;
	Fractal fractal;
	FractalViewConsole view(&fractal, W, H);

	for(unsigned int x = 0; x < W; ++x)
	{
		for(unsigned int y = 0; y < H; ++y)
		{
			Quaternion z0((x-W/2.)/100., (y-H/2.)/100., 0, 0);
			suites.push_back(new QS_Julia(id++, z0, C, 100., 100.));
		}
	}

	fractal.CreatePart(suites);
	fractal.ComputeResults();
	view.Display();
}

int main(void)
{
	std::cout << "Fractals. Here." << std::endl;
	testJuliaLocal();
	return 0;
}

