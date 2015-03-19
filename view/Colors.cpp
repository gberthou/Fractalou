#include "Colors.h"
#include <cmath>

/* HSV to RGB conversion */
void Colors::HsvToRgb(sf::Uint8 *r, sf::Uint8 *g, sf::Uint8 *b, sf::Uint8 h, sf::Uint8 s, sf::Uint8 v)
{
    sf::Uint8 region, fpart, p, q, t;
    if(s == 0) { /* grayscale */
        *r = *g = *b = v;
        return;
    }
    
    /* make hue 0-5 */
    region = h / 43;
    /* find remainder part, make it from 0-255 */
    fpart = (h - (region * 43)) * 6;
    
    /* calculate temp vars, doing integer multiplication */
    p = (v * (255 - s)) >> 8;
    q = (v * (255 - ((s * fpart) >> 8))) >> 8;
    t = (v * (255 - ((s * (255 - fpart)) >> 8))) >> 8;
        
    /* assign temp vars based on color cone region */
    switch(region) {
        case 0:
            *r = v; *g = t; *b = p; break;
        case 1:
            *r = q; *g = v; *b = p; break;
        case 2:
            *r = p; *g = v; *b = t; break;
        case 3:
            *r = p; *g = q; *b = v; break;
        case 4:
            *r = t; *g = p; *b = v; break;
        default:
            *r = v; *g = p; *b = q; break;
    }
}

Colors::Colors()
{
}

Colors::~Colors()
{
}

void Colors::GetColor(double nbIteration, sf::Uint8 *r, sf::Uint8 *g, sf::Uint8 *b)
{
    // example
    *r = 255*(sin(18*nbIteration-3.14159/2)+1)/2.;
	*g = 255*(sin(12*nbIteration-3.14159/2)+1)/2.;
	*b = 255*(sin(10*nbIteration-3.14159/2)+1)/2.;
}
