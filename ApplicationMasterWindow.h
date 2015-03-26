#ifndef APPLICATION_MASTER_WINDOW_H
#define APPLICATION_MASTER_WINDOW_H

#include "ApplicationMaster.h"

class ApplicationMasterWindow : public ApplicationMaster
{
	public:
		ApplicationMasterWindow();
		virtual ~ApplicationMasterWindow();

		virtual bool Run(void);
		virtual void OnPartComplete(FractalPart *part);
	
	protected:
};

#endif

