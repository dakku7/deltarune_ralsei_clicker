#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Text : public Entity {
private:
	sf::Text text;
public:
	Text();

	void update(float dt) override;
	void render(sf::RenderTarget* target) override;
	sf::Vector2f getPosition() override;
	void syncWithPlayer(Player& p) override;
};