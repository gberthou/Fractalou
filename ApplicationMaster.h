#ifndef APPLICATION_MASTER_H
#define APPLICATION_MASTER_H

#include <SFML/System.hpp>

#include "Application.h"
#include "MasterSocket.h"
#include "MasterBonjour.h"
#include "netcommon.h"

struct FractalContext
{
	Quaternion center;
	double zoom;
	double limit;
	sf::Uint32 itMax;
};

class ApplicationMaster : public Application
{
	public:
		ApplicationMaster();
		virtual ~ApplicationMaster();

		virtual bool Run(bool blocking);
		virtual void WaitForEnd(void);
		
		virtual void OnPartComplete(const ResultCollection &results) = 0;

		void LockFractal(void);
		void UnlockFractal(void);

	protected:
		sf::Uint32 fractalId;
		Fractal *fractal;
		MasterSocket *socket;
	
	private:	
		MasterBonjour *bonjour;
		
		// Synchronization
		sf::Mutex mtxFractal;
};

#endif

