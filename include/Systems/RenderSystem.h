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

	};

	void operator()(float dt, Sprite& sprite, Transform2D& transform)
	{
		renderer->draw_texture(sprite.texture, transform.position, transform.rotation);
	}

};

#endif