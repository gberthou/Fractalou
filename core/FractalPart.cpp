#include "FractalPart.h"
#include "fractals/QS_Julia.h"

FractalPart::FractalPart()
{
}

FractalPart::FractalPart(const SuiteCollection &asuites):
	suites(asuites)
{
}

FractalPart::~FractalPart()
{
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
	for(it = results.begin(); it != results.end(); ++it)
		result.insert(*it);
}

std::string FractalPart::ToString()
{
	return std::to_string(suites.size()) + " " + std::to_string(results.size()) + " " + std::to_string(suites[0]->GetId());
}

std::ostream& operator<<(std::ostream& os, const FractalPart& obj)
{
	os << obj.suites.size();
	SuiteCollection sc = SuiteCollection(obj.suites);
	for(SuiteCollection::iterator it = sc.begin() ; it != sc.end(); ++it)
		os << (**it) << std::endl;
	os << obj.results.size();
	ResultCollection rc = ResultCollection(obj.results);
	for(ResultCollection::iterator it = rc.begin() ; it != rc.end(); ++it)
	 	os << it->first << it->second;
	return os;
}
std::istream& operator>>(std::istream& is, FractalPart& obj)
{
	size_t size;
	is >> size;
	QS_Julia* qs;
	sf::Uint32 ui;
	double d;
	for(size_t i = 0; i < size; ++i)
	{
		Quaternion q(0, 0, 0, 0);
		Quaternion z0(0, 0, 0, 0);
		qs = new QS_Julia(1, z0, q, 0, 0);
		is >> *qs;
		obj.suites.push_back(qs);
	}
	is >> size;
	for(size_t i = 0; i < size; ++i)
	{
		is >> ui >> d;
		obj.results.insert(std::pair<sf::Uint32, double>(ui, d));
	}
	return is;
}
