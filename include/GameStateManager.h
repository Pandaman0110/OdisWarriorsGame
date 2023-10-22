#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <stack>
#include <memory>

class GameStateManager;

class IGameState
{
protected:
public:
	IGameState() {};

	virtual void update(float dt) = 0;
	virtual void leave() = 0;
	virtual void enter() = 0;
};

class GameStateManager
{
private:
	std::stack<std::unique_ptr<IGameState>> gamestate_stack;

public:
	GameStateManager() {};
	~GameStateManager() {};

	inline void update(float dt)
	{
		gamestate_stack.top()->update(dt);
	}

	inline void change_state(std::unique_ptr<IGameState> gamestate)
	{
		if (!gamestate_stack.empty())
		{
			gamestate_stack.top()->leave();
			gamestate_stack.pop();
		}
		gamestate->enter();
		gamestate_stack.push(std::move(gamestate));
	}
};

#endif // GAMESTATEMANAGER_H