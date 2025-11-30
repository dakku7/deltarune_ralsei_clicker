#pragma once
#include "SFML/Graphics.hpp"
#include "AssetManager.h"
#include "Player.h"

class Button {
private:
	sf::Sprite button;
	TextureID id;
	TextureID id_light;

	AssetManager* ass_mgr;
public:
	Button(TextureID button_tex, TextureID button_tex_light, AssetManager* asset);
	void initSprite();
	void buttonHover(Player& p, sf::RenderWindow& window);
	sf::Sprite& getSprite();
	void setPosition(sf::Vector2f& pos);
};