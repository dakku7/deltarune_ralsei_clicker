#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Animation.h"
#include "Backup.h"
#include "Button.h"
#include "Menu.h"



static const float VIEW_WIDTH = 800;
static const float VIEW_HEIGHT = 600;

class Game {
public:

private:
	//window and ralsei
	sf::RenderWindow window;
	sf::Sprite ralsei;
	sf::Texture ralsei_texture;
	

	//main visual part
	sf::View main_view; 
	sf::Sprite background;
	sf::Texture background_tex;
	//sf::Texture skins_tex[3];
	//sf::Texture skins_lock_tex[3];
	
	//player
	Player player;
	Animation anim;
	Backup backup;
	
	//skins
	std::map<int, sf::Texture> skins_tex_orig;     
	std::map<int, sf::Texture> skins_tex_button;
	sf::RectangleShape skins[3];

	//heart(lvl objects)
	sf::Sprite heartLvl;
	sf::Sprite heartEmpty;
	sf::Texture heart_texture;
	sf::Texture heartEmpty_texture;
	sf::IntRect rect_heart; // for animation of filling up

	//menu
	Menu menu_;
	sf::Text menu_guide;
public:

	Game();

	bool run();
	void render();
	void setPositionRalsei();
	sf::Vector2f GetRalseiPosition();
	void ResizeView(const sf::RenderWindow& window, sf::View& view);
	void checkWindowSize();
	void ButtonHover(sf::RectangleShape* skins, int count, sf::RenderWindow& window);
	void updateHeart(Player& player);
	void centerLvl(sf::Text& level_text);

	~Game();
};