#pragma once
#include "SFML//Graphics.hpp"
#include "SFML/Audio.hpp"

class Options {
private:
	sf::Font font;

private:
//new layer of options
	sf::RectangleShape overlay;
	sf::Text opt_text;
//main visual part
	sf::Sprite button_options[3];
	sf::Text button_options_text[3];
	sf::Texture button_options_tex;
	sf::Texture button_options_light_tex;
	sf::Texture back_button_tex;
	sf::Sprite back_button;
	sf::Texture back_button_light;
	sf::Texture back_button_heart;
//desc of option
	sf::Sprite description;
	sf::Texture description_tex;
//sprite of mini ralsei to talk 
	sf::Sprite ralsei_mini;
	sf::Texture ralsei_mini_tex;
	sf::Texture ralsei_mini_blushy;
	sf::Texture ralsei_mini_sad;
//text on buttons
	sf::Text text_button[3];
//heart on chosen option 
	sf::Sprite heart;
	sf::Texture heart_tex;
//dialogue text
	sf::Text dialogue;
	
//bool variables 
	bool activeOpt;
	bool isHeartChosen;

	int button_count = 3;
	sf::Music click;
	
public:
	Options();

	void check_action(sf::RenderWindow& window, sf::Event& ev);
	void light_up_button_hover(sf::RenderWindow& window, sf::Sprite* button);
	void light_up_button(sf::RenderWindow& window, sf::Sprite& button);
	void arrowControl_opt(sf::RenderWindow& window, sf::Event& ev);
	void draw(sf::RenderWindow& window);
	~Options();
};