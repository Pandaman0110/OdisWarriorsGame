#include "GameStates.h"

#include <iostream>
#include <string>
#include <memory>

#include <imgui.h>

#include "Game.h"
#include "GameStates.h"

#include "Components/Cat.h"
#include "Components/Transform.h"
#include "Components/Sprite.h"
#include "Components/PhysicsBodies.h"

using namespace GameState;
using namespace OdisEngine;

CatGame::CatGame()
{
	auto entity = world.create_entity();

	auto &body = world.assign<KinematicBody2D>(entity);


	physics_system.add_physics_component(body, 1, 1);

	auto& cum = body.body;

	world.assign<Transform2D>(entity);
	world.assign<Cat>(entity, "CumStar");


	//world.write_entities(std::cout);
}

void CatGame::update(float dt)
{

	renderer.clear(Color{0.9f, 0.6f, 0.7f});
	physics_system.update_physics();
	//reference wrapper is for the functors
	world.update_system(std::function<void(float, KinematicBody2D&, Transform2D&)>{ std::ref(physics_system) }, dt);
	world.update_system(std::function<void(float, Transform2D&)>{ std::ref(render_system) }, dt);
}

void CatGame::leave()
{
}

void CatGame::enter()
{
}