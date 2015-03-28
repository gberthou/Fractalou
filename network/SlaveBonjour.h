#ifndef SLAVE_BONJOUR_H
#define SLAVE_BONJOUR_H

#include <map>

#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include "netcommon.h"

class ApplicationSlave;

class SlaveBonjour
{
	public:
		SlaveBonjour(ApplicationSlave *application, unsigned short askPort, sf::Time asleep);
		virtual ~SlaveBonjour();

		bool Initialize(void);
		void Run(void);
		void WaitForEnd(void);

	protected:
		// Routine that asks for a job
		static void askJobRoutine(SlaveBonjour *socket);

		// Routine that waits for a master response
		static void responseRoutine(SlaveBonjour *socket);

		// Future! (maybe)
		static void connectionRoutine(SlaveBonjour *socket);

		void chooseMasterAndConnect(void);

		ApplicationSlave *app;
		sf::UdpSocket askSocket;

		std::map<MachineDesc, sf::Clock> masters;
		unsigned short askPort;
		unsigned short responsePort;
		sf::Time bonjourSleep;
		sf::Time jobSleep;
		bool hadJob;

		// Synchronization
		sf::Thread *threadAsk;
		sf::Mutex canAsk;
};

#endif
