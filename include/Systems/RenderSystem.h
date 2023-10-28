#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "Game.h"
#include "Components/Cat.h"
#include "Components/Transform.h"

using namespace OdisEngine;

class RenderSystem
{
private:
	int cum = 2;
public:
	RenderSystem()
	{
	};

	void operator()(float dt, Transform2D& transform)
	{
		auto &text = resource_manager.load_texture("assets/textures/cat_textures/catgreyidle.png", true, "cat");
		//auto& text = resource_manager.load_texture("assets/textures/cat_textures/catgreyidle.png", true, "cat");
		renderer.draw_texture(text, transform.position, transform.rotation);

		//std::cout << "X: " << transform.position.x << " Y: " << transform.position.y << std::endl;
	}

};

#endif