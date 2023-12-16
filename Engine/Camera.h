#ifndef CAMERA_HEADER
#define CAMERA_HEADER
#include "Vector2.h"
class Camera {
public:
	float zoom = 5;
	Vector2 position = Vector2(0, 0);
	void Update();
	void SetPosition(Vector2 position) {
		this->position = position;
		Update();
	}
};
#endif