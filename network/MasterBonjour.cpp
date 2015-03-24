#include "MasterBonjour.h"
#include <iostream>

MasterBonjour::MasterBonjour(unsigned short aport):
	port(aport)
{
}

MasterBonjour::~MasterBonjour()
{	
}

bool MasterBonjour::Initialize(void)
{
	if (bjr.bind(port) != sf::Socket::Done)
	{
		std::cerr << "Failed to initialize bonjour as master." << std::endl;
		return false;
	}
	return true;
}

void MasterBonjour::Run()
{
	sf::Thread thread(&MasterBonjour::authentificationRoutine, this);
	thread.launch();
}

void MasterBonjour::authentificationRoutine(MasterBonjour *socket)
{
	sf::Packet packet;
	sf::IpAddress sender;

	while(1)
	{
		if (socket->bjr.receive(packet, sender, socket->port) != sf::Socket::Done)
		{
			std::cerr << "Failed to recognize bonjour request." << std::endl;
		}
		else if (socket->bjr.send(packet, sender, socket->port) != sf::Socket::Done)
		{
			std::cerr << "Failed to answer bonjour to " << sender << "on port " << socket->port << std::endl;
		}
		else
		{
			std::cout << "Bonjour process done with " << sender << "on port " << socket->port << std::endl;
		}
	}
}

