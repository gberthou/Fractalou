#include "netcommon.h"

bool operator<(const MachineDesc &d1, const MachineDesc &d2)
{
	if(d1.address.toInteger() < d2.address.toInteger())
		return true;
	return d1.port < d2.port;
}

