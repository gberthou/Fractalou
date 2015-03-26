#ifndef SLAVE_SOCKET_H
#define SLAVE_SOCKET_H

#include <SFML/Network.hpp>

#include "FractalPart.h"

class SlaveSocket
{
	public:
		SlaveSocket(const sf::IpAddress &server, unsigned short port);
		virtual ~SlaveSocket();
		
		bool Initialize(void);
		void Run(void);
		void WaitForEnd(void);

	protected:
		static void computeRoutine(SlaveSocket *socket);

		sf::IpAddress masterAddress;
		unsigned short masterPort;	
		sf::TcpSocket *socket;

		// Synchronization
		sf::Thread *threadCompute;
};

#endif
