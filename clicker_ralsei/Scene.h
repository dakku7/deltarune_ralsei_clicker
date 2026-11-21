#pragma once
#include <functional>
#include "Clickable.h"
#include "SFML/Graphics.hpp"
#include "Player.h"
#include <vector>

#include "Animation+.h"
#include "Ralsei.h"
#include "Button.h"
#include "Tree.h"
#include "Heart.h"

class Scene {
private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::vector<Clickable*> clickables;

	AssetManager& ass_mgr;
	Player& player;
	Ralsei* ralsei_ptr = nullptr;
	std::function<void()> update_buttons;
	sf::Text click_text;
public:
	Scene(AssetManager& assets, Player& p);
	void init(const sf::Vector2u& size);

	void initMainCharacter(const sf::Vector2u& size);
	void initBackground();
	void initButtons();
	void initText();
	void initLvlSprite();

	void addEntity(std::unique_ptr<Entity> target);
	void addClickable(Clickable* target);

	void update(float dt, sf::RenderWindow& window);
	void render(sf::RenderWindow*window);

	void handleClick(sf::Vector2f& pos, Player& p, sf::RenderWindow& window, sf::Event& ev);
	void handleLvlChange();

	void setUpdateButtonFunc(std::function<void()> f);
	void resetSkin();

};