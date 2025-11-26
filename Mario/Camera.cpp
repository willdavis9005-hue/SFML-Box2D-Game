#include "Camera.hpp"

Camera::Camera() {
	view.reset(sf::FloatRect(0, 0, 800, 600));
}
void Camera::update(const b2Vec2 &playerPosition) {
	view.setCenter(b2Vec2(playerPosition.x * SCALE, playerPosition.y * SCALE));
}
const sf::View &Camera::getView() const {
	return view;
}