#include "FractalPart.h"

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
	result.insert(results.begin(), results.end());
}

