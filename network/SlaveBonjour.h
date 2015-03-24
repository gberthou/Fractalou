#ifndef SLAVE_BONJOUR_H
#define SLAVE_BONJOUR_H

#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include <vector>

class SlaveBonjour
{
	public:
		SlaveBonjour(unsigned short askPort, sf::Time asleep);
		virtual ~SlaveBonjour();

		bool Initialize(void);
		void Run(void);
		//bool GetMaster();
		
	protected:
		static void askJobRoutine(SlaveBonjour *socket);
		static void responseRoutine(SlaveBonjour *socket);

		sf::UdpSocket askSocket;

		std::vector<sf::IpAddress> servers;
		unsigned short askPort;
		unsigned short responsePort;
		sf::Time sleepTime;
};

#endif
