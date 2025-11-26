#pragma once
#include "Libraries.hpp"
#include "Common.hpp"

class Physics {
public:
	Physics(float playerWidth, float playerHeight);
	~Physics();

	b2Body *createBox(float x, float y, float halfWidth, float halfHeight, bool dynamic);
	void step(float dt);
	b2Body *getPlayer();
	b2Body *getFloor();

	bool isPlayerOnGround();
	float playerHeightPixels;

	bool grounded = false;

	class ContactListener : public b2ContactListener {
	public:
		Physics* physics;
		ContactListener(Physics* physicsPtr);

		void BeginContact(b2Contact* contact) override;
		void EndContact(b2Contact* contact) override;
	};
	ContactListener listener;
private:
	b2World *world;
	b2Body *player;
	b2Body *floor;
};