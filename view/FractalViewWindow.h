#ifndef FRACTALVIEWWINDOW_H
#define FRACTALVIEWWINDOW_H

#include "FractalView.h"
#include <SFML/Graphics.hpp>

class FractalViewWindow : public FractalView
{
    public:
        FractalViewWindow(const Fractal* fractal, sf::RenderWindow* window, unsigned int width = 800, unsigned int height = 600 );
        virtual ~FractalViewWindow();

        virtual void Display(void) const;
        
        bool Initialize(void);
        void BuildImage(void);
		void UpdatePart(const ResultCollection &results);
   
    protected:
        sf::RenderWindow* window;
        unsigned int width;
        unsigned int height;
        sf::Sprite sprite;
        sf::Texture texture;
		sf::Uint8 *pixels;
};

#endif // FRACTALVIEWWINDOW_H
