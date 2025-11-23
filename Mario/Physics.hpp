#pragma once
#include "Libraries.hpp"
#include "Common.hpp"

class Physics {
public:
	Physics();
	~Physics();

	void step(float dt);

	b2Body *createBox(float x, float y, float halfWidth, float halfHeight, bool dynamic);

	b2Body *getPlayer();
	b2Body *getFloor();
private:
	b2World *world;
	b2Body *player;
	b2Body *floor;
};