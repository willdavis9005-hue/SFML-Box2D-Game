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
private:
	b2World *world;
	b2Body *player;
	b2Body *floor;
};