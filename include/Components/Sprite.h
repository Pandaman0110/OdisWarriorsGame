#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>

#include "Texture2D.h"
#include "World.h"

struct Sprite
{
	Texture2D texture;

	inline void write(std::ostream& os)
	{
		os << get_component_name<Sprite>() << "\n";
		os << "ID: " << texture.ID << "\n";
		os << "Name: " << texture.name << "\n";
	}

};
#endif