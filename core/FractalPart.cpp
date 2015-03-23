#include "FractalPart.h"
#include "fractals/QS_Julia.h"
#include "Utils.h"

#include <iostream>

FractalPart::FractalPart()
{
}

FractalPart::FractalPart(const SuiteCollection &asuites):
	suites(asuites)
{
}

FractalPart::~FractalPart()
{
	SuiteCollection::iterator it;
	for(it = suites.begin(); it != suites.end(); ++it)
		delete (*it);
}

void FractalPart::AddSuite(QuaternionSuite *suite)
{
	suites.push_back(suite);
}

void FractalPart::SetResults(const ResultCollection &r)
{
	results = r;
}

void FractalPart::ComputeResults(void)
{
	SuiteCollection::const_iterator it;
	results.clear();
	for(it = suites.begin(); it != suites.end(); ++it)
	{
		sf::Uint32 r = (*it)->ComputeIterationNumber();
		sf::Uint32 itMax = (*it)->GetIterationsMax();
		results.insert(ResultPair((*it)->GetId(), (double)r/itMax));
	}
}

void FractalPart::BuildResult(ResultCollection &result) const
{
	ResultCollection::const_iterator it;
	result.insert(results.begin(), results.end());
}

std::string FractalPart::ToString()
{
	return ttos(suites.size()) + " " + ttos(results.size()) + " " ;
}

ResultCollection& FractalPart::GetResults()
{
	return results;
}

void FractalPart::SerializeTask(sf::Packet &packet) const
{
	sf::Uint32 size = suites.size();
	std::cout << "this is my sze: " << size << std::endl;
	packet << size;
	
	for(SuiteCollection::const_iterator it = suites.begin() ; it != suites.end(); ++it)
		(*it)->Serialize(packet);
}

void FractalPart::SerializeResult(sf::Packet &packet) const
{
	sf::Uint32 size = results.size();
	packet << size;
	
	for(ResultCollection::const_iterator it = results.begin() ; it != results.end(); ++it)
	 	packet << it->first << it->second;
}

void FractalPart::DeserializeTask(sf::Packet &packet)
{
	sf::Uint32 size;	
	QS_Julia* qs;

	packet >> size;

	suites.clear();
	suites.reserve(size); // Optimization

	std::cout << "Nb px: " << size << std::endl;
	for(sf::Uint32 i = 0; i < size; ++i)
	{
		qs = new QS_Julia();
		qs->DeSerialize(packet);
		suites.push_back(qs);
	}
}

void FractalPart::DeserializeResult(sf::Packet &packet)
{
	sf::Uint32 size;
	sf::Uint32 ui;
	double d;
	
	packet >> size;
	for(sf::Uint32 i = 0; i < size; ++i)
	{
		packet >> ui >> d;
		results.insert(ResultPair(ui, d));
	}
}

