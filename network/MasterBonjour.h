#ifndef MASTER_BONJOUR_H
#define MASTER_BONJOUR_H

#include <SFML/Network.hpp>

class ApplicationMaster;

class MasterBonjour
{
	public:
		MasterBonjour(ApplicationMaster *master, unsigned short port, unsigned short listenerPort);
		virtual ~MasterBonjour();

		bool Initialize(void);
		void Run(void);
		void WaitForEnd(void);

	protected:
		// Routine that waits for job requests and responds to them
		static void ackJobRoutine(MasterBonjour *socket);

		ApplicationMaster *app;
		sf::UdpSocket bjr; // Broadcast
		unsigned short port;
		unsigned short listenerPort;

		// Synchronization
		sf::Thread *threadAck;
};

#endif

