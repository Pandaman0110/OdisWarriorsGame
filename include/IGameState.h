#ifndef IGAMESTATE_H
#define IGAMESTATE_H

#include <iostream>
#include <memory>

class GameStateManager;

class IGameState
{
protected:
	std::shared_ptr<GameStateManager> game_state_manager;
public:
	IGameState() {};
	IGameState(std::shared_ptr<GameStateManager> game_state_manager)
	{
		this->game_state_manager = game_state_manager;
	};

	virtual void update(float dt) = 0;
	virtual void draw(float dt) = 0;
	virtual void leave() = 0;
	virtual void enter() = 0;
};

#endif // IGAMESTATE_H