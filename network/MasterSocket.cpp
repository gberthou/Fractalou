#include "MasterSocket.h"

#include <SFML/System.hpp>
#include <iostream>

MasterSocket::MasterSocket(const unsigned short& port)
{
	if(listener.listen(port) != sf::Socket::Done)
	{
		std::cerr << "Failed to initialize master socket." << std::endl;
		std::exit(1);
	}
}

MasterSocket::~MasterSocket() {
	for (std::vector<sf::TcpSocket*>::iterator it = clients.begin() ; it != clients.end(); ++it)
		delete *it;
	listener.close();
}

void MasterSocket::AuthentificationRoutine(void)
{
	while(1)
	{
		sf::TcpSocket* client = new sf::TcpSocket;
		if (listener.accept(*client) != sf::Socket::Done)
		{
			std::cerr << "Failed when accepting connection." << std::endl;
			exit(1);
		} else {
			clients.push_back(client);
			sf::Thread thread(&MasterSocket::ClientRoutine, client);
			thread.launch();
		}
	}
}

void MasterSocket::ClientRoutine(sf::TcpSocket* client)
{
	char data[MasterSocket::BUFFER_SIZE];
	std::size_t received;

	while(1)
	{
		if(client->receive(data, MasterSocket::BUFFER_SIZE, received) != sf::Socket::Done)
		{
			std::cerr << "Connection lost." << std::endl;
			return;
		} 
		else 
		{
			std::cout << data << std::endl;
			if(client->send(data, BUFFER_SIZE) != sf::Socket::Done)
			{
				std::cerr << "Error while trying to send data to client." << std::endl;
			}
			else
			{
				std::cout << "Data sent to client." << std::endl;
			}
		}
	}
}
