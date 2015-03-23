#ifndef MASTER_BONJOUR_H
#define MASTER_BONJOUR_H

#include <SFML/Network.hpp>

class MasterBonjour
{
	public:
		MasterBonjour(const unsigned short& a_port);
		virtual ~MasterBonjour();
		void Run(void);

	protected:
		void authentificationRoutine(void);
		sf::UdpSocket bjr;
		static const size_t BUFFER_SIZE = 100; // FIXME
		char data[BUFFER_SIZE];
		const unsigned short& port;
};

#endif
