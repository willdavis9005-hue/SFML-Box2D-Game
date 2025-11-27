#pragma once
#include "Libraries.hpp"
#include "Common.hpp"

class Camera {
public:
	Camera();
	void update(const b2Vec2& playerPosition);
	const sf::View& getView() const;
private:
	sf::View view;
};