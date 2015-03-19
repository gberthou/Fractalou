#ifndef FRACTALPART_H
#define FRACTALPART_H

#include <vector>
#include <map>
#include <string>

#include <SFML/System.hpp>

#include "QuaternionSuite.h"

typedef std::vector<QuaternionSuite *> SuiteCollection;
typedef std::map<sf::Uint32, double> ResultCollection;
typedef std::pair<sf::Uint32, double> ResultPair;

class FractalPart
{
	public:
		FractalPart();
		FractalPart(const SuiteCollection &suites);
		virtual ~FractalPart();

		// AddSuite: adds the given suite to the suite collection
		void AddSuite(QuaternionSuite *suite);

		// SetResults: Used by the master
		void SetResults(const ResultCollection &r);

		// ComputeResults: Used by the slave
		void ComputeResults(void);

		// BuildResult: adds all the results to the given collection
		void BuildResult(ResultCollection &result) const;

		std::string ToString();

		friend std::ostream& operator<<(std::ostream& os, const FractalPart& obj);
		friend std::istream& operator>>(std::istream& is, FractalPart& obj);

	private:
		SuiteCollection suites;
		ResultCollection results;
};

#endif

