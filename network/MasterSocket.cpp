#include "MasterSocket.h"

#include <SFML/System.hpp>
#include <iostream>

MasterSocket::MasterSocket(const int& port)
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
			sf::Thread thread(&MasterSocket::ClientRoutine, this);
			thread.launch();
		}
	}
}

void MasterSocket::ClientRoutine()
{
	char data[MasterSocket::BUFFER_SIZE];
	std::size_t received;

	// TCP socket:
	if (clients[0]->receive(data, MasterSocket::BUFFER_SIZE, received) != sf::Socket::Done)
	{
		std::cerr << "Failed when receiving data from client." << std::endl;
		exit(1);
	} else {
		std::cout << data << std::endl;
	}
}
