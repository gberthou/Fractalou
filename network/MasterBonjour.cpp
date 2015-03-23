#include "MasterBonjour.h"
#include <iostream>

MasterBonjour::MasterBonjour(const unsigned short& a_port) :
{
	if (bjr.bind(a_port) != sf::Socket::Done)
	{
		std::cerr << "Failed to initialize bonjour as master." << std::endl;
		return;
	}
	port = a_port;
}

MasterBonjour::~MasterBonjour() {
	
}

void MasterBonjour::Run()
{
	sf::Thread thread(&MasterBonjour::authentificationRoutine);
	thread.launch();
}

void MasterBonjour::authentificationRoutine()
{
	sf::IpAddress sender;
	while(1)
	{
		if (bjr.receive(data, BUFFER_SIZE, received, sender, port) != sf::Socket::Done)
		{
			std::cerr << "Failed to recognize bonjour request." << std::endl;
		} else if (bjr.send(data, BUFFER_SIZE, sender, port) != sf::Socket::Done)
		{
			std::cerr << "Failed to answer bonjour to " << sender << "on port " << port << std::endl;
		} else
		{
			std::cout << "Bonjour process done with " << sender << "on port " << port << std::endl;
		}
	}
}