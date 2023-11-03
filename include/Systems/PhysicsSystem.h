#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include <iostream>
#include <memory>

#include <box2d/box2d.h>

#include "Game.h"
#include "OdisMath.h"
#include "Components/Transform.h"
#include "Components/Cat.h"
#include "Components/PhysicsBodies.h"
#include "World.h"


const float PIXELS_PER_METER = 1.0f / 50.0f;
const float TIME_STEP = 1.0f / 60.0f;
const uint8_t VELOCITY_ITERATIONS = 8;
const uint8_t POSITION_ITERATIONS = 3;


template <typename T>
concept PhysicsComponent = requires (T component)
{
	{ component.body_type };
	{ component.body };
};

class PhysicsSystem
{
private:
	b2World* physics_world;

	template <PhysicsComponent T>
	glm::vec2 get_position(T& component)
	{
		b2Vec2 b = component.body->GetPosition();
		return glm::vec2{ b.x, b.y };
	}
	template <PhysicsComponent T1, VectorType T2>
	void set_linear_velocity(T1& component, T2 velocity)
	{
		component.body->SetLinearVelocity(b2Vec2{ velocity.x, velocity.y });
	}
	template <PhysicsComponent T1>
	void set_linear_velocity(T1& component, float x, float y)
	{
		component.body->SetLinearVelocity(b2Vec2{ x, y });
	}
public:
	PhysicsSystem()
	{
		physics_world = new b2World(std::move(b2Vec2{ 0.0f, 0.0f }));
	};
	~PhysicsSystem()
	{
		delete physics_world;
	}
	PhysicsSystem(const PhysicsSystem& other)
	{
		this->physics_world = other.physics_world;
	}
	PhysicsSystem& operator=(const PhysicsSystem& other) 
	{
		this->physics_world = other.physics_world;
		return *this;
	}
	PhysicsSystem(PhysicsSystem&& other) noexcept
	{
		this->physics_world = std::exchange(other.physics_world, nullptr);
	}
	PhysicsSystem& operator=(PhysicsSystem&& other) noexcept // move assignment
	{
		std::swap(physics_world, other.physics_world);
		return *this;
	}
	
	template<PhysicsComponent T>
	void operator()(float dt, T& physics_component, Transform2D& transform)
	{
		glm::vec2 velocity{0.0f, 0.0f};

		float speed = 300.0f;

		if (input.is_key_down(Key::KEY_W))
			velocity.y = -1;
		if (input.is_key_down(Key::KEY_S))
			velocity.y = 1;
		if (input.is_key_down(Key::KEY_D))
			velocity.x = 1;
		if (input.is_key_down(Key::KEY_A))
			velocity.x = -1;

		auto normalized = velocity;

		auto length = glm::length(velocity);
		if (length != 0 and length != 1)
			normalized = glm::normalize(velocity);

		normalized.x *= speed * dt;
		normalized.y *= speed * dt;

		set_linear_velocity(physics_component, normalized);

		glm::vec2 position { glm::round(to_pixel(get_position(physics_component))) };
		transform.position.x = position.x;
		transform.position.y = position.y;

		//std::cout << "X: " << transform.position.x << " Y: " << transform.position.y << std::endl;
	}

	inline void update_physics()
	{
		this->physics_world->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
	}

	//TODO
	template <PhysicsComponent T>
	void add_physics_component(T& physics_component, float x, float y)
	{
		b2BodyDef body_def;

		body_def.type = static_cast<b2BodyType>(physics_component.body_type);
		body_def.position.Set(x, y);
		body_def.angle = 0;

		b2Body* body = this->physics_world->CreateBody(&body_def);

		//TODO
		b2CircleShape circle_shape;

		circle_shape.m_radius = 0.25f;
		circle_shape.m_p.Set(0, 0);

		b2FixtureDef fixture_def;
		fixture_def.density = 5.0f;
		fixture_def.shape = &circle_shape;
		fixture_def.friction = 0.0f;

		body->CreateFixture(&fixture_def);

		auto b = static_cast<b2Body*>(physics_component.body);
		physics_component.body = body;
	}
	glm::vec2 to_world(glm::vec2 pixel_position)
	{
		return glm::vec2{ pixel_position.x * PIXELS_PER_METER, pixel_position.x * PIXELS_PER_METER };
	}
	float to_world_scalar(float scalar)
	{
		static_cast<float>(scalar * PIXELS_PER_METER);
	}
	glm::vec2 to_pixel(glm::vec2 world_position)
	{
		return glm::vec2{ world_position.x / PIXELS_PER_METER, world_position.y / PIXELS_PER_METER };
	}
	float to_pixel_scalar(float scalar)
	{
		return static_cast<float>(scalar / PIXELS_PER_METER);
	}
};

#endif