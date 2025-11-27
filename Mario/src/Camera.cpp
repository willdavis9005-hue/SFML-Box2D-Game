#include "Camera.hpp"

Camera::Camera() {
	view.setSize(sf::Vector2f(800.f, 600.f));
	view.setCenter(sf::Vector2f(400.f, 300.f));
}
void Camera::update(const b2Vec2 &playerPosition) {
    sf::Vector2f target(playerPosition.x * SCALE,
        playerPosition.y * SCALE);
    sf::Vector2f current = view.getCenter();

    float smooth = 0.1f; // smaller = smoother

    sf::Vector2f newCenter = current + (target - current) * smooth;
    view.setCenter(newCenter);
}
const sf::View &Camera::getView() const {
	return view;
}