#include <iostream>
#include <memory>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include "Game.h"
#include "GameStates.h"

using namespace OdisEngine;

Window window { 1920, 1080, "OdisEngineWarriorsGame", false, RenderAPI::OpenGL };
ResourceManager resource_manager{};
Renderer renderer{ window, resource_manager };
Input input{ window };
Timer timer{};
GameStateManager game_state_manager{};

int main()
{
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window.get_window_handle(), true);
	ImGui_ImplOpenGL3_Init();

	game_state_manager.change_state(std::make_unique<GameState::MainMenu>());

	while (!window.should_close())
	{
		timer.update();
		input.poll_inputs(timer.get_delta_time());
		window.poll();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (input.is_key_pressed(Key::KEY_ESCAPE))
			break;

		game_state_manager.update(timer.get_delta_time());

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		window.swap_buffers();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	window.terminate();

	return 0;
}