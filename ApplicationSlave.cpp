#include "ApplicationSlave.h"

ApplicationSlave::ApplicationSlave():
	socket(0)
{
}

ApplicationSlave::~ApplicationSlave()
{
}

bool ApplicationSlave::Run(void)
{
	socket = new SlaveSocket("localhost", 54000);
	socket->Run();
	return true;
}

