#ifndef APPLICATION_SLAVE_H
#define APPLICATION_SLAVE_H

#include "Application.h"
#include "SlaveBonjour.h"
#include "SlaveSocket.h"

class ApplicationSlave : public	Application
{
	public:
		ApplicationSlave();
		virtual ~ApplicationSlave();

		virtual bool Run(void);

	protected:
		SlaveBonjour *bonjour;
		SlaveSocket *socket;
};

#endif

