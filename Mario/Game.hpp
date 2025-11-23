#pragma once
#include "Libraries.hpp"
#include "Physics.hpp"
//Game class that instantiates the functions and variables needed
class Game {
public:
	Game();
	void run();

private:
	void update();
	void render();

	sf::RenderWindow window;
	sf::Texture texture;
	std::optional<sf::Sprite> sprite;
	sf::Music music;

	Physics physics;
};