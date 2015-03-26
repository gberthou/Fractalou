#ifndef MASTER_SOCKET_H
#define MASTER_SOCKET_H

#include <SFML/Network.hpp>

#include "Fractal.h"
#include "JobList.h"

class MasterSocket;

struct ClientRoutineParams
{
	MasterSocket *socket;
	sf::TcpSocket *client;
};

class ApplicationMaster;

class MasterSocket
{
	public:
		MasterSocket(ApplicationMaster *application, Fractal *fractal);
		virtual ~MasterSocket();

		bool Initialize(void);
		void Run(void);
		void WaitForEnd(void);
		
		unsigned short GetListenerPort(void) const;

	protected:
		static void authentificationRoutine(MasterSocket *socket);
		static void clientRoutine(ClientRoutineParams params); 

		ApplicationMaster *app;

		sf::TcpListener listener;
		//std::vector<sf::TcpSocket> clients;
		unsigned short port;
		Fractal *fractal;
		JobList *jobList;

		// Synchronization
		sf::Thread *threadAuth;
		std::vector<sf::Thread*> clientThreads;
		sf::Mutex mtxJob;
		sf::Mutex mtxClients;
};

#endif
