#include "MasterSocket.h"

MasterSocket::MasterSocket(const int& port)
{
	if(listener.listen(port) != sf::Socket::Done)
	{
		std::exit(1);
	}
}

void MasterSocket::AuthentificationRoutine(void)
{

}

void MasterSocket::ClientRoutine(sf::TcpSocket* client)
{
	
}
