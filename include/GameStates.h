#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "GameStateManager.h"
#include "World.h"

#include "Systems/RenderSystem.h"
#include "Systems/PhysicsSystem.h"

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

	class CatGame : public IGameState
	{
	private:
		World world{};

		PhysicsSystem physics_system{};
		RenderSystem render_system{};
	public:
		CatGame();

		void update(float dt) override;
		void leave() override;
		void enter() override;
	};

	class LevelEditor : public IGameState
	{
	private:
		World world{};

		RenderSystem render_system{};

	public:
		LevelEditor();

		void update(float dt) override;
		void leave() override;
		void enter() override;
	};
}

#endif 
