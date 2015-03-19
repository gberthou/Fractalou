#ifndef FRACTALVIEWWINDOW_H
#define FRACTALVIEWWINDOW_H

#include "FractalView.h"
#include <SFML/Graphics.hpp>

class FractalViewWindow : public FractalView
{
    public:
        FractalViewWindow(Fractal* fractal, sf::RenderWindow* window, unsigned int width = 800, unsigned int height = 600 );
        virtual ~FractalViewWindow();

        virtual void Display(void) const;
        
		bool Initialize(void);
		void BuildImage(void);
   
   	protected:
        sf::RenderWindow* window;
        unsigned int width;
        unsigned int height;
        sf::Sprite sprite;
        sf::Texture texture;
};

#endif // FRACTALVIEWWINDOW_H
