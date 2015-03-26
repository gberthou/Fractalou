#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "ApplicationMaster.h"
#include "Fractal.h"
#include "Bonjour.h"

ApplicationMaster::ApplicationMaster():
	bonjour(0),
	socket(0)
{
}

ApplicationMaster::~ApplicationMaster()
{
	if(bonjour != 0)
		delete bonjour;
	if(socket != 0)
		delete socket;
}

bool ApplicationMaster::Run(void)
{
	socket = new MasterSocket(this, fractal);
	if(!socket->Initialize())
		return false;

	bonjour = new MasterBonjour(this, BONJOUR_ASK_PORT, socket->GetListenerPort());
	if(!bonjour->Initialize())
		return false;

	bonjour->Run();
	socket->Run();

	bonjour->WaitForEnd();
	socket->WaitForEnd();

	return true;
}

void ApplicationMaster::setFractal(Fractal *f)
{
	fractal = f;
}

