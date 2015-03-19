#ifndef MASTER_SOCKET_H
#define MASTER_SOCKET_H

#include "../core/Fractal.h"

#include <SFML/Network.hpp>

class MasterSocket
{
	public:
		MasterSocket(const unsigned short& port, const Fractal&);
		virtual ~MasterSocket();

		void AuthentificationRoutine(void);

	protected:
		struct ClientRoutineParams {
			sf::TcpSocket* client;
			const Fractal& fractal;
		};

		sf::TcpListener listener;
		static const size_t BUFFER_SIZE = 100; // FIXME
		std::vector<sf::TcpSocket*> clients;
		Fractal fractal;

		static void ClientRoutine(ClientRoutineParams params); 
};

#endif
