#include "SlaveSocket.h"

#include <SFML/System.hpp>
#include <iostream>

SlaveSocket::SlaveSocket(const sf::IpAddress server, const unsigned short& port)
{
	if (socket.connect(server, port) != sf::Socket::Done)
	{
		std::cout << "Error connection to server "<< server << " on port : " << port << std::endl;
		return;
	}
	std::cout << "Connected to server " << server << std::endl;
}

SlaveSocket::~SlaveSocket()
{
}

void SlaveSocket::Run()
{
	while(1)
	{
		while(!AskJob());

		std::cout << part.ToString() << std::endl;

		part.ComputeResults();

		std::cout << part.ToString() << std::endl;

		while(!SendData());
	}
}

bool SlaveSocket::AskJob()
{
	const char out[] = "I need dis JOB";
	sf::Packet packet;
	
	if (socket.send(out, sizeof(out)) != sf::Socket::Done)
	{
		return false;
	}
	std::cout << "Asking job..." << std::endl;

	if (socket.receive(packet) != sf::Socket::Done)
	{
		return false;
	}

	part.DeserializeTask(packet);
	std::cout << "Job received !" << std::endl;

	return true;
}

bool SlaveSocket::SendData()
{
	sf::Packet packet;
	part.SerializeResult(packet);

	if (socket.send(packet) != sf::Socket::Done)
	{
		return false;
	}
	std::cout << "Sending processed data" << std::endl;
	return true;
}
