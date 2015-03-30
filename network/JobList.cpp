#include "JobList.h"

bool JobList::empty = false;
sf::Mutex JobList::mtxEmpty;

JobList::JobList(JobList *parent, sf::Uint32 afractalId, FractalPart *p):
	fractalId(afractalId),
	part(p)
{
	mtxEmpty.lock();
	empty = false;
	mtxEmpty.unlock();

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
		mtxEmpty.lock();
		empty = true;
		mtxEmpty.unlock();
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

void JobList::LockEmpty(void)
{
	mtxEmpty.lock();
}

void JobList::UnlockEmpty(void)
{
	mtxEmpty.unlock();
}

