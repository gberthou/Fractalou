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
		static void authentificationRoutine(MasterBonjour *socket);

		sf::UdpSocket bjr;
		unsigned short port;
};

#endif

