#ifndef JOBLIST_H
#define JOBLIST_H

#include "FractalPart.h"

class JobList
{
	public:
		JobList(JobList *parent, FractalPart *p);
		virtual ~JobList();

		FractalPart *GetPart(void) const;
		JobList *GetNext(void) const;
		static bool empty;
	private:
		FractalPart *part;
		JobList *next;

};

#endif

