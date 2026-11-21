#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Animation.h"
#include "Backup.h"
#include "Menu.h"

#include "mini_game.h"
#include "AssetManager.h"


//new
#include "Clickable.h"
#include "Scene.h"
#include "Constants.h"



class Game {
private:
	sf::Sprite center;
	MiniGame game_ev;
private:
	//window and ralsei
	sf::RenderWindow window;
	bool fullscreen = false;

	//main visual part
	sf::View main_view; 
	sf::Sprite background;

	//player
	Player player;
	Animation anim;
	Backup backup;

	//menu
	Menu menu_;
	sf::Text menu_guide;
	bool isKeyPressed = false;
	bool levelUpState = false;
	bool isFullscreen = false;

	//audio
	sf::Music theme;
	float ralseiGroundOffset = 0.f;

//new part
	AssetManager assets;
	sf::Clock clock;
	Scene game_scene;
public:

	Game();

	bool run();
	void render();
	void ResizeView(const sf::RenderWindow& window, sf::View& view);


	void initSprites();
	void loadTextures();

//new 
	void update(float dt, sf::RenderWindow* window);
	void handleClick(sf::Event& ev);
	void toggleFullScreen();
	void handleResize();
	void handleEvents(sf::Event& ev);
	~Game();
};