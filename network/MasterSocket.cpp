#include "MasterSocket.h"
#include "ApplicationMaster.h"

#include <SFML/System.hpp>
#include <iostream>

MasterSocket::MasterSocket(ApplicationMaster *application,Fractal *f):
	app(application),
	fractal(f),
	threadAuth(0)
{
}

MasterSocket::~MasterSocket()
{
	std::vector<sf::Thread*>::iterator it;
	
	listener.close();
	
	for(it = clientThreads.begin(); it != clientThreads.end(); ++it)
		delete (*it);
	delete threadAuth;
}

bool MasterSocket::Initialize(void)
{
	FractalPartCollection parts = fractal->GetParts();

	if(listener.listen(sf::Socket::AnyPort) != sf::Socket::Done)
	{
		std::cerr << "Failed to initialize master socket." << std::endl;
		return false;
	}

	std::cout << "TCP listener set on port " << listener.getLocalPort() << std::endl;

	if(parts.size() > 0)
	{
		JobList *tmp;
		jobList = new JobList(0, parts[0]);
		tmp = jobList;
		
		for(unsigned int i = 1; i < parts.size(); ++i)
		{
			tmp = new JobList(tmp, parts[i]);
		}
	}
	return true;
}

void MasterSocket::Run(void)
{
	threadAuth = new sf::Thread(&MasterSocket::authentificationRoutine, this);
	threadAuth->launch();
}

void MasterSocket::WaitForEnd(void)
{
	if(threadAuth != 0)
		threadAuth->wait();
}

void MasterSocket::authentificationRoutine(MasterSocket *socket)
{
	while(1)
	{
		sf::TcpSocket *client = new sf::TcpSocket();
		if (socket->listener.accept(*client) != sf::Socket::Done)
		{
			std::cerr << "Failed when accepting connection." << std::endl;
			continue;
		}
		else
		{
			ClientRoutineParams params = {socket, client};
			sf::Thread *thread = new sf::Thread(&MasterSocket::clientRoutine, params);
			socket->mtxClients.lock();
			socket->clientThreads.push_back(thread);
			socket->mtxClients.unlock();
			
			thread->launch();
		}
	}
}

void MasterSocket::clientRoutine(ClientRoutineParams params)
{
	sf::Packet inPacket;
	sf::Packet outPacket;
	FractalPart *part;
	JobList* jobList;
	
	params.socket->mtxJob.lock();
	jobList = params.socket->jobList; //Get the job list
	part = jobList->GetPart(); // Get the current job part
	params.socket->jobList = jobList->GetNext(); // Let's rotate the list!
	params.socket->mtxJob.unlock();

	part->SerializeTask(outPacket);

	sf::Socket::Status st;	
	if((st = params.client->send(outPacket)) != sf::Socket::Done)
	{
		std::cerr << "Error while trying to send data to client." << std::endl;
		std::cerr << st << std::endl;
	}
	else
	{
		sf::Packet packetResult;
		
		std::cout << "Data sent to client." << std::endl;
		if(params.client->receive(packetResult) != sf::Socket::Done)
		{
			std::cerr << "Connection lost." << std::endl;
		}
		else 
		{
			part->DeserializeResult(packetResult);
			std::cout << "Job finished." << std::endl;
			std::cout << part->ToString() << std::endl;

			params.socket->app->OnPartComplete(part);
			
			params.socket->mtxJob.lock();
			delete jobList;
			params.socket->mtxJob.unlock();
		}
	}
}

unsigned short MasterSocket::GetListenerPort(void) const
{
	return listener.getLocalPort();
}

