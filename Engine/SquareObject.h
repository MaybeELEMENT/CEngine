#ifndef SQUAREOBJECT_HEADER
#define SQUAREOBJECT_HEADER
#include "Object.h"
#include "Color.h"
#include <string>
class SquareObject : public Object
{
public:
	Color color;
	Vector2 size;
	SquareObject(std::string name, Vector2 position, Vector2 size, Color color, float angle = 0, ObjectType type = ObjectType::DYNAMIC, float density = 1, float friction = 0.3f);
	SquareObject() {}
	void Draw() override;
};
#endif