#ifndef FRACTALPART_H
#define FRACTALPART_H

#include <vector>
#include <map>
#include <string>

#include <SFML/System.hpp>
#include <SFML/Network.hpp>

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

		const ResultCollection& GetResults(void) const;

		// SetResults: Used by the master
		void SetResults(const ResultCollection &r);

		// ComputeResults: Used by the slave
		void ComputeResults(void);

		// BuildResult: adds all the results to the given collection
		void BuildResult(ResultCollection &result) const;

		std::string ToString();

		// Used by master
		void SerializeTask(sf::Packet &packet) const;

		// Used by slave
		void SerializeResult(sf::Packet &packet) const;

		// Used by slave
		void DeserializeTask(sf::Packet &packet);

		// Used by master
		void DeserializeResult(sf::Packet &packet);

	private:
		SuiteCollection suites;
		ResultCollection results;
};

#endif

