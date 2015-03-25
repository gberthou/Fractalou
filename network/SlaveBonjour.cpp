#include <iostream>

#include "SlaveBonjour.h"
#include "Bonjour.h"
#include "ApplicationSlave.h"

const float MASTER_PERSISTENCE = 20; // seconds

bool operator<(const MasterDesc &d1, const MasterDesc &d2)
{
	if(d1.address.toInteger() < d2.address.toInteger())
		return true;
	return d1.port < d2.port;
}

SlaveBonjour::SlaveBonjour(ApplicationSlave *application, unsigned short aport, sf::Time asleep):
	app(application),
	askPort(aport),
	sleepTime(asleep)
{
}

SlaveBonjour::~SlaveBonjour()
{
}

bool SlaveBonjour::Initialize(void)
{
	return true;
}

void SlaveBonjour::Run()
{
	sf::Thread threadAsk(&SlaveBonjour::askJobRoutine, this);
	sf::Thread threadResponse(&SlaveBonjour::responseRoutine, this);
	
	threadAsk.launch();
	threadResponse.launch();
}

void SlaveBonjour::askJobRoutine(SlaveBonjour *socket)
{
	sf::Packet bonjourPacket;
	bonjourPacket << BONJOUR_ASK_JOB;

	while(1)
	{
		socket->canAsk.lock();

		if (socket->askSocket.send(bonjourPacket, sf::IpAddress::Broadcast, socket->askPort) != sf::Socket::Done)
		{
			std::cerr << "Failed to send bonjour request." << std::endl;
		}
		else 
		{
			std::cout << "Bonjour broadcasted on port " << socket->askPort << std::endl;
		}
		socket->canAsk.unlock();

		sf::sleep(socket->sleepTime);
	}
}

void SlaveBonjour::responseRoutine(SlaveBonjour *socket)
{
	sf::IpAddress recvAddress;
	unsigned short recvPort;
	sf::Uint8 id;
	sf::Uint16 masterPort;
	MasterDesc desc;

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
			continue;
		}
		std::cout << "Received bonjour response from master " << recvAddress<< std::endl;

		packet >> masterPort;
		desc.address = recvAddress;
		desc.port = masterPort;

		socket->masters[desc].restart();
		
		socket->chooseMasterAndConnect();
	}
}

void SlaveBonjour::chooseMasterAndConnect(void)
{
	std::map<MasterDesc, sf::Clock>::iterator it;

	// First, erase masters that are "persistence timed out"
	for(it = masters.begin(); it != masters.end();)
	{
		if(it->second.getElapsedTime().asSeconds() > MASTER_PERSISTENCE)
		{
			std::map<MasterDesc, sf::Clock>::iterator tmp = it++;
			masters.erase(tmp);
		}
		else
			++it;
	}

	// Then, try some masters until it works
	for(it = masters.begin(); it != masters.end(); ++it)
	{
		if(app->ConnectToMaster(it->first.address, it->first.port))
		{
			canAsk.lock();
			std::cout << "Successfully connected to master " << it->first.address << ":" << it->first.port << std::endl;
		}
		else
		{
			std::cout << "Failed to connect to master " << it->first.address << ":" << it->first.port << std::endl;
		}
	}
}

