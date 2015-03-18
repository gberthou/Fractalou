#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Fractal.h"
#include "fractals/QS_Julia.h"
#include "FractalViewConsole.h"

#include "network/MasterSocket.h"

//#define WINDOW

void testJuliaLocal(void)
{
	const unsigned int W = 80;
	const unsigned int H = 42;

	const Quaternion C(-0.835, -0.232, 0, 0);

	sf::Uint32 id = 0;
	SuiteCollection suites;
	Fractal fractal;
	FractalViewConsole view(&fractal, W, H);

	for(unsigned int x = 0; x < W; ++x)
	{
		for(unsigned int y = 0; y < H; ++y)
		{
			Quaternion z0((x-W/2.)/100., (y-H/2.)/100., 0, 0);
			suites.push_back(new QS_Julia(id++, z0, C, 100., 100.));
		}
	}

	fractal.CreatePart(suites);
	fractal.ComputeResults();
	view.Display();
}

int main(void)
{

    #ifndef  WINDOW

	std::cout << "Fractals. Here." << std::endl;
	
	testJuliaLocal();
	MasterSocket ms(54000);
	ms.AuthentificationRoutine();

	#else

    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();

	sf::RenderWindow window(modes[0], "Fractalou", sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(true);
    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {


        sf::Event event;
        while (window.pollEvent(event))
        {
            switch( event.type )
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseMoved:
            {
                window.clear();
                sf::CircleShape shape(10);
                shape.setPosition( event.mouseMove.x, event.mouseMove.y );
                shape.setFillColor(sf::Color::Green);
                window.draw(shape);
                break;
            }
            default:
                break;
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //window.draw(shape);
        window.display();
    }

    #endif

	return 0;
}

