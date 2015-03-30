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

		virtual bool Run(bool blocking);
		virtual void OnPartComplete(const ResultCollection &results);
	
	protected:
		void replaceFractal(Fractal *fractal);
		void displayHUD(const FractalContext *context);
		
		std::vector<ResultCollection> partsToUpdate;

		// Synchronization
		sf::Mutex mtxUpdate;

		// Visualization
		sf::RenderWindow window;
		sf::Font font;
		FractalViewWindow *view;
};

#endif

