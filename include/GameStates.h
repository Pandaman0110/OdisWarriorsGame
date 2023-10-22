#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "GameStateManager.h"
#include "World.h"
#include "RenderSystem.h"

namespace GameState
{
	class MainMenu : public IGameState
	{
	private:
		World world{};

		RenderSystem render_system{};
	public:
		MainMenu();

		void update(float dt) override;
		void leave() override;
		void enter() override;
	};
}

#endif 
