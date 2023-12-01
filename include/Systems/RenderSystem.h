#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <functional>

#include <Renderer.h>
#include <ResourceManager.h>

#include "Game.h"
#include "Components/Cat.h"
#include "Components/Transform.h"
#include "Color.h"
#include "ScriptManager.h"

using namespace OdisEngine;


class RenderSystem
{
private:

public:
	RenderSystem()
	{
		renderer->set_font(resource_manager->load_font("ebg_r.ttf", 24, "my_font"));
		resource_manager->load_texture("assets/textures/cat_textures/catgreyidle.png", true, "cat");

	};

	void operator()(float dt, Transform2D& transform)
	{
		renderer->clear(232.0f / 255.0f, 209.0f / 255.0f, 169.0f / 255.0f);

		renderer->draw_rect(glm::ivec2{ 200, 200 }, glm::ivec2{ 200, 200 }, Color{ 0.5f, 0.2f, 0.2f });

		renderer->draw_texture(resource_manager->get_texture("cat"), transform.position, transform.rotation);

		renderer->draw_text(std::to_string(timer->get_fps()), glm::vec2{10, 10}, Color{1.0f, 1.0f, 1.0f});

		renderer->draw_polygon(glm::ivec2{ 600, 700 }, 300, 6, glm::vec3{ 1.0f, 1.0f, 1.0f });
	}

};

#endif