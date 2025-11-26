#pragma once
#include "Libraries.hpp"

class Camera {
public:
	Camera();
	void update(const b2Vec2& playerPosition);
	sf::View &getView() const;
private:
	sf::View view;
};