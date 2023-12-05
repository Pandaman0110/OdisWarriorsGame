#ifndef CAMERA_SYSTEM_H
#define CAMERA_SYSTEM_H

#include <functional>

#include <Renderer.h>
#include <Window.h>

#include "Game.h"
#include "Components/Transform.h"
#include "Components/Player.h"
#include "ScriptManager.h"

using namespace OdisEngine;


class CameraSystem
{
private:

	Camera2d camera;
public:
	CameraSystem()
	{
	};

	void operator()(float dt, Player& player, Sprite& sprite, Transform2D& transform)
	{
		glm::vec2 offset{ window->get_window_size() / 2 };

		offset.x -= static_cast<float>(sprite.texture.w) / 2;
		offset.y -= static_cast<float>(sprite.texture.h) / 2;

		camera.offset(offset);
		camera.target(transform.position);
		camera.move(dt);

		renderer->set_camera(camera.position(), camera.rotation());
	}

};

#endif