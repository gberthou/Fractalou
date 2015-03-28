#ifndef JOBLIST_H
#define JOBLIST_H

#include <SFML/System.hpp>

#include "FractalPart.h"

class JobList
{
	public:
		JobList(JobList *parent, sf::Uint32 fractalId, FractalPart *p);
		virtual ~JobList();

		sf::Uint32 GetFractalId(void) const;
		FractalPart *GetPart(void) const;
		JobList *GetNext(void) const;
		static bool empty;
	private:
		sf::Uint32 fractalId;
		FractalPart *part;
		JobList *next;

};

#endif

