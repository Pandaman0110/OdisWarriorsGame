#ifndef CLAN_H
#define CLAN_H

#include <iostream>

#include "World.h"

struct Clan
{
	std::string name;

	inline void write(std::ostream& os)
	{
		os << get_component_name<Clan>() << "\n";
		os << "Name: " << name << "\n";
	}
};


#endif