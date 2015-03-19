#ifndef SLAVE_SOCKET_H
#define SLAVE_SOCKET_H

#include <SFML/Network.hpp>

#include "FractalPart.h"

class SlaveSocket
{
	public:
		SlaveSocket(const sf::IpAddress server, const unsigned short& port);
		virtual ~SlaveSocket();
		void Run();

	protected:
		sf::TcpSocket socket;
		static const size_t BUFFER_SIZE = 100; // FIXME
		char data[BUFFER_SIZE];
		FractalPart part;

		bool AskJob();
		bool SendData();
};

#endif
