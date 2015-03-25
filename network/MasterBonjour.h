#ifndef MASTER_BONJOUR_H
#define MASTER_BONJOUR_H

#include <SFML/Network.hpp>

class MasterBonjour
{
	public:
		MasterBonjour(unsigned short aport);
		virtual ~MasterBonjour();

		bool Initialize(void);
		void Run(void);

	protected:
		static void ackJobRoutine(MasterBonjour *socket);

		sf::UdpSocket bjr; // Broadcast
		sf::TcpListener listener; // Gets new connections from slaves
		unsigned short port;
		unsigned short listenerPort;
};

#endif

