#include "Game.hpp"
#include "Common.hpp"

//Run automatically when we create a game object
Game::Game() {
	window.create(sf::VideoMode({ 800, 600 }), "SFML window");
	window.setFramerateLimit(60);

	if (!texture.loadFromFile("Assets/Graphics/lebron.jpg"))
		throw std::runtime_error("Failed to load texture");
														
	sprite.emplace(texture);
	sprite->setOrigin(sf::Vector2f(texture.getSize().x / 2.f, texture.getSize().y / 2.f));
}

//Update the state of the game
void Game::update() {
	// Handle window events (compatible with SFML < 2.6 and 2.6+)
	while (const std::optional<sf::Event> event = window.pollEvent()) {
		if (event->is<sf::Event::Closed>())
			window.close();
	}

	// Update physics
	physics.step(1.f / 60.f);

	b2Body* player = physics.getPlayer();
	if (!player) {
		// Player not created yet — skip sprite update
		return;
	}

	const b2Vec2& pos = player->GetPosition();
	sprite->setPosition(sf::Vector2f(pos.x * SCALE, pos.y * SCALE));
}

//Refresh the screen
void Game::render() {
	window.clear();
	if(sprite) window.draw(*sprite);
	window.display();
}

//Main loop
void Game::run() {
	while (window.isOpen()) {
		update();
		render();
	}
}