#ifndef CATGAME_H
#define CATGAME_H

#include <iostream>
#include <string>
#include <memory>
#include <type_traits>
#include <vector>

#include <Input.h>

#include "GameStateManager.h"
#include "World.h"
#include "Game.h"
#include "ScriptManager.h"
#include "CatGenerator.h"
#include "ClanGenerator.h"
#include "Components/Cat.h"
#include "Components/Clan.h"
#include "Components/Transform.h"
#include "Components/Sprite.h"
#include "Components/PhysicsBodies.h"

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
	public:

		CatGame()
		{
			auto entity = world.create_entity();
			auto& body = world.assign<KinematicBody2D>(entity);

			physics_system.add_physics_component(body, 1, 1);
			auto& cum = body.body;

			world.assign<Transform2D>(entity);
			world.assign<Cat>(entity, "CumStar");

			auto state = script_manager->new_lua_state("Warriors");

			cat_generator = { state };
			clan_generator = { state };

			auto cat = cat_generator();
			auto clan = clan_generator();

			logger->log(cat);
			logger->log(clan);
		}

		void update(float dt) override
		{
			renderer->clear(232.0f / 255.0f, 209.0f / 255.0f, 169.0f / 255.0f);

			//if (input->is_key_pressed(Key::KEY_F))
				//script->execute();

			/*
			if (input->is_key_pressed(Key::KEY_B))
				std::cout << "key" << std::endl;

			if (input->is_key_pressed(Key::MOUSE_BUTTON_1))
				std::cout << "mouse" << std::endl;
				*/

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