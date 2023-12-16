#ifndef ROUNDOBJECT_HEADER
#define ROUNDOBJECT_HEADER
#include "Object.h"
#include "Color.h"
#include <string>
class RoundObject : public Object
{
	float radius = 5;
public:
	Color color;
	RoundObject(std::string name, Vector2 position, float radius, Color color, float angle = 0, ObjectType type = ObjectType::DYNAMIC, float density = 1, float friction = 0.3f);
	RoundObject() {}
	void Draw() override;
	float GetRadius();
	void SetRadius(float newRadius);
};
#endif