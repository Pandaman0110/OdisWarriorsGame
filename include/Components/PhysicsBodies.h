#ifndef PHYSICS_BODIES_H
#define PHYSICS_BODIES_H

#include <iostream>

#include <box2d/box2d.h>

#include "World.h"

enum class BodyType
{
	Static = b2_staticBody,
	Kinematic = b2_kinematicBody,
	Dynamic = b2_dynamicBody
};

struct KinematicBody2D
{
	BodyType body_type = BodyType::Kinematic;
	b2Body* body = nullptr;

	inline void write(std::ostream& os)
	{
		os << get_component_name<KinematicBody2D>() << "\n";
	}
};

struct StaticBody2D
{
	BodyType body_type = BodyType::Static;
	b2Body* body = nullptr;

	inline void write(std::ostream& os)
	{
		os << get_component_name<StaticBody2D>() << "\n";
	}
};

struct RigidBody2D
{
	BodyType body_type = BodyType::Dynamic;
	b2Body* body = nullptr;

	inline void write(std::ostream& os)
	{
		os << get_component_name<RigidBody2D>() << "\n";
	}
};


#endif