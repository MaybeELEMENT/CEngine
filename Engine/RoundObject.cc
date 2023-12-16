#include "RoundObject.h"
#include "Engine.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include "EngineException.h"
extern Engine engine;

RoundObject::RoundObject(std::string name, Vector2 position, float radius, Color color, float angle, ObjectType type, float density, float friction) {
	if(engine.objects.find(name) != engine.objects.end()) 
		throw EngineException("Object with name '" + name + "' already exists.");	
	b2BodyDef bodyDef;
	this->name = name;
	switch (type) {
	case ObjectType::STATIC:
		bodyDef.type = b2_staticBody;
		break;
	case ObjectType::KINEMATIC:
		bodyDef.type = b2_kinematicBody;
		break;
	case ObjectType::DYNAMIC:
		bodyDef.type = b2_dynamicBody;
		break;
	}
	this->color = color;
	bodyDef.position.Set(position.x, position.y);
	rawBody = engine.world->CreateBody(&bodyDef);
	b2CircleShape circleShape;
	circleShape.m_radius = radius;
	this->radius = circleShape.m_radius;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = density;
	fixtureDef.friction = friction;
	rawBody->CreateFixture(&fixtureDef);
	engine.objects.emplace(name, std::make_unique<RoundObject>(*this));
}
void RoundObject::SetRadius(float newRadius) {
	static_cast<b2CircleShape*>(this->rawBody->GetFixtureList()->GetShape())->m_radius = newRadius;
	this->rawBody->ResetMassData();
}
float RoundObject::GetRadius() {
	return radius;
}
void RoundObject::Draw() {
	if (!this->rawBody || !engine.world) {
		return;
	};
	if (this->rawBody != nullptr) {
		const b2Vec2 center = this->rawBody->GetWorldPoint(static_cast<b2CircleShape*>(this->rawBody->GetFixtureList()->GetShape())->m_p);
		glColor3f(this->color.r / 255.f, this->color.g / 255.f, this->color.b / 255.f);
		glBegin(GL_TRIANGLE_FAN);
		for (int i = 0; i < 360; i++) {
			float angle = i * b2_pi / 180.0f + this->GetAngle();
			float x = center.x + radius * std::cos(angle);
			float y = center.y + radius * std::sin(angle);
			glVertex2f(x, y);
		}
		glEnd();
	}
}