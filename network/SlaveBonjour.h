#ifndef SLAVE_BONJOUR_H
#define SLAVE_BONJOUR_H

#include <map>

#include <SFML/Network.hpp>
#include <SFML/System.hpp>

struct MasterDesc
{
	sf::IpAddress address;
	unsigned short port;
};

bool operator<(const MasterDesc &d1, const MasterDesc &d2);

class ApplicationSlave;

class SlaveBonjour
{
	public:
		SlaveBonjour(ApplicationSlave *application, unsigned short askPort, sf::Time asleep);
		virtual ~SlaveBonjour();

		bool Initialize(void);
		void Run(void);
		
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

		std::map<MasterDesc, sf::Clock> masters;
		unsigned short askPort;
		unsigned short responsePort;
		sf::Time sleepTime;

		// Synchronization
		sf::Mutex canAsk;
};

#endif
