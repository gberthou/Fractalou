#include <iostream>

#include "SlaveBonjour.h"
#include "Bonjour.h"

SlaveBonjour::SlaveBonjour(unsigned short aport, sf::Time asleep):
	port(aport),
	sleepTime(asleep)
{
}

SlaveBonjour::~SlaveBonjour()
{
}

bool SlaveBonjour::Initialize(void)
{
	/*
	if (bjr.bind(port) != sf::Socket::Done)
	{
		std::cerr << "Failed to initialize bonjour as slave." << std::endl;
		return false;
	}
	*/
	return true;
}

void SlaveBonjour::Run()
{
	sf::Thread thread(&SlaveBonjour::authentificationRoutine, this);
	thread.launch();
}

/*
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
*/

void SlaveBonjour::authentificationRoutine(SlaveBonjour *socket)
{
	sf::Packet bonjourPacket;
	bonjourPacket << BONJOUR_ASK_JOB;

	while(1)
	{
		if (socket->bjr.send(bonjourPacket, sf::IpAddress::Broadcast, socket->port) != sf::Socket::Done)
		{
			std::cerr << "Failed to send bonjour request." << std::endl;
		}
		else 
		{
			std::cout << "Bonjour broadcasted on port " << socket->port << std::endl;
		}

		sf::sleep(socket->sleepTime);
	}
}

