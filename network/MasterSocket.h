#ifndef MASTER_SOCKET_H
#define MASTER_SOCKET_H

#include <SFML/Network.hpp>

#include "Fractal.h"
#include "JobList.h"

class MasterSocket;

struct ClientThread
{
	sf::Thread *thread;
	sf::TcpSocket *socket;
	bool done;
};

struct ClientRoutineParams
{
	MasterSocket *socket;
	ClientThread *ct;
};

class ApplicationMaster;

class MasterSocket
{
	public:
		MasterSocket(ApplicationMaster *application, Fractal *fractal);
		virtual ~MasterSocket();

		// Initialize is NOT thread-safe! (and has to be)
		bool Initialize(void);
		void Run(void);
		void WaitForEnd(void);

		void CheckThreads(void);

		// UpdateJobList is NOT thread-safe! (and has to be)
		void UpdateJobList(Fractal *fractal);
		
		unsigned short GetListenerPort(void) const;

	protected:
		static void authentificationRoutine(MasterSocket *socket);
		static void clientRoutine(ClientRoutineParams *params); 

		ApplicationMaster *app;

		sf::TcpListener listener;
		unsigned short port;
		Fractal *fractal;
		JobList *jobList;

		// Synchronization
		sf::Thread *threadAuth;
		std::vector<ClientThread*> clientThreads;
		sf::Mutex mtxClients;
};

#endif
