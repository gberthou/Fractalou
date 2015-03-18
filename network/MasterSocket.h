#ifndef MASTER_SOCKET_H
#define MASTER_SOCKET_H

#include <SFML/Network.hpp>

class MasterSocket
{
	public:
		MasterSocket(const int&);
		~MasterSocket();

		void AuthentificationRoutine(void);
		void ClientRoutine();

	protected:
		sf::TcpListener listener;
		static const size_t BUFFER_SIZE = 100; // FIXME
		std::vector<sf::TcpSocket*> clients;
};

#endif
