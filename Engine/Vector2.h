#ifndef VECTOR2_HEADER
#define VECTOR2_HEADER

class Vector2 {
public:
	float y;
	float x;
	Vector2(float x, float y) {
		this->x = x;
		this->y = y;
	}
	Vector2() {
		this->x = 0;
		this->y = 0;
	}
};
#endif