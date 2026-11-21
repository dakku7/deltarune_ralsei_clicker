#pragma once
#include "SFML/Graphics.hpp"


class MiniGame {
private:

	sf::RectangleShape overlay;
	sf::Sprite frame;
	sf::Texture frame_tex;
	sf::Sprite heart;
	sf::Texture heart_tex;
	sf::Sprite background;
	sf::Texture background_tex;

	sf::Clock clock;

	sf::Sprite bullet;
	sf::Texture bullet_tex;
	
	sf::Texture overlay_tex;

	float velocityY = 0.f;
	float jumpPower = -9.f;    // вверх
	float gravity = 0.4f;
	float groundY;
	float move_sp = 5.f;

	sf::Vector2f modelPosition;
	bool isGameRunning = false;
	bool isOnGround = false;
	bool jump = false;

	
public:
	MiniGame();
	void run();
	void stop();
	void update(sf::Event& event);
	void draw(sf::RenderWindow& window);
	void playerController(sf::Event& event);
	void groundCheck();
	bool isOpen();
	~MiniGame();
};