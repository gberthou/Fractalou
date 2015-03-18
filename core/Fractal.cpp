#include "Fractal.h"

Fractal::Fractal()
{
}

Fractal::~Fractal()
{
	for(unsigned int i = 0; i < parts.size(); ++i)
		delete parts[i];
}

void Fractal::CreatePart(const SuiteCollection &suites)
{
	parts.push_back(new FractalPart(suites));
}

void Fractal::ComputeResults(void)
{
	FractalPartCollection::iterator it;
	for(it = parts.begin(); it != parts.end(); ++it)
	{
		(*it)->ComputeResults();
	}
}

void Fractal::BuildResult(ResultCollection &result) const
{
	FractalPartCollection::const_iterator it;
	
	result.clear();
	
	for(it = parts.begin(); it != parts.end(); ++it)
	{
		(*it)->BuildResult(result);
	}
}

