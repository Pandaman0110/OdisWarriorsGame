#include <memory>

#include <utility/OdisMath.h>
#include <Renderer.h>
#include <Window.h>
#include <Input.h>
#include <Log.h>

#include "Game.h"
#include "Timer.h"
#include "GameStateManager.h"
#include "ScriptManager.h"

//#include "GameStates.h"
#include "CatGame.h"
#include "Config.h"

using namespace OdisEngine;

const std::string font_path{ "assets/fonts/" };
const std::string shader_path{ "lib/OdisEngine/shaders/" };

std::unique_ptr<Log> logger = std::make_unique<Log>();

std::unique_ptr<Window> window = std::make_unique<Window>(1920, 1080, "OdisEngineWarriorsGame", false, RenderAPI::opengl);
std::unique_ptr<ResourceManager> resource_manager = std::make_unique<ResourceManager>(font_path, shader_path);
std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>(window.get(), resource_manager.get(), ScaleMode::integer);
std::unique_ptr<Input> input = std::make_unique<Input>(window.get());
std::unique_ptr<Timer> timer = std::make_unique<Timer>();
std::unique_ptr<GameStateManager> game_state_manager = std::make_unique<GameStateManager>();
std::unique_ptr<ScriptManager> script_manager = std::make_unique<ScriptManager>();


int main()
{

	renderer->set_resolution(glm::ivec2{ 640, 360 });

	game_state_manager->change_state(std::make_unique<GameState::CatGame>());

	while (!window->should_close())
	{
		timer->update();
		input->poll_inputs(timer->get_delta_time());
		window->poll();


		//.substr(0, 3)
		if (input->is_key_pressed(Key::KEY_ESCAPE))
			break;
		
		game_state_manager->update(timer->get_delta_time());

		window->swap_buffers();
	}

	window->terminate();

	return 0;
}