#include <sstream>

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
			Quaternion z0 = Quaternion(x-WINDOW_W/2.,y-WINDOW_H/2., 0, 0) * (1. / context->zoom)  - context->center;
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
	view(0), hud(true)
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

	if(!font.loadFromFile("font/DejaVuSans.ttf"))
		return false;

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
							   || sf::Keyboard::isKeyPressed(sf::Keyboard::S)
							   || sf::Keyboard::isKeyPressed(sf::Keyboard::E)
							   || sf::Keyboard::isKeyPressed(sf::Keyboard::D)
							   || sf::Keyboard::isKeyPressed(sf::Keyboard::R)
							   || sf::Keyboard::isKeyPressed(sf::Keyboard::F))
					{
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
							context.zoom*=2.;
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
							context.zoom/=2.;
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
							context.limit*=2.;
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
							context.limit/=2.;
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
							context.itMax*=2.;
						if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
							context.itMax/=2.;

						replaceFractal(buildJuliaFractal(++fractalId, &context));
					}
					else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
					{
						hud = !hud;
					}
					break;
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::MouseButtonPressed:
					{
						double x, y;
						x = sf::Mouse::getPosition(window).x;
						y = sf::Mouse::getPosition(window).y;

						x = (WINDOW_W/2) - x;
						y = (WINDOW_H/2) - y;

						Quaternion q(x / context.zoom, y / context.zoom, 0., 0.);
						context.center = context.center + q;

						replaceFractal(buildJuliaFractal(++fractalId, &context));
					}
					break;
				default:
					break;
            }
        }

		view->Display();
		if(hud) displayHUD(&context);
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

void ApplicationMasterWindow::displayHUD(const FractalContext *context)
{
	const sf::Vector2f HUD_SIZE(300, 100);
	const sf::Vector2f MARGIN(4, 4);
	const unsigned int LINE_NUM = 4;
	const unsigned int FONT_SIZE = 16;
	const float LINE_SPACE = FONT_SIZE + 8;

	std::ostringstream strCenter;
	std::ostringstream strZoom;
	std::ostringstream strLimit;
	std::ostringstream strIterations;
	
	sf::RectangleShape shape(HUD_SIZE);
	sf::Text txt[LINE_NUM];

	strCenter << "Center: " << context->center.GetX() << (context->center.GetY() >= 0 ? " + " : " - ") << (context->center.GetY() >= 0 ? context->center.GetY() : -context->center.GetY()) << "i";

	strZoom << "Zoom: " << context->zoom;
	strLimit << "Limit: " << context->limit;
	strIterations << "It. max: " << context->itMax;

	shape.setFillColor(sf::Color(0, 0, 0, 128));

	txt[0].setString(sf::String(strCenter.str()));
	txt[1].setString(sf::String(strZoom.str()));
	txt[2].setString(sf::String(strLimit.str()));
	txt[3].setString(sf::String(strIterations.str()));
	
	window.draw(shape);
	for(unsigned int i = 0; i < LINE_NUM; ++i)
	{
		txt[i].setFont(font);
		txt[i].setCharacterSize(FONT_SIZE);
		txt[i].setColor(sf::Color(255, 255, 255, 255));
		txt[i].setPosition(MARGIN + sf::Vector2f(0, i * LINE_SPACE));
		window.draw(txt[i]);
	}

}

