#include "ApplicationSlave.h"
#include "Bonjour.h"

ApplicationSlave::ApplicationSlave():
	bonjour(0),
	socket(0)
{
}

ApplicationSlave::~ApplicationSlave()
{
	if(bonjour != 0)
		delete bonjour;
	if(socket != 0)
		delete socket;
}

bool ApplicationSlave::Run(void)
{
	const sf::Time BONJOUR_SLEEP_TIME = sf::seconds(2);
	bonjour = new SlaveBonjour(BONJOUR_PORT, BONJOUR_SLEEP_TIME);
	if(!bonjour->Initialize())
		return false;

	bonjour->Run();

	return true;
}

