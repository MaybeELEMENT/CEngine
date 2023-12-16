#ifndef OBJECT_HEADER
#define OBJECT_HEADER
#include <box2d/box2d.h>
#include <GLFW/glfw3.h>
#include "Vector2.h"
#include <string>

class Object {
public:
	enum ObjectType {
		STATIC, DYNAMIC, KINEMATIC
	};
	b2Body* rawBody = nullptr;
	std::string name;
	ObjectType rigidType = ObjectType::DYNAMIC;
	void SetPosition(Vector2 position);
	void SetAngle(float angle);
	float GetAngle();
	Vector2 GetPosition();
	Object() {}
	void Destroy();
	void AddForce(Vector2 velocity);
	void SetVelocity(Vector2 velocity);
	void AddVelocity(Vector2 velocity);
	Vector2 GetVelocity();
	virtual void Draw() = 0;
};
#endif