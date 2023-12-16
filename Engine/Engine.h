#ifndef ENGINE_HEADER
#define ENGINE_HEADER
#include <box2d/box2d.h>
#include <map>
#include <string>
#include <memory>
#include "Vector2.h"
#include "Object.h"
#include "Color.h"
#include "Camera.h"
#include "Platform.h"
class Engine {
	std::string title = "Game Window";
public:
	#ifdef _WIN32
	Platform platform = Platform::Windows32;
	#elif _WIN64
	Platform platform = Platform::Windows64;
	#elif __APPLE__ || __MACH__
	Platform platform = Platform::MacOS;
	#elif __linux__
	Platform platform = Platform::Linux;
	#elif __FreeBSD__
	Platform platform = Platform::FreeBSD;
	#elif __unix || __unix__
	Platform platform = Platform::Unix;
	#endif
	float timeStep = 1.0f / 60.0f;
	Camera camera;
	int width = 800, height = 700;
	int iterations = 10;
	float gravity = -9.8;
	b2World* world = nullptr;
	GLFWwindow* gameWin = NULL;
	Color backgroundColor = Color(239, 244, 249);
	std::map<std::string, std::unique_ptr<Object>> objects;
	void Quit(int exitCode = 0);
	void SetTitle(std::string name);
	Object& GetObject(std::string name);
	std::string GetTitle();

	// This function run every frame after input event
	void Update();

	// This function run before any frame
	void Start();
	
	// This function run before everything
	void InitEngine();

	// This function run when game are being closed
	void OnQuit();

	//This function run on every objects after they are being rendered
	void UpdateObject(Object* object);

	Engine();
};
#endif