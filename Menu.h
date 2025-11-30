#pragma once
#include "Player.h"
#include "Options.h"

class Options;

class Menu {
private:
	sf::RectangleShape overlay;
	sf::Text paused;
	sf::Font pause_font;
	sf::Sprite buttons[3];
	sf::Texture buttons_frame[3];
	sf::Texture buttons_frame_lightened;
	sf::Text buttons_text[3];
	sf::Texture back_buttons_tex;
	sf::Sprite back_buttons;

	sf::Sprite top_layer;
	sf::Sprite bottom_layer;
	
	sf::Texture top_layer_tex;
	sf::Texture bottom_layer_tex;
	sf::Clock anim_clock;
	const float layer_speed = 30.f;
	bool isActive;

	sf::Vector2f top_offset{ 0.f, 0.f };
	sf::Vector2f bottom_offset{ 0.f, 0.f };

	sf::Sprite heart;
	sf::Texture heart_tex;
	bool isHeartActive;
	int button_count = 0;

	Options options;
	sf::Music click;
public:
	 Menu();
	 void draw(Player& player, sf::RenderWindow& window);
	 void button_action(sf::RenderWindow& window, sf::Event& ev);
	
	 void startAnim();
	 void updateAnim();
	 void drawAnim(sf::RenderWindow* window);
	 void checkHoverButton(sf::RenderWindow& window, sf::Sprite buttons[3]);
	 void hoverButton(sf::RenderWindow& window, sf::Sprite& button);
	 void arrowControl(sf::RenderWindow& window, sf::Event& ev);
	 ~Menu();
};
