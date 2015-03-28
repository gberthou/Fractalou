#include "JobList.h"

bool JobList::empty = false;

JobList::JobList(JobList *parent, sf::Uint32 afractalId, FractalPart *p):
	fractalId(afractalId),
	part(p)
{
	empty = false;
	
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
	
	prev = this;
	current = next;
	
	if(this->next != this) //if list doesn't have only one job
	{
		while(current != this) // O(list.size)
		{
			prev = current;
			current = current->next;
		}

		prev->next = next;
	}
	else
	{
		empty = true;
	}
}

sf::Uint32 JobList::GetFractalId(void) const
{
	return fractalId;
}

FractalPart *JobList::GetPart(void) const
{
	return part;
}

JobList *JobList::GetNext(void) const
{
	return next;
}
