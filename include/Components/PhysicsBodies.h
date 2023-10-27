#ifndef PHYSICS_BODIES_H
#define PHYSICS_BODIES_H

#include <iostream>

#include "World.h"

struct StaticBody2D
{
	//Texture2D texture;

	inline void write(std::ostream& os)
	{
		os << get_component_name<StaticBody2D>() << "\n";
	}

};

struct RigidBody2D
{

	inline void write(std::ostream& os)
	{
		os << get_component_name<RigidBody2D>() << "\n";
	}
};

struct KinematicBody2D
{

	inline void write(std::ostream& os)
	{
		os << get_component_name<KinematicBody2D>() << "\n";
	}
};


#endif