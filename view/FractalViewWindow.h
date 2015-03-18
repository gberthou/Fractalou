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
        void Perform(void);
        sf::Sprite* getSprite();
    protected:
        unsigned int width;
        unsigned int height;
        sf::RenderWindow* window;
        sf::Sprite sprite;
        sf::Texture texture;
    private:
};

#endif // FRACTALVIEWWINDOW_H
