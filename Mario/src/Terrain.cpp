#include "Terrain.hpp"

Terrain::Terrain(b2World *world) : world(world) {}


//Create Chunk
b2Body *Terrain::createChunk(float x, float width) {
	b2BodyDef def;
	def.position.Set(x / SCALE, 580.f / SCALE);
	b2Body *body = world->CreateBody(&def);
	b2PolygonShape shape;
	shape.SetAsBox(width / 2.f / SCALE, 10.f / SCALE);
	body->CreateFixture(&shape, 0.f);
	//Visual rectangle
	sf::RectangleShape rect;
	rect.setSize({ width, 20.f });
	rect.setOrigin(sf::Vector2f(width / 2.f, 10.f));
	rect.setPosition(sf::Vector2f(x, 580.f));
	rect.setFillColor(sf::Color::Green);
	visuals.push_back(rect);

	return body;
}
//Initial terrain
void Terrain::generateInitialTerrain() {
	chunks.push_back(createChunk(400.f, 900.f));
	lastChunkX = 400.f + 450.f;
}
void Terrain::update(float playerX) {
	while (lastChunkX - playerX < 1000.f) {
		float width = 250.f;
		chunks.push_back(createChunk(lastChunkX + width / 2.f, width));
		lastChunkX += width;
	}
}
//Getters
const std::vector<b2Body*> &Terrain::getChunks() const {
	return chunks;
}