#include "SlaveSocket.h"

#include <SFML/System.hpp>
#include <iostream>

SlaveSocket::SlaveSocket(const sf::IpAddress &server, unsigned short port):
	masterAddress(server),
	masterPort(port)
{
}

SlaveSocket::~SlaveSocket()
{
}

bool SlaveSocket::Initialize(void)
{
	if (socket.connect(masterAddress, masterPort) != sf::Socket::Done)
	{
		std::cout << "Error connection to master "<< masterAddress << " on port  " << masterPort << std::endl;
		return false;
	}
	std::cout << "Connected to server " << masterAddress << std::endl;
	return true;
}

void SlaveSocket::Run(void)
{
}

/*
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
*/

bool SlaveSocket::SendData()
{
	/*
	sf::Packet packet;
	part.SerializeResult(packet);

	if (socket.send(packet) != sf::Socket::Done)
	{
		return false;
	}
	std::cout << "Sending processed data" << std::endl;
	*/
	return true;
}
