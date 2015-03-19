#ifndef MASTER_SOCKET_H
#define MASTER_SOCKET_H

#include <SFML/Network.hpp>

class MasterSocket
{
	public:
		MasterSocket(const unsigned short& port);
		virtual ~MasterSocket();

		void AuthentificationRoutine(void);

	protected:
		sf::TcpListener listener;
		static const size_t BUFFER_SIZE = 100; // FIXME
		std::vector<sf::TcpSocket*> clients;

		static void ClientRoutine(sf::TcpSocket*); 
};

#endif
