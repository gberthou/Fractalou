#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "ApplicationMaster.h"
#include "Fractal.h"
#include "Bonjour.h"

ApplicationMaster::ApplicationMaster():
	fractal(0),
	bonjour(0),
	socket(0)
{
}

ApplicationMaster::~ApplicationMaster()
{
	if(fractal != 0)
		delete fractal;
	if(bonjour != 0)
		delete bonjour;
	if(socket != 0)
		delete socket;
}

bool ApplicationMaster::Run(bool blocking)
{
	socket = new MasterSocket(this, fractal);
	if(!socket->Initialize())
		return false;

	bonjour = new MasterBonjour(this, BONJOUR_ASK_PORT, socket->GetListenerPort());
	if(!bonjour->Initialize())
		return false;

	bonjour->Run();
	socket->Run();

	if(blocking)
	{
		bonjour->WaitForEnd();
		socket->WaitForEnd();
	}

	return true;
}

void ApplicationMaster::WaitForEnd(void)
{
	if(bonjour != 0)
		bonjour->WaitForEnd();
	if(socket != 0)
		socket->WaitForEnd();
}

