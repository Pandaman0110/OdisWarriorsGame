#ifndef GAME_H
#define GAME_H

//#include "OdisEngine.hpp"
//#include "Timer.h"
//#include "GameStateManager.h"
//#include "ScriptManager.h"

namespace OdisEngine
{
	class Window;
	class ResourceManager;
	class Renderer;
	class Input;
}

class Timer;
class GameStateManager;
class ScriptManager;

extern std::unique_ptr<OdisEngine::Window> window;
extern std::unique_ptr<OdisEngine::ResourceManager> resource_manager;
extern std::unique_ptr<OdisEngine::Renderer> renderer;
extern std::unique_ptr<OdisEngine::Input> input;
extern std::unique_ptr<Timer> timer;
extern std::unique_ptr<GameStateManager> game_state_manager;
extern std::unique_ptr<ScriptManager> script_manager;

template <std::integral I, class... Args>
decltype(auto) get(Args&&... args) {
	return std::get<I>(std::forward_as_tuple(args...));
}

#endif

