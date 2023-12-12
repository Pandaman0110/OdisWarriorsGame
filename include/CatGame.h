#ifndef CATGAME_H
#define CATGAME_H

#include <iostream>
#include <string>
#include <memory>
#include <type_traits>
#include <vector>
#include <fstream>

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
#include "Timer.h"
#include "Camera.h"
#include "ResourceManager.h"

#include "Systems/RenderSystem.h"
#include "Systems/TileMapRenderSystem.h"
#include "Systems/CameraSystem.h"
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
		CameraSystem camera_system{};
		RenderSystem render_system{};
		TileMapRenderSystem tile_map_render_system{&world};

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
			world.assign<Player>(me, PlayerNumbers::one);
			world.assign<Cat>(me, "CumStar");
			world.assign<Sprite>(me, resource_manager->load_texture("assets/textures/cat_textures/catgreyidle.png", "cat"));
			
			auto state = script_manager->new_lua_state("Warriors");

			cat_generator = { state };
			clan_generator = { state };

			auto cat = cat_generator();
			auto clan = clan_generator();

			logger->log(cat);
			logger->log(clan);

			OdisGui::Gui gui;

			//ileMap<uint8_t> tile_map{ {0, 1, 2, 1, 0, 0, 2, 1}, 4 };

			//tile_map.write_file("assets/data/forest.map");

			//auto test = TileMap<uint8_t>::load_file("assets/data/forest.map");

			//std::cout << test << "\n";

		}

		void update(float dt) override
		{
			physics_system.update_physics();

			renderer->clear(232.0f / 255.0f, 209.0f / 255.0f, 169.0f / 255.0f);
			//renderer->draw_rect(glm::ivec2{ 200, 200 }, glm::ivec2{ 200, 200 }, Color{ 0.5f, 0.2f, 0.2f });
			renderer->draw_text(std::to_string(timer->get_fps()), glm::vec2{ 10, 10 }, Color{ 0.0f, 0.0f, 0.0f });
			//renderer->draw_polygon(glm::ivec2{ 0, 0 }, 100, 6, glm::vec3{ 1.0f, 1.0f, 1.0f });

			world.update_system(std::function<void(float, KinematicBody2D&, Transform2D&)>{ std::ref(physics_system) }, dt);
			world.update_system(std::function<void(float, Player&, Sprite&, Transform2D&)>{ std::ref(camera_system) }, dt);
			world.update_system(std::function<void(float, TileMap<uint8_t>&)>{ std::ref(tile_map_render_system) }, dt);
			world.update_system(std::function<void(float, Sprite&, Transform2D&)>{ std::ref(render_system) }, dt);

			std::cout << *logger;

			renderer->flush();
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