#include "Physics.hpp"

//Contact listener
Physics::ContactListener::ContactListener(Physics *physicsptr) : physics(physicsptr) {}
void Physics::ContactListener::BeginContact(b2Contact *contact) {
	uintptr_t a = contact->GetFixtureA()->GetUserData().pointer;
	uintptr_t b = contact->GetFixtureB()->GetUserData().pointer;

	if (a == 1 || b == 1) physics->grounded = true;
}
void Physics::ContactListener::EndContact(b2Contact* contact) {
	uintptr_t a = contact->GetFixtureA()->GetUserData().pointer;
	uintptr_t b = contact->GetFixtureB()->GetUserData().pointer;

	if (a == 1 || b == 1) physics->grounded = false;
}
//World setup and automatic deletion
Physics::Physics(float playerWidth, float playerHeight) : listener(this){
	playerHeightPixels = playerHeight;
	world = new b2World(b2Vec2(0.f, 9.8f));
	world->SetContactListener(&listener);
	//Floor (thin edge at bottom of window)
	b2BodyDef floorDef;
	floorDef.position.Set(0.f, 0.f); //Origin of world
	floor = world->CreateBody(&floorDef);
	b2EdgeShape edge;
	edge.SetTwoSided(b2Vec2(0.f, 600.f / SCALE), b2Vec2(800.f / SCALE, 600.f / SCALE));
	//Set user data to identify the floor fixture
	b2FixtureDef floorFix;
	floorFix.shape = &edge;
	floorFix.friction = 0.3f;
	b2Fixture* floorFixture = floor->CreateFixture(&floorFix);
	floorFixture->GetUserData().pointer = 2; // ID for floor
	//Player
	float playerHalfWidth = playerWidth / 2.f;
	float playerHalfHeight = playerHeight / 2.f;
	float playerStartY = 600.f - playerHalfHeight - 30.f;
	player = createBox(400.f, playerStartY, playerHalfWidth, playerHalfHeight, true);
	//Create foot sensor
	b2PolygonShape footShape;
	footShape.SetAsBox(
	(playerHalfWidth / SCALE) * .85f,
	.05f,
	b2Vec2(0.f, playerHalfHeight / SCALE),
	0.f
	);
	b2FixtureDef footFix;
	footFix.shape = &footShape;
	footFix.isSensor = true;
	footFix.userData.pointer = 1; //Identifier for foot sensor

	player->CreateFixture(&footFix);
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
	return grounded;
}

b2Body *Physics::getPlayer() { return player; }
b2Body *Physics::getFloor() { return floor; }