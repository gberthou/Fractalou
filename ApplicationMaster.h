#ifndef APPLICATION_MASTER_H
#define APPLICATION_MASTER_H

#include <SFML/System.hpp>

#include "Application.h"
#include "MasterSocket.h"
#include "MasterBonjour.h"
#include "netcommon.h"

class ApplicationMaster : public Application
{
	public:
		ApplicationMaster();
		virtual ~ApplicationMaster();

		virtual bool Run(void);
		virtual void OnPartComplete(FractalPart *part) = 0;
	
	protected:
		void setFractal(Fractal *fractal);

	private:	
		MasterBonjour *bonjour;
		MasterSocket *socket;

		Fractal *fractal;
};

#endif

