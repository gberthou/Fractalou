#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Fractal.h"
#include "QS_Julia.h"
#include "FractalViewConsole.h"
#include "FractalViewWindow.h"
#include "MasterSocket.h"
#include "SlaveSocket.h"

#define WINDOW
#define WINDOW_W 1280
#define WINDOW_H 720

FractalViewWindow* testJuliaLocalWindowed(sf::RenderWindow* window, double zoom)
{
    const unsigned int W = WINDOW_W;
	const unsigned int H = 720;

	//const Quaternion C(-0.835, 0.232, 0, 0);
	const Quaternion C(-0.756, 0.232, 0, 0); // fractus
	//const Quaternion C(-0.756, 0.156, 0, 0); // fractus pas beau
	//const Quaternion C(-0.756, 0.356, 0, 0); // rose
	//const Quaternion C(0.42, 0.42, 0, 0); // stars
	//const Quaternion C(0.005, 0.852, 0, 0); // lightning

	sf::Uint32 id = 0;
	SuiteCollection suites;
	Fractal fractal;
	FractalViewWindow* view = new FractalViewWindow(&fractal, window, W, H);
	if(!view->Initialize()) // Unable to create the texture
	{
		return 0;
	}

    for(unsigned int y = 0; y < H; ++y)
	{
        for(unsigned int x = 0; x < W; ++x)
		{
			//Quaternion z0((x-W/2.)/300., (y-H/2.)/300., 0, 0);
			Quaternion z0((x-W/2.-0.835)/zoom,(y-H/2.+0.232)/zoom, 0, 0);
			//Quaternion z0((x-W/2.)/(100.*zoom), (y+H/2.)/(100.*zoom), 0, 0);
			suites.push_back(new QS_Julia(id++, z0, C, 100., 100.));
		}
	}

	fractal.CreatePart(suites);
	MasterSocket ms(54000, fractal);
	ms.AuthentificationRoutine();

	while(fractal.GetParts()[0]->GetResults().size() == 0) {}

	std::cout << "Building image..." << std::endl;
	view->BuildImage();
	std::cout << "Image built!" << std::endl;

	return view;
}

int main(void)
{

    #ifndef  WINDOW
	MasterSocket ms(54000);

	std::cout << "Fractals. Here." << std::endl;

	testJuliaLocal();
	ms.AuthentificationRoutine();

    //*******For testing purpose*********
    //SlaveSocket ss("localhost", 54000);
    //ss.Run();

	#else

    //std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
	//sf::RenderWindow window(modes[0], "Fractalou", sf::Style::Fullscreen);

	sf::RenderWindow window(sf::VideoMode(WINDOW_W,WINDOW_H), "Fractalou", sf::Style::Default);

	double zoom = 500;
	FractalViewWindow* view = 0;

	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

    view = testJuliaLocalWindowed(&window, zoom);

	view->Display();
	window.display();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch( event.type )
            {
				case sf::Event::KeyPressed:
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					{
						window.close();
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)
							   || sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
					{
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
							zoom*=2.;
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
							zoom/=2.;

						delete view;
						view = testJuliaLocalWindowed(&window, zoom);

						window.clear();
						view->Display();
						window.display();
					}
					break;
				case sf::Event::Closed:
					window.close();
					break;
				default:
					break;
            }
        }
    }

	delete view;

    #endif

	return 0;
}
