#include "Input.h"
#include "Engine.h"
#include <GLFW/glfw3.h>
extern Engine engine;
KeyCode Input::currentKey = KeyCode::NONEKEY;
MouseCode Input::currentMouse = MouseCode::NONEMOUSE;
InputStatus Input::mouseStatus = InputStatus::NONE; 
InputStatus Input::keyStatus = InputStatus::NONE;
Vector2 Input::Mouse::position = Vector2(0, 0);

bool Input::Key::press(KeyCode code) {
	return Input::currentKey == code && Input::keyStatus == InputStatus::PRESS;
}
bool Input::Key::hold(KeyCode code) {
	return Input::currentKey == code && Input::keyStatus == InputStatus::HOLD;
}
bool Input::Key::release(KeyCode code) {
	return Input::currentKey == code && Input::keyStatus == InputStatus::RELEASE;
}

bool Input::Mouse::press(MouseCode code) {
	return Input::currentMouse == code && Input::mouseStatus == InputStatus::PRESS;
}
bool Input::Mouse::hold(MouseCode code) {
	return Input::currentMouse == code && Input::mouseStatus == InputStatus::HOLD;
}
bool Input::Mouse::release(MouseCode code) {
	return Input::currentMouse == code && Input::mouseStatus == InputStatus::RELEASE;
}