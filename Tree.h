#pragma once
#include "SFML/Graphics.hpp"

class Tree {
private:
	sf::Sprite tree;
	sf::Texture tree_tex[20];

	sf::Clock clock;
	float dt;
	int currentFrame = 0;
	float frameTime = 0.15;
public:
	Tree();
	void anim();
	void draw(sf::RenderWindow& window);
	void setTree(sf::Vector2f pos);
	~Tree();
};