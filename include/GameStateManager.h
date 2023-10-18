#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <stack>
#include <memory>

#include "IGameState.h"

class GameStateManager
{
private:
	std::stack<std::unique_ptr<IGameState>> gamestate_stack;

public:
	GameStateManager() {};
	~GameStateManager() {};

	void update(float dt) const;
	void draw(float dt) const;
	void change_state(std::unique_ptr<IGameState> gamestate);
};

#endif // GAMESTATEMANAGER_H