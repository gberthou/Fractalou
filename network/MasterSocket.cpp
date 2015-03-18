#include "MasterSocket.h"

MasterSocket::MasterSocket(const int& port)
{
	if(listener.listen(port) != sf::Socket::Done)
	{
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
			exit(1);
		} else {
			clients.push_back(client);
		}
	}
}

void MasterSocket::ClientRoutine()
{
	
}
