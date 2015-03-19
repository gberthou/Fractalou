#ifndef APPLICATION_H
#define APPLICATION_H

class Application
{
	public:
		Application();
		virtual ~Application();

		virtual bool Run(void) = 0;
		
		static Application *GetApplication(int argc, char **argv);
};

#endif

