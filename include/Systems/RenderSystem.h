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
		auto &font = resource_manager->load_font("ebg_r.ttf", "my_font", 48);
		renderer->set_font(font);
	};

	void operator()(float dt, Transform2D& transform)
	{
		renderer->draw_rect(glm::ivec2{ 200, 200 }, glm::ivec2{ 200, 200 }, Color{ 0.5f, 0.2f, 0.2f });

		auto &text = resource_manager->load_texture("assets/textures/cat_textures/catgreyidle.png", "cat", true);
		renderer->draw_texture(text, transform.position, transform.rotation);

		renderer->draw_text("Hello world", glm::vec2{ 350, 200 });
	}

};

#endif