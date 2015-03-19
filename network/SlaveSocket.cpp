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
