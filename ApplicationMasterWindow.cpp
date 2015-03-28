#include "ApplicationMasterWindow.h"

#include "FractalViewWindow.h"
#include "QS_Julia.h"

const unsigned int WINDOW_W = 1280;
const unsigned int WINDOW_H = 720;

const unsigned int MAX_SUITES_PER_PART = 1000;

static unsigned int getPartNumber(unsigned int width, unsigned int height)
{
	unsigned int x = (width * height);
	if((x % MAX_SUITES_PER_PART) == 0)
		return x / MAX_SUITES_PER_PART;
	return 1 + x / MAX_SUITES_PER_PART;
}

static Fractal *buildJuliaFractal(double zoom)
{
	//const Quaternion C(-0.835, 0.232, 0, 0);
	const Quaternion C(-0.756, 0.232, 0, 0); // fractus
	//const Quaternion C(-0.756, 0.156, 0, 0); // fractus pas beau
	//const Quaternion C(-0.756, 0.356, 0, 0); // rose
	//const Quaternion C(0.42, 0.42, 0, 0); // stars
	//const Quaternion C(0.005, 0.852, 0, 0); // lightning

	unsigned int partNumber = getPartNumber(WINDOW_W, WINDOW_H);
	unsigned int i = 0;
	Fractal *fractal = new Fractal();
	sf::Uint32 id = 0;
	SuiteCollection *subsuites = new SuiteCollection[partNumber];
	
	// Optimization: preallocate the vectors
	for(unsigned int j = 0; j < partNumber; ++j)
		subsuites[j].reserve(MAX_SUITES_PER_PART);

    for(unsigned int y = 0; y < WINDOW_H; ++y)
	{
        for(unsigned int x = 0; x < WINDOW_W; ++x)
		{
			//Quaternion z0((x-W/2.)/300., (y-H/2.)/300., 0, 0);
			Quaternion z0((x-WINDOW_W/2.-0.835)/zoom,(y-WINDOW_H/2.+0.232)/zoom, 0, 0);
			//Quaternion z0((x-W/2.)/(100.*zoom), (y+H/2.)/(100.*zoom), 0, 0);
			subsuites[i++].push_back(new QS_Julia(id++, z0, C, 100., 100.));
			
			if(i >= partNumber)
				i = 0;
		}
	}

	for(unsigned int j = 0; j < partNumber; ++j)
		fractal->CreatePart(subsuites[j]);
	
	delete [] subsuites;
	
	return fractal;
}

static FractalViewWindow *testJuliaLocalWindowed(sf::RenderWindow* window, const Fractal *fractal)
{
	FractalViewWindow* view = new FractalViewWindow(fractal, window, WINDOW_W, WINDOW_H);
	if(!view->Initialize()) // Unable to create the texture
	{
		return 0;
	}
	view->Initialize();

	return view;
}

ApplicationMasterWindow::ApplicationMasterWindow():
	window(sf::VideoMode(WINDOW_W,WINDOW_H), "Fractalou", sf::Style::Default),
	view(0)
{
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
}

ApplicationMasterWindow::~ApplicationMasterWindow()
{
	if(view != 0)
		delete view;
}

bool ApplicationMasterWindow::Run(bool)
{
	double zoom = 500.;
	std::vector<FractalPart*>::const_iterator it;

	fractal = buildJuliaFractal(zoom);
	view = testJuliaLocalWindowed(&window, fractal);

	window.clear();
	view->Display();
	window.display();
	//window.setActive(false);

	if(!ApplicationMaster::Run(false))
		return false;

	while(window.isOpen())
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
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)
							   || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
					{
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
							zoom*=2.;
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
							zoom/=2.;

						FractalViewWindow* oldView = view;
						
						fractal = buildJuliaFractal(zoom);
						view = testJuliaLocalWindowed(&window, fractal);
						delete oldView;

						socket->UpdateJobList(fractal);

						window.clear();
					}
					break;

				case sf::Event::Closed:
					window.close();
					break;
				default:
					break;
            }
        }

		view->Display();
		window.display();

		mtxUpdate.lock();
		if(partsToUpdate.size() != 0)
		{
			for(it = partsToUpdate.begin(); it != partsToUpdate.end(); ++it)
			{
				view->UpdatePart(*it);
			}
			partsToUpdate.clear();
		}		
		mtxUpdate.unlock();
	}

	ApplicationMaster::WaitForEnd();
	
	return true;
}

void ApplicationMasterWindow::OnPartComplete(FractalPart *part)
{
	// Put here some code to be called when the given part is complete

	mtxUpdate.lock();
	partsToUpdate.push_back(part);
	mtxUpdate.unlock();
}

