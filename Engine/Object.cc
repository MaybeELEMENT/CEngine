#include "Object.h"
#include "Engine.h"
extern Engine engine;

void Object::SetPosition(Vector2 position) {
	this->rawBody->SetTransform(b2Vec2(position.x, position.y), this->rawBody->GetAngle());
}
Vector2 Object::GetPosition() {
	return Vector2(this->rawBody->GetPosition().x, this->rawBody->GetPosition().y);
}
float Object::GetAngle() {
	return this->rawBody->GetAngle();
}
void Object::SetAngle(float angle) {
	return this->rawBody->SetTransform(this->rawBody->GetPosition(), angle);
}
void Object::AddForce(Vector2 velocity) {
	this->rawBody->ApplyForceToCenter(b2Vec2(velocity.x, velocity.y), true);
}
void Object::AddVelocity(Vector2 velocity) {
	this->rawBody->ApplyLinearImpulseToCenter(b2Vec2(velocity.x, velocity.y), true);
}
void Object::SetVelocity(Vector2 velocity) {
	this->rawBody->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
}
void Object::Destroy() {
	engine.world->DestroyBody(this->rawBody);
	engine.objects.erase(this->name);
}
Vector2 Object::GetVelocity() {
	b2Vec2 velo = this->rawBody->GetLinearVelocity();
	return Vector2(velo.x, velo.y);
}