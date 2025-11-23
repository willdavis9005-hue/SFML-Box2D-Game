#include "Physics.hpp"

//World setup and automatic deletion
Physics::Physics() {
	world = new b2World(b2Vec2(0.f, 9.8f));
	player = createBox(400.f, 300.f, 32.f, 32.f, true);
	floor = createBox(400.f, 580.f, 400.f, 20.f, false);
}
Physics::~Physics() {
	delete world;
}
//Construct a physics step
b2Body *Physics::createBox(float x, float y, float halfWidth, float halfHeight, bool dynamic) {
	b2BodyDef bodyDef;
	bodyDef.type = dynamic ? b2_dynamicBody : b2_staticBody;
	bodyDef.position.Set(x / SCALE, y / SCALE);
	b2Body *body = world->CreateBody(&bodyDef);
	b2PolygonShape boxShape;
	boxShape.SetAsBox(halfWidth / SCALE, halfHeight / SCALE);
	b2FixtureDef fixDef;
	fixDef.shape = &boxShape;
	fixDef.density = dynamic ? 1.f : 0.f;
	fixDef.friction = 0.3f;
	fixDef.restitution = 0.2f;
	body->CreateFixture(&fixDef);
	return body;
}
void Physics::step(float dt) {
	int32 velocityIterations = 8;
	int32 positionIterations = 3;
	world->Step(dt, velocityIterations, positionIterations);
}

b2Body *Physics::getPlayer() { return player; }
b2Body *Physics::getFloor() { return floor; }