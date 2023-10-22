#include "GameStates.h"

#include <iostream>
#include <string>
#include <memory>

#include <imgui.h>

#include "Game.h"
#include "GameStates.h"

#include "Components.h"

using namespace GameState;
using namespace OdisEngine;

MainMenu::MainMenu()
{
	auto entity = world.create_entity();
	world.assign<Transform2D>(entity);
	world.assign<Sprite>(entity);
}

void MainMenu::update(float dt)
{
	renderer.clear(Color{});
	world.update_system(std::function{ render_system });
}

void MainMenu::leave()
{

}

void MainMenu::enter()
{

}

///////////////////////////////////