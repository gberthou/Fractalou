#include "FractalPart.h"
#include "fractals/QS_Julia.h"
#include "Utils.h"

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

sf::Packet& operator<<(sf::Packet& os, const FractalPart& obj)
{
	sf::Uint32 size = obj.suites.size();
	std::cout << "this is my sze: " << size << std::endl;
	os << size;
	//SuiteCollection sc = SuiteCollection(obj.suites);
	for(SuiteCollection::const_iterator it = obj.suites.begin() ; it != obj.suites.end(); ++it)
		os << (**it);
	size = obj.results.size();
	os << size;
	//ResultCollection rc = ResultCollection(obj.results);
	for(ResultCollection::const_iterator it = obj.results.begin() ; it != obj.results.end(); ++it)
	 	os << it->first << it->second;
	return os;
}
sf::Packet& operator>>(sf::Packet& is, FractalPart& obj)
{
	sf::Uint32 size;
	is >> size;
	QS_Julia* qs;
	sf::Uint32 ui;
	double d;

	std::cout << "Nb px: " << size << std::endl;
	for(sf::Uint32 i = 0; i < size; ++i)
	{
		Quaternion q(0, 0, 0, 0);
		Quaternion z0(0, 0, 0, 0);
		qs = new QS_Julia(1, z0, q, 0, 0);
		is >> *qs;
		obj.suites.push_back(qs);
	}
	is >> size;
	for(sf::Uint32 i = 0; i < size; ++i)
	{
		is >> ui >> d;
		obj.results.insert(std::pair<sf::Uint32, double>(ui, d));
	}
	return is;
}
