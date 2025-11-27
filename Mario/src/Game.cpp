#include "Game.hpp"
#include "Common.hpp"

// Run automatically when we create a game object
Game::Game() {
    window.create(sf::VideoMode({ 800, 600 }), "SFML window");
    window.setFramerateLimit(60);

    if (!texture.loadFromFile("Assets/Graphics/lebron.jpg"))
        throw std::runtime_error("Failed to load texture");

    physics = new Physics(texture.getSize().x, texture.getSize().y);
    terrain = new Terrain(physics->getWorld());
	terrain->generateInitialTerrain();

    sprite.emplace(texture);
    sprite->setOrigin(sf::Vector2f(texture.getSize().x / 2.f, texture.getSize().y / 2.f));
}

Game::~Game() {
    delete physics;
    delete terrain;
}

// Update the state of the game
void Game::update() {
    // Handle window events
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            window.close();
    }

    b2Body* player = physics->getPlayer();
    if(player) player->SetGravityScale(.9f);

    //Player controls
    if (player) {
        float moveSpeed = 10.f;
        float acceleration = 0.2f;
        float jumpForce = 200.f;

        // Horizontal movement
        b2Vec2 targetVel(0, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) targetVel.x -= 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) targetVel.x += 1;

        if (targetVel.Length() > 0) {
            targetVel.Normalize();
            targetVel.x *= moveSpeed;
        }

        // Smoothly interpolate horizontal velocity
        b2Vec2 vel = player->GetLinearVelocity();
        vel.x += (targetVel.x - vel.x) * acceleration;
        player->SetLinearVelocity(b2Vec2(vel.x, vel.y));

        // Jumping
        bool onGround = physics->isPlayerOnGround();
        bool jumpPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
        if (jumpPressed && !jumpHeld && onGround)
            player->ApplyLinearImpulseToCenter(b2Vec2(0, -jumpForce), true);
        jumpHeld = jumpPressed;

        // Update sprite position
        const b2Vec2& pos = player->GetPosition();
        sprite->setPosition(sf::Vector2f(pos.x * SCALE, pos.y * SCALE));

        // Optional: linear damping for natural deceleration
        player->SetLinearDamping(0.10f);

        //Update camera & terrain
        terrain->update(player->GetPosition().x * SCALE);
		camera.update(player->GetPosition());
    }

    // Step physics
    physics->step(1.f / 60.f);
}

// Refresh the screen
void Game::render() {
    window.clear();
    window.setView(camera.getView());
    if (sprite) window.draw(*sprite);
    for (auto& chunk : terrain->visuals)
        window.draw(chunk);
    window.display();
}

// Main loop
void Game::run() {
    while (window.isOpen()) {
        update();
        render();
    }
}
