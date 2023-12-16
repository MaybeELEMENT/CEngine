#include "Engine.h"
#include "SquareObject.h"
#include <typeinfo>
#include <GLFW/glfw3.h>
#include "Input.h"
#define ENGINEAPI
Engine engine;
Engine::Engine() {
	
}
ENGINEAPI void Reshape(GLFWwindow*, int w, int h)
{
	engine.width = w;
	engine.height = h > 0 ? h : 1;

	// glViewport(0, 0, engine.width, engine.height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float aspect = float(engine.width) / float(engine.height);
	if (engine.width >= engine.height)
	{
		glOrtho(-engine.camera.zoom * aspect + engine.camera.position.x, 
				engine.camera.zoom * aspect + engine.camera.position.x, 
				-engine.camera.zoom + engine.camera.position.y,
				engine.camera.zoom + engine.camera.position.y, -1.0, 1.0);
	}
	else
	{
		glOrtho(-engine.camera.zoom + engine.camera.position.x, 
				engine.camera.zoom + engine.camera.position.x, 
				-engine.camera.zoom / aspect + engine.camera.position.y, 
				engine.camera.zoom / aspect + engine.camera.position.y, -1.0, 1.0);
	}
	glMatrixMode(GL_MODELVIEW);
}
ENGINEAPI void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS) {
		Input::mouseStatus = InputStatus::PRESS;
	}
	else if (action == GLFW_RELEASE) {
		Input::mouseStatus = InputStatus::RELEASE;
	}
	Input::currentMouse = (MouseCode)button;
}
ENGINEAPI void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		Input::keyStatus = InputStatus::PRESS;
	}
	else if (action == GLFW_RELEASE) {
		Input::keyStatus = InputStatus::RELEASE;
	}
	Input::currentKey = (KeyCode) key;
}

int exitcode = 0;
void Engine::Quit(int exitCode) {
	exitcode = exitCode;
	glfwSetWindowShouldClose(engine.gameWin, GL_TRUE);
}
void Engine::SetTitle(std::string title) {
	this->title = title;
	if(this->gameWin != nullptr && this->gameWin != NULL)
		glfwSetWindowTitle(this->gameWin, this->title.c_str());
}

std::string Engine::GetTitle() {
	return this->title;
}
Object& Engine::GetObject(std::string name) {

}
void error_callback(int error, const char* msg) {
	printf("ERROR %d: %s", error, msg);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
int main() {
	engine.InitEngine();
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
	{
		printf("Failed to initialize GLFW\n");
		return -1;
	}
	engine.gameWin = glfwCreateWindow(engine.width, engine.height, engine.GetTitle().c_str(), NULL, NULL);
	if (engine.gameWin == NULL)
	{
		printf("Failed to create GLFW Window.\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(engine.gameWin);
	glfwSwapInterval(1);
	glfwSetWindowSizeCallback(engine.gameWin, Reshape);
	glfwSetFramebufferSizeCallback(engine.gameWin, framebuffer_size_callback);
	/*glfwSetKeyCallback(engine.gameWin, Keyboard);*/

	float xscale, yscale;
	glfwGetWindowContentScale(engine.gameWin, &xscale, &yscale);
	float uiScale = xscale;
	engine.world = new b2World(b2Vec2(0, engine.gravity));
	Reshape(engine.gameWin, engine.width, engine.height);
	engine.Start();
	glMatrixMode(GL_MODELVIEW);
	double previousTime = glfwGetTime();
	int frameCount = 0;
	glfwSetKeyCallback(engine.gameWin, key_callback);
	glfwSetMouseButtonCallback(engine.gameWin, mouse_button_callback);

	while (!glfwWindowShouldClose(engine.gameWin))
	{
		if (Input::keyStatus == InputStatus::PRESS) {
			Input::keyStatus = InputStatus::HOLD;
		}
		if (Input::mouseStatus == InputStatus::PRESS) {
			Input::mouseStatus = InputStatus::HOLD;
		}
		glfwPollEvents();
		engine.Update();

		if (Input::keyStatus == InputStatus::RELEASE) {
			Input::keyStatus = InputStatus::NONE;
			Input::currentKey = KeyCode::NONEKEY;
		}
		if (Input::mouseStatus == InputStatus::RELEASE) {
			Input::mouseStatus = InputStatus::NONE;
			Input::currentMouse = MouseCode::NONEMOUSE;
		}
		/*double currentTime = glfwGetTime();
		frameCount++;
		if (currentTime - previousTime >= 1.0)
		{
			printf("\rFPS: %i  ", frameCount);

			frameCount = 0;
			previousTime = currentTime;
		}*/
		
		glClearColor(engine.backgroundColor.r / 255.f, engine.backgroundColor.g / 255.f, engine.backgroundColor.b / 255.f, engine.backgroundColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		
		engine.world->Step(engine.timeStep, 8, 3);
		std::map<std::string, std::unique_ptr<Object>>::iterator it;
		for (it = engine.objects.begin(); it != engine.objects.end(); it++)
		{
			it->second->Draw();
			engine.UpdateObject(it->second.get());
		}
		
		glfwSwapBuffers(engine.gameWin);
	}

	engine.OnQuit();
	glfwTerminate();
	return exitcode;
}