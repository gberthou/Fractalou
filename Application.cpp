#include "Application.h"
#include "ApplicationMaster.h"
#include "ApplicationSlave.h"
#include "Options.h"

Application::Application()
{
}

Application::~Application()
{
}

Application *Application::GetApplication(int argc, char **argv)
{
	Options options(argc, argv);
	
	// TODO: Edit this so that man can launch a master and a slave, for instance
	if(options.HasMaster())
	{
		std::cout << "Running master..." << std::endl;
		return new ApplicationMaster();
	}

	std::cout << "Running slave..." << std::endl;
	return new ApplicationSlave();
}

