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

