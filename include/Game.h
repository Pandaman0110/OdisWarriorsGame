#ifndef GAME_H
#define GAME_H

#include "OdisEngine.hpp"
#include "Timer.h"
#include "GameStateManager.h"

extern OdisEngine::Window window;
extern OdisEngine::ResourceManager resource_manager;
extern OdisEngine::Renderer renderer;
extern OdisEngine::Input input;

extern Timer timer;
extern GameStateManager game_state_manager;

#endif

