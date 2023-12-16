#include "Engine/Engine.h"
#include "Engine/SquareObject.h"
#include "Engine/RoundObject.h"
#include "Engine/Input.h"

void Engine::InitEngine() {
	// This function is called before everything.
	SetTitle("Test Engine");
	camera.zoom = 15;
}
void Engine::OnQuit() {
	printf("Game quitted");
}
RoundObject player;
void Engine::Start() {
	// This function is called before any frame but after every initialization
	player = RoundObject("Player", Vector2(0, 10), 0.5f, Color(0, 149, 255), rand() % 360);
	SquareObject floor = SquareObject("Floor",Vector2(0, 0), Vector2(10, 1), Color(0, 0, 0), 0, Object::KINEMATIC);
}
void Engine::Update() {
	// Always set the position of the camera to player's position.
	camera.SetPosition(player.GetPosition());
	// Move player according to key pressed
	if (Input::Key::hold(KeyCode::A))
		player.AddVelocity(Vector2(-.5, 0));
	if (Input::Key::hold(KeyCode::D))
		player.AddVelocity(Vector2(.5, 0));
	if (Input::Key::press(KeyCode::W))
		player.SetVelocity(Vector2(player.GetVelocity().x, 5));
	/*if (Input::Key::press(KeyCode::RIGHT_ARROW))
		camera.SetPosition(Vector2(camera.position.x + 1, camera.position.y));
	if (Input::Key::press(KeyCode::LEFT_ARROW))
		camera.SetPosition(Vector2(camera.position.x - 1, camera.position.y));
	if (Input::Key::press(KeyCode::UP_ARROW))
		camera.SetPosition(Vector2(camera.position.x, camera.position.y + 1));
	if (Input::Key::press(KeyCode::DOWN_ARROW))
		camera.SetPosition(Vector2(camera.position.x, camera.position.y - 1));*/
	if (Input::Key::press(KeyCode::ESCAPE))
		Quit(0);
	// This function is called every frame
}
void Engine::UpdateObject(Object* object) {
	// This function is called aftered everytime each objects getting rendered
}