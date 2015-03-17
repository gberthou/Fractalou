#include "Fractal.h"

Fractal::Fractal()
{
}

Fractal::~Fractal()
{
	for(unsigned int i = 0; i < parts.size(); ++i)
		delete parts[i];
}

void Fractal::CreatePart(const std::vector<QuaternionSuite *> &suites)
{
	parts.push_back(new FractalPart(suites));
}

void Fractal::BuildResult(std::vector<sf::Uint32> &result) const
{
	FractalPartCollection::const_iterator it;
	
	result.clear();
	
	for(it = parts.begin(); it != parts.end(); ++it)
	{
		(*it)->BuildResult(result);
	}
}

