#include "JobList.h"

JobList::JobList(JobList *parent, FractalPart *p):
	part(p)
{
	if(parent != 0) // Insert
	{
		next = parent->next;
		parent->next = this;
	}
	else // No parent = One-element list
		next = this; // Circular list
}

JobList::~JobList()
{
	// Destructor: erases the job from the list (doesn't delete the FractalPart)
	JobList *prev;
	for(prev = this->next; prev != this; prev = prev->next); // O(list.size)
	prev->next = next;
}

FractalPart *JobList::GetPart(void) const
{
	return part;
}

JobList *JobList::GetNext(void) const
{
	return next;
}

