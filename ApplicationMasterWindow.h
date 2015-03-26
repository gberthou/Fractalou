#ifndef APPLICATION_MASTER_WINDOW_H
#define APPLICATION_MASTER_WINDOW_H

#include <vector>

#include <SFML/Graphics.hpp>

#include "ApplicationMaster.h"
#include "Fractal.h"
#include "FractalViewWindow.h"

class ApplicationMasterWindow : public ApplicationMaster
{
	public:
		ApplicationMasterWindow();
		virtual ~ApplicationMasterWindow();

		virtual bool Run(void);
		virtual void OnPartComplete(FractalPart *part);
	
	protected:
		std::vector<FractalPart*> partsToUpdate;

		// Synchronization
		sf::Mutex mtxUpdate;

		// Visualization
		sf::RenderWindow window;
		FractalViewWindow *view;
};

#endif

