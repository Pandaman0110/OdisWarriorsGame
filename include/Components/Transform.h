#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <iostream>

#include "OdisMath.h"
#include "World.h"


struct Transform2D
{
	glm::vec2 position { 0, 0 };
	float rotation = 0;
	glm::vec2 scale = { 1, 1 };

	inline void write(std::ostream& os)
	{
		os << get_component_name<Transform2D>() << "\n";
		os << "Position:  X - " << position.x << " Y - " << position.y << "\n";
		os << "Scale:  X - " << scale.x << " Y - " << scale.y << "\n";
		os << "Rotation: " << rotation << "\n";
	}
};

struct Transform3D
{
	glm::vec3 position = { 0, 0, 0 };
	glm::vec3 rotation = { 0, 0, 0 };
	glm::vec3 scale = { 1, 1, 1 };
};


#endif