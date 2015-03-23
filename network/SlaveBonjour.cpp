#include "SlaveBonjour.h"

#include <iostream>

SlaveBonjour::SlaveBonjour(const unsigned short& a_port, sf:Time a_sleep)
{
	if (bjr.bind(a_port) != sf::Socket::Done)
	{
		std::cerr << "Failed to initialize bonjour as slave." << std::endl;
		return;
	}
	port = a_port;
	sleepTime = a_sleep;
}

SlaveBonjour::~SlaveBonjour()
{
}

void SlaveBonjour::Run()
{
	sf::Thread thread(&SlaveBonjour::authentificationRoutine);
	thread.launch();
}

void SlaveBonjour::authentificationRoutine()
{
	while(1)
	{
		if (bjr.send(data, BUFFER_SIZE, sf::IpAddress::Broadcast, port) != sf::Socket::Done)
		{
			std::cerr << "Failed to send bonjour request." << std::endl;
		} else 
		{
			std::cout << "Bonjour broadcasted on port " << port << std::endl;
		}
		sf::sleep(sleepTime);
	}
}

bool SlaveBonjour::GetMaster(sf::IpAddress &server)
{
		if (bjr.receive(data, BUFFER_SIZE, received, server, port) != sf::Socket::Done)
		{
			std::cerr << "Failed to understand bonjour on port " << port << std::endl;
			return false;
		}
		for (std::vector<sf::IpAddress*>::iterator it = serverss.begin() ; it != servers.end(); ++it)
			if (**it == server) return false;
		servers.push_back(server);
		std::cout << "Bonjour process done with " << server << "on port " << port << std::endl;
		return true;
}