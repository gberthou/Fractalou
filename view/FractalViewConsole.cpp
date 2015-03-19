#include <iostream>

#include "FractalViewConsole.h"

FractalViewConsole::FractalViewConsole(const Fractal *f, unsigned int w, unsigned int h):
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
	ResultCollection::const_iterator it;

	fractal->BuildResult(result);

	std::cout << "There are " << result.size() << " results." << std::endl;
	
	for(unsigned int y = 0; y < height; ++y)
	{
		for(unsigned int x = 0; x < width; ++x)
		{
			sf::Uint32 id = y * width + x;
			it = result.find(id);
			if(it != result.end())
			{
				std::cout << GetCharacter(it->second);
			}
			else
				std::cout << "X";
		}
		std::cout << std::endl;
	}
}

char FractalViewConsole::GetCharacter(double ratio)
{
	if(ratio > 0.8)
		return '8';
	if(ratio > 0.6)
		return '0';
	if(ratio > 0.4)
		return 'o';
	if(ratio > 0.2)
		return '.';
	return ' ';
}

