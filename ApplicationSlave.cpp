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

bool ApplicationSlave::Run(bool blocking)
{
	const sf::Time BONJOUR_SLEEP_TIME = sf::seconds(2);
	bonjour = new SlaveBonjour(this, BONJOUR_ASK_PORT, BONJOUR_SLEEP_TIME);
	if(!bonjour->Initialize())
		return false;

	bonjour->Run();
	if(blocking)
		WaitForEnd();

	return true;
}

void ApplicationSlave::WaitForEnd(void)
{
	if(bonjour != 0)
		bonjour->WaitForEnd();
}

bool ApplicationSlave::ConnectToMaster(const sf::IpAddress &address, unsigned short port)
{
	socket = new SlaveSocket(address, port);
	if(!socket->Initialize())
		return false;
	socket->Run();
	socket->WaitForEnd();
	return true;
}

