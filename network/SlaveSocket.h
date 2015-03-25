#ifndef SLAVE_SOCKET_H
#define SLAVE_SOCKET_H

#include <SFML/Network.hpp>

#include "FractalPart.h"

class SlaveSocket
{
	public:
		SlaveSocket(const sf::IpAddress &server, unsigned short port);
		virtual ~SlaveSocket();
		
		void Run(void);
		bool Initialize(void);

	protected:
		sf::IpAddress masterAddress;
		unsigned short masterPort;	
		sf::TcpSocket socket;

		FractalPart part;

		bool SendData();
};

#endif
