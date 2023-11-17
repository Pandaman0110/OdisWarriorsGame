#ifndef CAT_H
#define CAT_H

#include <iostream>

#include "World.h"

struct Cat
{
	std::string name;

	inline void write(std::ostream& os)
	{
		os << get_component_name<Cat>() << "\n";
		os << "Name: " << name << "\n";
	}
};

#endif