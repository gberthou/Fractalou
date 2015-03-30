#include <iostream>

#include "MasterBonjour.h"
#include "Bonjour.h"
#include "ApplicationMaster.h"

MasterBonjour::MasterBonjour(ApplicationMaster *application, unsigned short aport, unsigned short lport):
	app(application),
	port(aport),
	listenerPort(lport),
	jobAvailability(false),
	threadAck(0)
{
}

MasterBonjour::~MasterBonjour()
{
	delete threadAck;	
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
	threadAck = new sf::Thread(&MasterBonjour::ackJobRoutine, this);
	threadAck->launch();
}

void MasterBonjour::WaitForEnd(void)
{
	if(threadAck != 0)
		threadAck->wait();
}

void MasterBonjour::SetJobAvailability(bool availability)
{
	mtxJobAvailability.lock();
	jobAvailability = availability;
	mtxJobAvailability.unlock();
}

void MasterBonjour::ackJobRoutine(MasterBonjour *socket)
{
	sf::Uint8 id;
	sf::IpAddress sender;
	
	while(1)
	{
		sf::Packet inPacket;
		sf::Packet outPacket;

		socket->mtxJobAvailability.lock();
		if(!socket->jobAvailability)
		{
			socket->mtxJobAvailability.unlock();
			sf::sleep(sf::milliseconds(200));
			continue;
		}
		socket->mtxJobAvailability.unlock();

		if (socket->bjr.receive(inPacket, sender, socket->port) != sf::Socket::Done)
		{
			std::cerr << "Failed to recognize bonjour request." << std::endl;
			continue;
		}
		
		inPacket >> id;
		if(id != BONJOUR_ASK_JOB)
		{
			std::cerr << "Received wrong bonjour request. (" << (int)id << ")" << std::endl;
			continue;
		}
	
		outPacket << BONJOUR_RESPONSE << (sf::Uint16)socket->listenerPort;

		if (socket->bjr.send(outPacket, sender, socket->port) != sf::Socket::Done)
		{
			std::cerr << "Failed to answer bonjour to " << sender << " on port " << socket->port << std::endl;
		}
		else
		{
			//std::cout << "Bonjour process done with " << sender << " on port " << socket->port << std::endl;
		}
	}
}

