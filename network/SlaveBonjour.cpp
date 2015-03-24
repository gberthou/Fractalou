#include <iostream>

#include "SlaveBonjour.h"
#include "Bonjour.h"

SlaveBonjour::SlaveBonjour(unsigned short aport, sf::Time asleep):
	askPort(aport),
	sleepTime(asleep)
{
}

SlaveBonjour::~SlaveBonjour()
{
}

bool SlaveBonjour::Initialize(void)
{
	/*
	if (askSocket.bind(port) != sf::Socket::Done)
	{
		std::cerr << "Failed to initialize bonjour as slave." << std::endl;
		return false;
	}
	*/

	return true;
}

void SlaveBonjour::Run()
{
	sf::Thread threadAsk(&SlaveBonjour::askJobRoutine, this);
	sf::Thread threadResponse(&SlaveBonjour::responseRoutine, this);
	
	threadAsk.launch();
	threadResponse.launch();
}

/*
bool SlaveBonjour::GetMaster(sf::IpAddress &server)
{
		if (askSocket.receive(data, BUFFER_SIZE, received, server, port) != sf::Socket::Done)
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

void SlaveBonjour::askJobRoutine(SlaveBonjour *socket)
{
	sf::Packet bonjourPacket;
	bonjourPacket << BONJOUR_ASK_JOB;

	while(1)
	{
		if (socket->askSocket.send(bonjourPacket, sf::IpAddress::Broadcast, socket->askPort) != sf::Socket::Done)
		{
			std::cerr << "Failed to send bonjour request." << std::endl;
		}
		else 
		{
			std::cout << "Bonjour broadcasted on port " << socket->askPort << std::endl;
		}

		sf::sleep(socket->sleepTime);
	}
}

void SlaveBonjour::responseRoutine(SlaveBonjour *socket)
{
	sf::IpAddress recvAddress;
	unsigned short recvPort;
	sf::Uint8 id;

std::cout << "waiting..." << std::endl;

	while(1)
	{
		sf::Packet packet;
		if(socket->askSocket.receive(packet, recvAddress, recvPort) != sf::Socket::Done)
		{
			std::cerr << "Failed to receive bonjour response." << std::endl;
			continue;
		}

		packet >> id;
		if(id != BONJOUR_RESPONSE)
		{
			std::cerr << "Received wrong bonjour response." << std::endl;
		}
		else
		{
			std::cout << "Received bonjour response from a master!" << std::endl;
		}
	}
}
