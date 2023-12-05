#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include "World.h"

enum class PlayerNumbers : size_t
{
	one = 1,
	two,
	three,
	four
};

struct Player
{
	PlayerNumbers player_num;
};

inline std::ostream& operator <<(std::ostream& os, const PlayerNumbers& players)
{
	os << static_cast<int64_t>(players);
	return os;
}

inline std::ostream& operator <<(std::ostream& os, const Player& player)
{
	os << "Player Number: " << player.player_num;
	return os;
}

#endif
