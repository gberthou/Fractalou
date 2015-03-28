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

static Fractal *buildJuliaFractal(sf::Uint32 fractalId, const FractalContext *context)
{
	//const Quaternion C(-0.835, 0.232, 0, 0);
	const Quaternion C(-0.756, 0.232, 0, 0); // fractus
	//const Quaternion C(-0.756, 0.156, 0, 0); // fractus pas beau
	//const Quaternion C(-0.756, 0.356, 0, 0); // rose
	//const Quaternion C(0.42, 0.42, 0, 0); // stars
	//const Quaternion C(0.005, 0.852, 0, 0); // lightning

	unsigned int partNumber = getPartNumber(WINDOW_W, WINDOW_H);
	unsigned int i = 0;
	Fractal *fractal = new Fractal(fractalId);
	sf::Uint32 id = 0;
	SuiteCollection *subsuites = new SuiteCollection[partNumber];
	
	// Optimization: preallocate the vectors
	for(unsigned int j = 0; j < partNumber; ++j)
		subsuites[j].reserve(MAX_SUITES_PER_PART);

    for(unsigned int y = 0; y < WINDOW_H; ++y)
	{
        for(unsigned int x = 0; x < WINDOW_W; ++x)
		{
			Quaternion z0 = (Quaternion(x-WINDOW_W/2.,y-WINDOW_H/2., 0, 0) - context->center) * (1. / context->zoom);
			subsuites[i++].push_back(new QS_Julia(id++, z0, C, context->itMax, context->limit));
			
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
	if(fractal != 0)
		delete fractal;
}

bool ApplicationMasterWindow::Run(bool)
{
	FractalContext context = {
		Quaternion(0, 0, 0, 0),
		500.,
		100.,
		100
	};
	std::vector<FractalPart*>::const_iterator it;


	fractal = buildJuliaFractal(fractalId, &context);
	view = testJuliaLocalWindowed(&window, fractal);

	window.clear();
	view->Display();
	window.display();

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
							context.zoom*=2.;
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
							context.zoom/=2.;

						replaceFractal(buildJuliaFractal(++fractalId, &context));
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

void ApplicationMasterWindow::replaceFractal(Fractal *f)
{
	delete view;
	//delete fractal;
	fractal = f;	
	view = testJuliaLocalWindowed(&window, fractal);

	socket->UpdateJobList(fractal);

	window.clear();
}
