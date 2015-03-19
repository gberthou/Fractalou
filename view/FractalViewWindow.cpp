#include "FractalViewWindow.h"
#include <math.h>
#include <iostream>

FractalViewWindow::FractalViewWindow(Fractal *fractal, sf::RenderWindow *win, unsigned int w, unsigned int h):
	FractalView(fractal),
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

    //double min = 5000,max = 0;

	for(unsigned int y = 0; y < height; ++y)
	{
        //std::cout << y+1 << "/" << height << std::endl;
		for(unsigned int x = 0; x < width; ++x)
		{
			sf::Uint32 id = y * width + x;
			it = result.find(id);
			if(it != result.end())
			{
			    double a = it->second;
				pixels[4*id  ] = 255*(sin(18*a-3.14159/2)+1)/2.;
				pixels[4*id+1] = 255*(sin(12*a-3.14159/2)+1)/2.;
				pixels[4*id+2] = 255*(sin(10*a-3.14159/2)+1)/2.;
				pixels[4*id+3] = 255;
				//if(it->second < min) min = it->second;
				//if(it->second > max) max = it->second;
			}
			else
				std::cout << "X";
		}
	}
    std::cout << "fin" << std::endl;
    //std::cout << "min : "<< min << std::endl;
    //std::cout << "max : "<< max << std::endl;

	texture.update(pixels);
	delete[] pixels;
}

