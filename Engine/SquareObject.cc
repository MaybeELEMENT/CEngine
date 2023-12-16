#include "SquareObject.h"
#include "Engine.h"
#include <GLFW/glfw3.h>
#include "EngineException.h"
extern Engine engine;

SquareObject::SquareObject(std::string name, Vector2 position, Vector2 size, Color color, float angle, ObjectType type, float density, float friction) {
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

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(size.x, size.y);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = density;
	fixtureDef.friction = friction;

	rawBody->CreateFixture(&fixtureDef);
	engine.objects.emplace(name, std::make_unique<SquareObject>(*this));
}
void SquareObject::Draw() {
	if (!this->rawBody || !engine.world) {
		return;
	};
	glColor3f(this->color.r / 255.f, this->color.g / 255.f, this->color.b / 255.f);
	b2Fixture* fixture = rawBody->GetFixtureList();
	while (fixture) {
		b2Shape* shape = fixture->GetShape();

		if (shape->GetType() == b2Shape::e_polygon) {
			b2PolygonShape* polygonShape = static_cast<b2PolygonShape*>(shape);
			if (polygonShape) {
				int vertexCount = polygonShape->m_count;
				const b2Vec2* vertices = polygonShape->m_vertices;

				glBegin(GL_POLYGON);
				for (int i = 0; i < vertexCount; ++i) {
					// Map Box2D coordinates to your rendering coordinates
					b2Vec2 transformedVertex = rawBody->GetWorldPoint(vertices[i]);
					glVertex2f(transformedVertex.x, transformedVertex.y);
				}
				glEnd();
			}
		}
		fixture = fixture->GetNext();
	}
}