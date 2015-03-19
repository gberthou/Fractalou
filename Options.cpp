#include <string>
#include <algorithm>

#include "Options.h"

Options::Options(int argc, char **argv)
{
	build(argc, argv);
}

Options::~Options()
{
}

bool Options::HasMaster(void) const
{
	return hasMaster;
}

unsigned int Options::GetSlaveCount(void) const
{
	return slaveCount;
}

void Options::build(int argc, char **argv)
{
	bool slaveSet = false;
	
	// Default settings
	hasMaster = false;
	slaveCount = 1;

	for(int i = 1; i < argc; ++i)
	{
		std::string flag(argv[i]);
		std::transform(flag.begin(), flag.end(), flag.begin(), ::tolower);

		if(flag.compare("-m") == 0) // Master flag
		{
			hasMaster = true;
			if(!slaveSet)
				slaveCount = 0;
		}
		else if(flag.compare(0, 2, "-s") == 0) // Slave flag
		{
			// TODO
			slaveCount = 1;
			slaveSet = true;
		}
	}
}

