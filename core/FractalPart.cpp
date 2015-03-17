#include "FractalPart.h"

FractalPart::FractalPart()
{
}

FractalPart::FractalPart(const std::vector<QuaternionSuite *> &asuites):
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

void FractalPart::SetResults(const std::vector<sf::Uint32> &r)
{
	results = r;
}

void FractalPart::BuildResult(std::vector<sf::Uint32> &result) const
{
	result.insert(result.begin(), results.begin(), results.end());
}

