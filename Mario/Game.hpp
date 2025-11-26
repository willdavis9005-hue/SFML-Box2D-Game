#pragma once
#include <optional>
#include "Libraries.hpp"
#include "Physics.hpp"
#include "Terrain.hpp"
#include "Camera.hpp"
//Game class that instantiates the functions and variables needed
class Game {
public:
	Game();
	~Game(); // Destructor to delete physics
	void run();

private:
	void update();
	void render();

	Camera camera;
	Terrain *terrain;
	Physics *physics;
	sf::RenderWindow window;
	sf::Texture texture;
	std::optional<sf::Sprite> sprite;
	sf::Music music;
	bool gameOver = false;
	bool jumpHeld = false;
};