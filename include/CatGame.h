#ifndef CATGAME_H
#define CATGAME_H

#include <iostream>
#include <string>
#include <memory>
#include <type_traits>
#include <vector>

#include <Camera.h>
#include <Input.h>
#include <Renderer.h>

#include "GameStateManager.h"
#include "World.h"
#include "Game.h"
#include "ScriptManager.h"
#include "CatGenerator.h"
#include "ClanGenerator.h"
#include "Components.h"
#include "Gui.h"

#include "Systems/RenderSystem.h"
#include "Systems/PhysicsSystem.h"

namespace GameState
{
	using namespace GameState;
	using namespace OdisEngine;

	class CatGame : public IGameState
	{
	private:
		World world{};
		Script* script;

		PhysicsSystem physics_system{};
		RenderSystem render_system{};

		CatGenerator cat_generator;
		ClanGenerator clan_generator;

		Entity me;
	public:

		CatGame()
		{
			auto me = world.create_entity();
			auto& body = world.assign<KinematicBody2D>(me);

			physics_system.add_physics_component(body, 1, 1);
			auto& cum = body.body;

			world.assign<Transform2D>(me);
			world.assign<Cat>(me, "CumStar");

			auto state = script_manager->new_lua_state("Warriors");


			cat_generator = { state };
			clan_generator = { state };

			auto cat = cat_generator();
			auto clan = clan_generator();

			logger->log(cat);
			logger->log(clan);

			OdisGui::Gui gui;

			//gui.

			std::cout << std::size(gui) << std::endl;
		}

		void update(float dt) override
		{


			physics_system.update_physics();

			//reference wrapper is for the functors
			world.update_system(std::function<void(float, KinematicBody2D&, Transform2D&)>{ std::ref(physics_system) }, dt);
			world.update_system(std::function<void(float, Transform2D&)>{ std::ref(render_system) }, dt);
		}

		void leave() override
		{
		}

		void enter() override
		{
		}
	};
}





#endif