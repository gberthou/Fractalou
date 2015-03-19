#include "FractalViewWindow.h"
#include <math.h>
#include <iostream>

FractalViewWindow::FractalViewWindow(const Fractal *f, sf::RenderWindow *win, unsigned int w, unsigned int h):
	FractalView(f),
	window(win),
	width(w),
	height(h)
{
    //ctor
}

FractalViewWindow::~FractalViewWindow()
{
    //dtor
}

void FractalViewWindow::Display(void) const
{
	window->draw(sprite);
}

bool FractalViewWindow::Initialize(void)
{
	bool res = texture.create(width, height);
	if(res)
	{
		texture.setSmooth(true);
		sprite.setTexture(texture);
	}
	return res;
}

void FractalViewWindow::BuildImage(void)
{
    ResultCollection result;
	ResultCollection::const_iterator it;
    
	sf::Uint8* pixels = new sf::Uint8[width * height * 4];

	fractal->BuildResult(result);

	std::cout << "There are " << result.size() << " results." << std::endl;

	for(it = result.begin(); it != result.end(); ++it)
	{
		sf::Uint32 id = it->first;
		double a = it->second;
		
		pixels[4*id  ] = 255*(sin(18*a-3.14159/2)+1)/2.;
		pixels[4*id+1] = 255*(sin(12*a-3.14159/2)+1)/2.;
		pixels[4*id+2] = 255*(sin(10*a-3.14159/2)+1)/2.;
		pixels[4*id+3] = 255;
	}

    std::cout << "done" << std::endl;

	texture.update(pixels);
	delete[] pixels;
}

