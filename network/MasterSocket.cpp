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
	std::vector<ClientThread*>::iterator it;
	
	listener.close();
	
	for(it = clientThreads.begin(); it != clientThreads.end(); ++it)
		delete (*it);
	delete threadAuth;
}

bool MasterSocket::Initialize(void)
{
	if(listener.listen(sf::Socket::AnyPort) != sf::Socket::Done)
	{
		std::cerr << "Failed to initialize master socket." << std::endl;
		return false;
	}

	std::cout << "TCP listener set on port " << listener.getLocalPort() << std::endl;

	UpdateJobList(fractal);
	return true;
}

void MasterSocket::UpdateJobList(Fractal *f)
{
	const FractalPartCollection &parts = f->GetParts();
	
	fractal = f;

	if(parts.size() > 0)
	{
		JobList *tmp;
		jobList = new JobList(0, fractal->GetId(), parts[0]);
		tmp = jobList;
		
		for(unsigned int i = 1; i < parts.size(); ++i)
		{
			tmp = new JobList(tmp, fractal->GetId(), parts[i]);
		}
	}
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

void MasterSocket::CheckThreads(void)
{
	std::vector<ClientThread*>::iterator it;
	mtxClients.lock();
	for(it = clientThreads.begin(); it != clientThreads.end();)
	{
		if((*it)->done)
		{
			std::vector<ClientThread*>::iterator tmp = it;
			delete (*it)->thread;
			delete (*it)->socket;
			delete (*it);
			it = clientThreads.erase(tmp);
		}
		else
			++it;
	}
	mtxClients.unlock();
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
			ClientThread *ct = new ClientThread();
			ClientRoutineParams *params = new ClientRoutineParams();
			sf::Thread *thread;

			params->socket = socket;
			params->ct = ct;
			
			socket->CheckThreads();
			
			thread = new sf::Thread(&MasterSocket::clientRoutine, params);
			
			ct->thread = thread;
			ct->socket = client;
			ct->done = false;
			
			socket->mtxClients.lock();
			socket->clientThreads.push_back(ct);
			socket->mtxClients.unlock();
			
			thread->launch();
		}
	}
}

void MasterSocket::clientRoutine(ClientRoutineParams *params)
{
	sf::Socket::Status st;	
	sf::Packet inPacket;
	sf::Packet outPacket;
	FractalPart *part;
	JobList* jobList;

	params->socket->app->LockFractal();	
	jobList = params->socket->jobList; //Get the job list
	
	JobList::LockEmpty();
	if(!JobList::empty)
	{
		JobList::UnlockEmpty();

		part = jobList->GetPart(); // Get the current job part
		params->socket->jobList = jobList->GetNext(); // Let's rotate the list!

		outPacket << jobList->GetFractalId();
		part->SerializeTask(outPacket);
		params->socket->app->UnlockFractal();

		if((st = params->ct->socket->send(outPacket)) != sf::Socket::Done)
		{
			std::cerr << "Error while trying to send data to client." << std::endl;
			std::cerr << st << std::endl;
		}
		else
		{
			sf::Packet packetResult;
			
			std::cout << "Data sent to client." << std::endl;
			if(params->ct->socket->receive(packetResult) != sf::Socket::Done)
			{
				std::cerr << "Connection lost." << std::endl;
			}
			else 
			{
				sf::Uint32 slaveFractalId;
				packetResult >> slaveFractalId;

				params->socket->app->LockFractal();
				if(slaveFractalId == params->socket->fractal->GetId())
				{
					part->DeserializeResult(packetResult);
					
					std::cout << "Job finished." << std::endl;

					params->socket->app->OnPartComplete(part->GetResults());
				
					JobList::LockEmpty();	
					if(jobList != 0 && !JobList::empty)
					{
						JobList::UnlockEmpty();
						delete jobList;
						params->socket->app->SetJobAvailability(!JobList::empty);
					}
					else
						JobList::UnlockEmpty();
				}
				else
					std::cout << "Received result for old fractal..." << std::endl;
				params->socket->app->UnlockFractal();
			}
		}
		params->socket->mtxClients.lock();
		params->ct->socket->disconnect();
		params->ct->done = true;
		params->socket->mtxClients.unlock();
	}
	else
	{
		JobList::UnlockEmpty();

		params->socket->jobList = 0;
		params->socket->app->UnlockFractal();	
	}
}

unsigned short MasterSocket::GetListenerPort(void) const
{
	return listener.getLocalPort();
}

