#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>

#include "Texture2D.h"
#include "World.h"

struct Sprite
{
	Texture texture;

	inline void write(std::ostream& os)
	{
		os << get_component_name<Sprite>() << "\n";
		os << "ID: " << texture.id << "\n";
	}

};

#endif