#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "Game.h"
#include "Components/Cat.h"
#include "Components/Transform.h"

using namespace OdisEngine;

class RenderSystem
{
private:
public:
	RenderSystem()
	{
		auto &font = resource_manager.load_font("EBG_R.ttf", "my_font", 24);
		renderer.set_font(font);
	};

	void operator()(float dt, Transform2D& transform)
	{
		auto &text = resource_manager.load_texture("assets/textures/cat_textures/catgreyidle.png", "cat", true);
		renderer.draw_texture(text, transform.position, transform.rotation);
		
		renderer.draw_text("cum", vec2{ 20.0f, 20.0f }, 3);
	}

};

#endif