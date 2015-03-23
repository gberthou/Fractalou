#ifndef SLAVE_BONJOUR_H
#define SLAVE_BONJOUR_H

#include <SFML/Network.hpp>


class SlaveBonjour
{
	public:
		SlaveBonjour(const unsigned short& a_port);
		virtual ~SlaveBonjour();
		void Run();
		bool GetMaster();
		
	protected:
		void authentificationRoutine();
		sf::UdpSocket bjr;
		static const size_t BUFFER_SIZE = 100; // FIXME
		char data[BUFFER_SIZE];
		std::vector<sf::IpAddress&> servers;
		const unsigned short& port;
};

#endif
