#include "GameStates.h"

#include <iostream>
#include <string>
#include <memory>
#include <type_traits>

#include <Input.h>

#include "Game.h"

#include "Components/Cat.h"
#include "Components/Transform.h"
#include "Components/Sprite.h"
#include "Components/PhysicsBodies.h"

#include "ScriptManager.h"

using namespace GameState;
using namespace OdisEngine;

Script* script;

CatGame::CatGame()
{
	auto entity = world.create_entity();

	auto &body = world.assign<KinematicBody2D>(entity);

	physics_system.add_physics_component(body, 1, 1);

	auto& cum = body.body;

	world.assign<Transform2D>(entity);
	world.assign<Cat>(entity, "CumStar");

	auto state = script_manager->new_lua_state("cum_state");
	script = script_manager->new_script("script/test.lua", state, "script");

	state->open_libraries(sol::lib::base);

}

void CatGame::update(float dt)
{
	renderer->clear(232.0f/255.0f, 209.0f / 255.0f, 169.0f / 255.0f);

	if (input->is_key_pressed(Key::KEY_F))
		script->execute();

	if (input->is_key_pressed(Key::KEY_B))
		std::cout << "key" << std::endl;

	if (input->is_key_pressed(Key::MOUSE_BUTTON_1))
		std::cout << "mouse" << std::endl;

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