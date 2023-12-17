#include <memory>
#include <numbers>

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

std::unique_ptr<Logger> logger = std::make_unique<Logger>();
std::unique_ptr<ResourceManager> resource_manager = std::make_unique<ResourceManager>(font_path, shader_path);

std::unique_ptr<Window> window = std::make_unique<Window>(1920, 1080, "OdisEngineWarriorsGame", true, true, true);
std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>(window.get(), ScaleMode::integer);
std::unique_ptr<Input> input = std::make_unique<Input>(window.get());
std::unique_ptr<Timer> timer = std::make_unique<Timer>();
std::unique_ptr<GameStateManager> game_state_manager = std::make_unique<GameStateManager>();
std::unique_ptr<ScriptManager> script_manager = std::make_unique<ScriptManager>();


int main()
{
	auto& buffer = resource_manager->load_framebuffer(640, 360, "game_buffer");

	logger->create("Warriors");

	game_state_manager->change_state(std::make_unique<GameState::CatGame>());

	timer->start();

	while (!window->should_close())
	{
		timer->update();
		input->poll_inputs(timer->get_delta_time());
		window->poll();
	
		if (input->is_key_pressed(Key::KEY_ESCAPE))
			break;
		
		renderer->begin_texture_mode(buffer);
		game_state_manager->update(timer->get_delta_time());
		renderer->end_texture_mode();

		renderer->draw_texture(buffer, { 0, 0 }, { 1, 1 }, 0.0f);

		window->swap_buffers();
	}

	//engine_shutdown:

	timer->stop();
	window->terminate();

	return 0;
}