#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <iostream>

#include "OdisMath.h"

namespace OdisEngine
{
	struct Transform2D
	{
		vec2 position { 0, 0 };
		float rotation = 0;
		vec2 scale = { 1, 1 };
	};

	inline std::ostream& operator<<(std::ostream& os, const Transform2D& transform)
	{
		os << "Position:  X - " << transform.position.x << " Y - " << transform.position.y << "\n";
		os << "Scale:  X - " << transform.scale.x << " Y - " << transform.scale.y << "\n";
		os << "Rotation: " << transform.rotation << "\n";

		return os;
	}

	struct Transform3D
	{
		vec3 position = { 0, 0, 0 };
		vec3 rotation = { 0, 0, 0 };
		vec3 scale = { 1, 1, 1 };
	};
}


#endif