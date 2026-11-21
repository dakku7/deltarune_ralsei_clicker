#pragma once
#include <SFML/Graphics.hpp>
#include"Entity.h"
#include "AssetManager.h"

class Player;

class Heart : public Entity {
private:
	sf::Sprite sprite;
	sf::Sprite sprite_fill;
	sf::IntRect rect_heart; // for animation of filling up
	
	int lvl = 0;
	int height_fill = 0;
	sf::Text lvl_text;
	sf::Font font;
	
	
	AssetManager& ass_mgr;
public:
	Heart(AssetManager& assets);
	void init();
	void initTextures();
	void initSprites();

	void heartFillingUp();

	void syncWithPlayer(Player& p) override;
	void update(float dt) override;
	void render(sf::RenderTarget* target) override;
	sf::Vector2f getPosition() override;
};