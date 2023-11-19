#ifndef CLAN_H
#define CLAN_H

#include <iostream>

#include "World.h"

struct Clan
{
	std::string name;
};

inline std::ostream& operator <<(std::ostream& os, const Clan& cat)
{
	os << "Name: " << cat.name;
	return os;
}


#endif