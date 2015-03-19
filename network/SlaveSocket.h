#ifndef SLAVE_SOCKET_H
#define SLAVE_SOCKET_H

#include <SFML/Network.hpp>

class SlaveSocket
{
	public:
		SlaveSocket(const sf::IpAddress server, const unsigned short& port);
		virtual ~SlaveSocket();

	protected:
		sf::TcpSocket socket;
};

#endif
