#include "SlaveSocket.h"

#include <SFML/System.hpp>
#include <iostream>

SlaveSocket::SlaveSocket(const sf::IpAddress &server, unsigned short port):
	masterAddress(server),
	masterPort(port),
	socket(0)
{
}

SlaveSocket::~SlaveSocket()
{
	if(socket != 0)
		delete socket;
}

bool SlaveSocket::Initialize(void)
{
	if(socket != 0)
		delete socket;

	socket = new sf::TcpSocket();	
	if (socket->connect(masterAddress, masterPort) != sf::Socket::Done)
	{
		std::cout << "Error connection to master "<< masterAddress << " on port  " << masterPort << std::endl;
		return false;
	}
	std::cout << "Connected to server " << masterAddress << std::endl;
	return true;
}

void SlaveSocket::Run(void)
{
	threadCompute = new sf::Thread(&SlaveSocket::computeRoutine, this);
	threadCompute->launch();
}

void SlaveSocket::WaitForEnd(void)
{
	if(threadCompute != 0)
		threadCompute->wait();
}

void SlaveSocket::computeRoutine(SlaveSocket *socket)
{
	const unsigned int TRY_NUMBER = 3;
	unsigned int i = 0;
	sf::Packet outPacket;
	FractalPart *part = 0;
	sf::Uint32 fractalId;
	sf::SocketSelector selector;
	bool noJob = false;

	selector.add(*(socket->socket));

	for(i = 0; i < TRY_NUMBER && !noJob; ++i)
	{
		sf::Packet inPacket;

		if(!selector.wait(sf::seconds(2)))
		{
			noJob = true;
		}
		else
		{
			if(socket->socket->receive(inPacket) != sf::Socket::Done)
			{
				std::cerr << "Cannot receive data from master..." << std::endl;
				if(i+1 != TRY_NUMBER)
					std::cerr << "Try n" << (i+2) << "/" << TRY_NUMBER << std::endl;
				continue;
			}

			inPacket >> fractalId;

			part = new FractalPart();
			part->DeserializeTask(inPacket);
			std::cout << "Job received!" << std::cout;
			break;
		}
	}

	if(noJob)
	{
		std::cout << "No job..." << std::endl;
	}
	else if(i == TRY_NUMBER)
	{
		std::cerr << "Too many tries... abort." << std::endl;
	}
	else
	{
		part->ComputeResults();

		outPacket << fractalId;
		part->SerializeResult(outPacket);
		
		for(i = 0; i < TRY_NUMBER; ++i)
		{
			if(socket->socket->send(outPacket) != sf::Socket::Done)
			{
				std::cerr << "Cannot send data to master..." << std::endl;
				if(i+1 != TRY_NUMBER)
					std::cerr << "Try n " << (i+2) << "/" << TRY_NUMBER << std::endl;
			}
			else
				break;
		}
		delete part;
		
		if(i != TRY_NUMBER)
		{
			std::cout << "Data sent to master! Job done!" << std::endl;
		}
	}

	socket->socket->disconnect();
}

