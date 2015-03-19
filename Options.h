#ifndef OPTIONS_H
#define OPTIONS_H

class Options
{
	public:
		Options(int argc, char **argv);
		virtual ~Options();

		bool HasMaster(void) const;
		unsigned int GetSlaveCount(void) const;

	private:
		void build(int argc, char **argv);

		bool hasMaster;
		unsigned int slaveCount;
};

#endif

