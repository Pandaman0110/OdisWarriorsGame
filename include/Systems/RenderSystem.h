#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "Components.h"
#include "Game.h"

class RenderSystem
{
private:

public:
	RenderSystem()
	{

	};

	void operator()(Transform2D& transform)
	{
		renderer.clear({});
	}

};

#endif