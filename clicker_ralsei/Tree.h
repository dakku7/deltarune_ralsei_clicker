#pragma once
#include "SFML/Graphics.hpp"
#include "Animation+.h"
#include "AssetManager.h"
#include "Entity.h"
#include <vector>

class Tree : public Entity {
private:
	sf::Sprite tree;
	std::vector<sf::Texture*> frames_tex;

	sf::Clock clock;
	float dt;
	int currentFrame = 0;
	float frameTime = 0.15;

	std::unique_ptr<Anim> idleAnimation;
	AssetManager& ass_mgr;
public:
	Tree(AssetManager& manager);
	void initSprites(AssetManager& asset_mgr);
	void initAnimations();
	
	void update(float dt);
	void render(sf::RenderTarget* target);
	sf::Vector2f getPosition() override;
	void setPosition(sf::Vector2f pos);
	
	~Tree();
};