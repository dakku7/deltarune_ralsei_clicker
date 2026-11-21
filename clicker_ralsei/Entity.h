#pragma once
#include "SFML/Graphics.hpp"

class Player;

class Entity {
public:
	Entity() {

	}
	virtual void update(float dt) {}
	virtual void render(sf::RenderTarget* target) {}
	virtual sf::Vector2f getPosition() { return sf::Vector2f(); }
	virtual void syncWithPlayer(Player& p) {}

};