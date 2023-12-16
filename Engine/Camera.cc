#include "Camera.h"
#include <GLFW/glfw3.h>
#include "Engine.h"
extern Engine engine;
void Camera::Update() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    float aspect = float(engine.width) / float(engine.height);
	if (engine.width >= engine.height)
	{
		// aspect >= 1, set the height from -1 to 1, with larger width
		glOrtho(-engine.camera.zoom * aspect + engine.camera.position.x, 
				engine.camera.zoom * aspect + engine.camera.position.x, 
				-engine.camera.zoom + engine.camera.position.y,
				engine.camera.zoom + engine.camera.position.y, -1.0, 1.0);
	}
	else
	{
		// aspect < 1, set the width to -1 to 1, with larger height
		glOrtho(-engine.camera.zoom + engine.camera.position.x, 
				engine.camera.zoom + engine.camera.position.x, 
				-engine.camera.zoom / aspect + engine.camera.position.y, 
				engine.camera.zoom / aspect + engine.camera.position.y, -1.0, 1.0);
	}
	glMatrixMode(GL_MODELVIEW);
}