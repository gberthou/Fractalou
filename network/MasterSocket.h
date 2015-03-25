#ifndef MASTER_SOCKET_H
#define MASTER_SOCKET_H

#include <SFML/Network.hpp>

#include "Fractal.h"
#include "JobList.h"

class MasterSocket;

struct ClientRoutineParams
{
	MasterSocket *socket;
	sf::TcpSocket &client;
};

class MasterSocket
{
	public:
		MasterSocket(Fractal *fractal);
		virtual ~MasterSocket();

		bool Initialize(void);
		void Run(void);

	protected:
		static void authentificationRoutine(MasterSocket *socket);
		static void clientRoutine(ClientRoutineParams params); 

		sf::TcpListener listener;
		//std::vector<sf::TcpSocket> clients;
		unsigned short port;
		Fractal *fractal;
		JobList *jobList;
};

#endif
