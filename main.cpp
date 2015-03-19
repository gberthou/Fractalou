#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Options.h"
#include "Application.h"
#include "Fractal.h"
#include "QS_Julia.h"
#include "FractalViewConsole.h"
#include "FractalViewWindow.h"
#include "MasterSocket.h"
#include "SlaveSocket.h"

void testJuliaLocal(void)
{
	const unsigned int W = 80;
	const unsigned int H = 42;

	const Quaternion C(-0.835, -0.232, 0, 0);

	sf::Uint32 id = 0;
	SuiteCollection suites;
	Fractal fractal;
	FractalViewConsole view(&fractal, W, H);

	for(unsigned int y = 0; y < H; ++y)
	{
		for(unsigned int x = 0; x < W; ++x)
		{
			Quaternion z0((x-W/2.)/20., (y-H/2.)/20., 0, 0);
			suites.push_back(new QS_Julia(id++, z0, C, 50., 100.));
		}
	}

	fractal.CreatePart(suites);
	fractal.ComputeResults();
	view.Display();
}

int main(int argc, char **argv)
{
	Application *app = Application::GetApplication(argc, argv);
	app->Run();

	return 0;
}

