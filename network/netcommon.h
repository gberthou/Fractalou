#ifndef NETCOMMON_H
#define NETCOMMON_H

#include <SFML/Network.hpp>

struct MachineDesc
{
	sf::IpAddress address;
	unsigned short port;
};

bool operator<(const MachineDesc &d1, const MachineDesc &d2);

#endif

