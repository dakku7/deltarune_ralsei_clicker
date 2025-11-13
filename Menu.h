#pragma once
#include "Player.h"


class Menu {
private:
	sf::RectangleShape overlay;
	sf::Text paused;
	sf::Font pause_font;
	sf::Sprite buttons[3];
	sf::Texture buttons_frame[3];
	sf::Text buttons_text[3];

	bool isActive;
public:
	 Menu();
	 void draw(Player& player, sf::RenderWindow& window);
	 void button_action(sf::RenderWindow& window, sf::Event& ev);
	~Menu();
};
