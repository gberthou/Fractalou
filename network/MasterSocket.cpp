#include "MasterSocket.h"

#include <SFML/System.hpp>
#include <iostream>

MasterSocket::MasterSocket(Fractal *f):
	fractal(f)
{
}

MasterSocket::~MasterSocket()
{
	listener.close();
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
	sf::Thread threadAuth(&MasterSocket::authentificationRoutine, this);
	threadAuth.launch();
}

void MasterSocket::authentificationRoutine(MasterSocket *socket)
{
	while(1)
	{
		sf::TcpSocket client;
		if (socket->listener.accept(client) != sf::Socket::Done)
		{
			std::cerr << "Failed when accepting connection." << std::endl;
			continue;
		}
		else
		{
			ClientRoutineParams params = {socket, client};
			//socket->clients.push_back(client);
			
			// :/
			sf::Thread thread(&MasterSocket::clientRoutine, params);
			thread.launch();
		}
	}
}

void MasterSocket::clientRoutine(ClientRoutineParams params)
{
	while(1)
	{
		sf::Packet inPacket;
		sf::Packet outPacket;
		FractalPart *part;
		
		if(params.client.receive(inPacket) != sf::Socket::Done)
		{
			std::cerr << "Connection lost." << std::endl;
			return;
		} 

		part = params.socket->jobList->GetPart(); // Get the current job part
		part->SerializeTask(outPacket);
		
		if(params.client.send(outPacket) != sf::Socket::Done)
		{
			std::cerr << "Error while trying to send data to client." << std::endl;
		}
		else
		{
			sf::Packet packetResult;
			
			params.socket->jobList = params.socket->jobList->GetNext(); // Let's rotate the list!
			
			std::cout << "Data sent to client." << std::endl;
			if(params.client.receive(packetResult) != sf::Socket::Done)
			{
				std::cerr << "Connection lost." << std::endl;
			}
			else 
			{
				part->DeserializeResult(packetResult);
				std::cout << "Job finished." << std::endl;
				std::cout << part->ToString() << std::endl;
			}
		}
	}
}
