#ifndef CAT_H
#define CAT_H

#include <iostream>

#include "World.h"

struct Cat
{
	std::string prefix;
	std::string suffix;
	std::string role;
};

inline std::string get_name(const Cat& cat)
{
	return cat.prefix + cat.suffix;
}

inline std::ostream& operator <<(std::ostream& os, const Cat& cat)
{
	os << "Name: " << get_name(cat) << " ";
	os << "Role: " << cat.role;
	return os;
}

#endif