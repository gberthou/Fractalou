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
	JobList *current;
	JobList *prev;

	if(this->next != next) //if list doesn't have only one job
	{
		prev = this;
		while(current != this) // O(list.size)
		{
			prev = current;
			current = current->next;
		}

		prev->next = next;
	}
}

FractalPart *JobList::GetPart(void) const
{
	return part;
}

JobList *JobList::GetNext(void) const
{
	return next;
}
