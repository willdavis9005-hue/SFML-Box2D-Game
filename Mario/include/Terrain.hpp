#pragma once
#include <vector>
#include "Libraries.hpp"
#include "Common.hpp"

class Terrain {
public:
	Terrain(b2World* world);

	void generateInitialTerrain();
	void update(float playerx);
	const std::vector<b2Body*> &getChunks() const;
	std::vector<sf::RectangleShape> visuals;

private:
	b2World *world;
	std::vector<b2Body*> chunks;
	float lastChunkX = 0.f;
	b2Body* createChunk(float xPosition, float width);
};