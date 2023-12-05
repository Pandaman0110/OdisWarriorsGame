#ifndef CAMERA_H
#define CAMERA_H

#include <concepts>
#include <math.h>
#include <type_traits>
#include <utility>

#include "utility/OdisMath.h"	

namespace OdisEngine
{
	constexpr float max_camera_speed = 10.0f;
	constexpr float min_camera_speed = 2.0f;

	class Camera
	{
	public:
		Camera() {};
		virtual ~Camera() = 0;
		
	};

	class Camera2d
	{
	private:
		glm::mat4 view;

		
		glm::vec2 tar{ 0, 0 };
		glm::vec2 pos{ 0, 0 };
		glm::vec2 off{ 0, 0 };

		float rot = 0.0f;
		float zoom = 1.0f;

		float speed = min_camera_speed;
		glm::vec2 velocity{ 0, 0 };
	public:
		Camera2d() {};

		template <IntVectorType T = glm::vec2>
		Camera2d(T position, T offset, float rotation, float zoom) : pos(position.x, position.y), off(offset.x, offset.y), rot(rotation), zoom(zoom)
		{
			
		}

		//projection.

		glm::vec2 position() const { return glm::vec2{ pos + -off }; };
		glm::vec2 offset() const { return glm::vec2{ off }; };
		float rotation() const { return rot; };

		void target(glm::vec2 target) { this->tar = target; };
		void offset(glm::vec2 offset) { this->off = offset; };
		void rotation(float rotation)  { this->rot = rotation; };

		void move(float dt) 
		{ 
			//glm::vec2 direction = tar - pos;

			//if (glm::length(direction) >= 1 and (pos.x != tar.x or pos.x != tar.y))
				//speed += glm::log(speed) * dt;

			//speed = glm::clamp(speed, min_camera_speed, max_camera_speed);

			//if (glm::length(direction) < 1)
			//	speed = 0;

			//velocity += direction * speed * dt;
			constexpr float lerp_speed = 0.05f;
			
			pos.x = std::lerp(pos.x, tar.x, lerp_speed);
			pos.y = std::lerp(pos.y, tar.y, lerp_speed);
		};

		void rotate(float rotation) { this->rot += rotation; };
	};


	/* TODO 3d
	class Camera3D : public Camera
	{
	public:
		Camera3D();

		vec3 getPosition() const { return position; };
		quat getOrientation() const { return rotation; };

		void setPosition(vec3 position) { this->position = position; };
		void setOrientation(quat rotation) { this->rotation = rotation; };

	private:
		vec3 position;
		quat orientation;


	};
	*/
}


#endif