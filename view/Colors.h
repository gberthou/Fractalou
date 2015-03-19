#ifndef COLORS_H_INCLUDED
#define COLORS_H_INCLUDED

#include <SFML/System.hpp>

class Colors 
{
    public:
        static void HsvToRgb(sf::Uint8 *r, sf::Uint8 *g, sf::Uint8 *b, sf::Uint8 h, sf::Uint8 s, sf::Uint8 v);
    
        Colors();
        virtual ~Colors();
        static void GetColor(double nbIteration, sf::Uint8 *r, sf::Uint8 *g, sf::Uint8 *b);
        
    protected:
};


#endif // COLORS_H_INCLUDED
