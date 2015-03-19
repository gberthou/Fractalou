#ifndef APPLICATION_MASTER_H
#define APPLICATION_MASTER_H

#include "Application.h"
#include "MasterSocket.h"

class ApplicationMaster : public Application
{
	public:
		ApplicationMaster();
		virtual ~ApplicationMaster();

		virtual bool Run(void);

	protected:
		MasterSocket *socket;
};

#endif

