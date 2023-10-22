#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "Components.h"
#include "Game.h"

using namespace OdisEngine;

class RenderSystem
{
private:

public:
	RenderSystem()
	{
	};

	void operator()(Transform2D& transform)
	{
		auto& text = resource_manager.load_texture("catgreyidle.png", true, "cat");
		renderer.draw_texture(text, {30, 30});
	}

};

#endif