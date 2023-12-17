#ifndef TILEMAP_RENDER_SYSTEM_H
#define TILEMAP_RENDER_SYSTEM_H

#include <Renderer.h>
#include <ResourceManager.h>

#include "Game.h"
#include "Components/TileMap.h"


using namespace OdisEngine;

class TileMapRenderSystem
{
private:
	Entity map;
	World* world = nullptr;
public:
	TileMapRenderSystem(World* world) : world(world)
	{
		map = world->create_entity();
		auto& tile_map = world->assign<TileMap<uint8_t>>(map, TileMap<uint8_t>::load_file("assets/data/forest.map"));

		tile_map.set(0, 0, 1);

		tile_map.resize(10, 10);

		world->get<TileMap<uint8_t>>(map).write_file("assets/data/forest.map");

		//print map
		/*
		for (int y = 0; y < tile_map.height(); y++)
		{
			for (int x = 0; x < tile_map.width(); x++)
			{
				std::cout << (int)tile_map.get(x, y) << " ";
			}
			std::cout << "\n";
		}
		*/

		resource_manager->load_texture("assets/textures/grass.png", "grass"); 
	}

	~TileMapRenderSystem()
	{
		//world->get<TileMap<uint8_t>>(map).write_file("assets/data/forest.map");
	}

	void operator()(float dt, TileMap<uint8_t>& tile_map)
	{
		
		for (int y = 0; y < tile_map.height(); y++)
		{
			for (int x = 0; x < tile_map.width(); x++)
			{
				const uint8_t val = tile_map.get(x, y);
				auto& texture = resource_manager->get_texture("grass");

				renderer->draw_texture(texture, glm::ivec2{ x * 32, y * 32 }, 0.0f);
			}
		}
		
	}

};

#endif
