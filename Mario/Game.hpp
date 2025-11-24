#pragma once
#include "Libraries.hpp"
#include "Physics.hpp"
//Game class that instantiates the functions and variables needed
class Game {
public:
	Game();
	~Game(); // Destructor to delete physics
	void run();

private:
	void update();
	void render();

	Physics *physics;
	sf::RenderWindow window;
	sf::Texture texture;
	std::optional<sf::Sprite> sprite;
	sf::Music music;
	bool jumpHeld = false;
};