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

using namespace GameState;
using namespace OdisEngine;

CatGame::CatGame()
{
	auto entity = world.create_entity();
	world.assign<Transform2D>(entity);
	world.assign<Cat>(entity, "CumStar");


	//world.write_entities(std::cout);
}

void CatGame::update(float dt)
{
	renderer.clear(Color{.9, .6, .7});
	//world.update_system(std::function{ physics_system });
	world.update_system(std::function{ render_system });
}

void CatGame::leave()
{
}

void CatGame::enter()
{
}