#ifndef CAMERA_H
#define CAMERA_H

#include "OdisMath.h"	

class Camera
{
public:
	Camera();

private:

};

class Camera2D : public Camera
{
public:	
	Camera2D();

	vec2 get_position() const { return position; };
	float get_orientation() const { return orientation; };

	inline void set_position(vec2 position) { this->position = position; };
	inline void set_orientation(float rotation) { this->orientation = rotation; };

	inline void move(vec2 velocity) { this->position += velocity; };
	inline void rotate(float rotation) { this->orientation += rotation; };

private:
	vec2 position;
	float orientation;
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
#endif