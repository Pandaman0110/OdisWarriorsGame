#include "Game.h"
#include "GameStates.h"

using namespace OdisEngine;

const std::string font_path{ "assets/fonts/" };

Window window { 1920, 1080, "OdisEngineWarriorsGame", false, RenderAPI::OpenGL };
ResourceManager resource_manager{ font_path };
Renderer renderer{ window, resource_manager };
Input input{ window };
Timer timer{};
GameStateManager game_state_manager{};


int main()
{



	game_state_manager.change_state(std::make_unique<GameState::CatGame>());

	while (!window.should_close())
	{
		timer.update();
		input.poll_inputs(timer.get_delta_time());
		window.poll();


		//.substr(0, 3)
		if (input.is_key_pressed(Key::KEY_ESCAPE))
			break;
		
		game_state_manager.update(timer.get_delta_time());

		window.swap_buffers();
	}

	window.terminate();

	return 0;
}