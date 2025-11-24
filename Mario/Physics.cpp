#include "Physics.hpp"

//World setup and automatic deletion
Physics::Physics(float playerWidth, float playerHeight) {
	playerHeightPixels = playerHeight;
	world = new b2World(b2Vec2(0.f, 9.8f));
	//Floor (thin edge at bottom of window)
	b2BodyDef floorDef;
	floorDef.position.Set(0.f, 0.f); //Origin of world
	floor = world->CreateBody(&floorDef);
	b2EdgeShape edge;
	edge.SetTwoSided(b2Vec2(0.f, 600.f / SCALE), b2Vec2(800.f / SCALE, 600.f / SCALE));

	b2FixtureDef floorFix;
	floorFix.shape = &edge;
	floorFix.friction = 0.3f;
	floor->CreateFixture(&floorFix);
	//Player
	float playerHalfWidth = playerWidth / 2.f;
	float playerHalfHeight = playerHeight / 2.f;
	float playerStartY = 600.f - playerHalfHeight - 30.f;
	player = createBox(400.f, playerStartY, playerHalfWidth, playerHalfHeight, true);
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
	fixDef.density = dynamic ? .3f : 0.f;
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
bool Physics::isPlayerOnGround() {
	if (!player) return false;

	b2Vec2 pos = player->GetPosition();

	float playerHalfHeight = (playerHeightPixels / 2.f) / SCALE;
	float playerBottom = pos.y + playerHalfHeight;

	float floorY = 600.f / SCALE; // your edge is at this height

	return fabs(playerBottom - floorY) < 0.05f;
}

b2Body *Physics::getPlayer() { return player; }
b2Body *Physics::getFloor() { return floor; }