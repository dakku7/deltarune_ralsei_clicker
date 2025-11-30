#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Animation.h"
#include "Backup.h"
#include "Menu.h"
#include "Tree.h"
#include "mini_game.h"
#include "AssetManager.h"
#include "Button.h"

static const float VIEW_WIDTH = 800;
static const float VIEW_HEIGHT = 600;

class Game {
private:
	sf::Sprite center;
	MiniGame game_ev;
private:
	//window and ralsei
	sf::RenderWindow window;
	sf::Sprite ralsei;

	//main visual part
	sf::View main_view; 
	sf::Sprite background;

	//player
	Player player;
	Animation anim;
	Backup backup;
	
	//skins
	std::map<int, sf::Texture> skins_tex_orig;     
	std::map<int, sf::Texture> skins_tex_button;
	Button butt_skin;
	sf::RectangleShape skins[3];
	

	//heart(lvl objects)
	sf::Sprite heartLvl;
	sf::Sprite heartEmpty;
	sf::IntRect rect_heart; // for animation of filling up

	//menu
	Menu menu_;
	sf::Text menu_guide;
	bool isKeyPressed = false;
	bool levelUpState = false;
	bool isFullscreen = false;
	
	Tree first_tree;
	Tree second_tree;

	//audio
	sf::Music theme;
	float ralseiGroundOffset = 0.f;

	AssetManager assets;
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
	void applyIntegerScaling();

	void drawFullScreen();

	void initSprites();
	void loadTextures();

	~Game();
};