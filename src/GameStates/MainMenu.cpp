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


void cum_shit(Transform2D& transform) {};

MainMenu::MainMenu()
{
	auto entity = world.create_entity();
	world.assign<Transform2D>(entity);
}

void MainMenu::update(float dt)
{
	world.update_system(std::function(cum_shit));
}

void MainMenu::leave()
{

}

void MainMenu::enter()
{

}

///////////////////////////////////