#include "FractalViewWindow.h"
#include <math.h>
#include <iostream>

FractalViewWindow::FractalViewWindow(Fractal *fractal, sf::RenderWindow*, unsigned int w, unsigned int h)
    : FractalView(fractal), width(w), height(h)
{
    //ctor
}

FractalViewWindow::~FractalViewWindow()
{
    //dtor
}

void FractalViewWindow::Display(void) const
{

        //window->draw(sprite);
}

void FractalViewWindow::Perform(void)
{
    ResultCollection result;
	ResultCollection::const_iterator it;

	fractal->BuildResult(result);

	std::cout << "There are " << result.size() << " results." << std::endl;

	if (!texture.create(width, height))
    {
        return;
    }

    sf::Uint8* pixels = new sf::Uint8[width * height * 4];

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
	texture.setSmooth(true);
	delete[] pixels;
	sprite.setTexture(texture);
}

sf::Sprite* FractalViewWindow::getSprite()
{
    return &sprite;
}
