#ifndef MASTER_SOCKET_H
#define MASTER_SOCKET_H

#include <SFML/Network.hpp>

#include "Fractal.h"
#include "JobList.h"

class MasterSocket;

struct ClientRoutineParams
{
	MasterSocket *msocket;
	sf::TcpSocket* client;
	const Fractal& fractal;
};

class MasterSocket
{
	public:
		MasterSocket(const unsigned short& port, const Fractal&);
		virtual ~MasterSocket();

		void AuthentificationRoutine(void);

	protected:

		sf::TcpListener listener;
		static const size_t BUFFER_SIZE = 100; // FIXME
		std::vector<sf::TcpSocket*> clients;
		Fractal fractal;
		JobList *jobList;

		static void ClientRoutine(ClientRoutineParams params); 
};

#endif
