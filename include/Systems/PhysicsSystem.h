#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include <iostream>
#include <memory>

#include <box2d/box2d.h>

#include "Game.h"
#include "Components/Transform.h"
#include "Components/Cat.h"


const float PIXELS_PER_METER = 1.0f / 50.0f;
const float TIME_STEP = 1.0f / 60.0f;
const uint8_t VELOCITY_ITERATIONS = 8;
const uint8_t POSITION_ITERATIONS = 3;

class PhysicsSystem
{
private:
	std::unique_ptr<b2World> physics_world;

public:
	PhysicsSystem()
	{
	};

	
	void operator() (Cat& transform) 
	{


	}
	/*
	static vec2 to_world(vec2 pixel_position)
	{
		return vec2(pixel_position.x * PIXELS_PER_METER, pixel_position.x * PIXELS_PER_METER);
	}

	static float to_world_scalar(float scalar)
	{

	}

	static vec2 to_pixel(vec2 world_position)
	{

	}

	static float to_pixel_scalar(float scalar)
	{

	}
	*/
};

#endif