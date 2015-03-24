#ifndef SLAVE_BONJOUR_H
#define SLAVE_BONJOUR_H

#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include <vector>

class SlaveBonjour
{
	public:
		SlaveBonjour(unsigned short aport, sf::Time asleep);
		virtual ~SlaveBonjour();

		bool Initialize(void);
		void Run(void);
		//bool GetMaster();
		
	protected:
		static void authentificationRoutine(SlaveBonjour *socket);

		sf::UdpSocket bjr;
		std::vector<sf::IpAddress> servers;
		unsigned short port;
		sf::Time sleepTime;
		
};

#endif
