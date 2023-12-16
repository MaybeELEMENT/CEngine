#ifndef COLOR_HEADER
#define COLOR_HEADER
class Color {
public:
	int r = 0, g = 0, b = 0;
	float a = 1;
	Color(int r, int g, int b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}
	Color(int r, int g, int b, float a) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
	Color() {}
};
#endif