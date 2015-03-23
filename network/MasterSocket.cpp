#include "MasterSocket.h"

#include <SFML/System.hpp>
#include <iostream>

MasterSocket::MasterSocket(const unsigned short& port, const Fractal& f) :
	fractal(f)
{
	FractalPartCollection parts = f.GetParts();

	if(listener.listen(port) != sf::Socket::Done)
	{
		std::cerr << "Failed to initialize master socket." << std::endl;
		std::exit(1);
	}

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
}

MasterSocket::~MasterSocket() {
	for (std::vector<sf::TcpSocket*>::iterator it = clients.begin() ; it != clients.end(); ++it)
		delete *it;
	listener.close();
}

void MasterSocket::AuthentificationRoutine(void)
{
	while(1)
	{
		sf::TcpSocket* client = new sf::TcpSocket;
		if (listener.accept(*client) != sf::Socket::Done)
		{
			std::cerr << "Failed when accepting connection." << std::endl;
			exit(1);
		} else {
			clients.push_back(client);
			ClientRoutineParams p = {this, client, fractal};
			sf::Thread thread(&MasterSocket::ClientRoutine, p);
			thread.launch();
			return;
		}
	}
}

void MasterSocket::ClientRoutine(ClientRoutineParams params)
{
	char data[MasterSocket::BUFFER_SIZE];
	std::size_t received;

	sf::sleep(sf::milliseconds(20));

	while(1)
	{
		if(params.client->receive(data, MasterSocket::BUFFER_SIZE, received) != sf::Socket::Done)
		{
			std::cerr << "Connection lost." << std::endl;
			return;
		} 
		else 
		{
			sf::Packet packet;
			FractalPart *part = params.msocket->jobList->GetPart(); // Get the current job part

			part->SerializeTask(packet);
			std::cout << data << std::endl;
			if(params.client->send(packet) != sf::Socket::Done)
			{
				std::cerr << "Error while trying to send data to client." << std::endl;
			}
			else
			{
				sf::Packet packetResult;
				
				params.msocket->jobList = params.msocket->jobList->GetNext(); // Let's rotate the list!
				
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
				}
			}
		}
	}
}
