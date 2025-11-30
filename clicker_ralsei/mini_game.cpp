#include "mini_game.h"

MiniGame::MiniGame()
{
	overlay.setSize(sf::Vector2f(800,600));
	overlay.setFillColor(sf::Color(0, 0, 0, 240));

	frame_tex.loadFromFile("Textures\\Chapter1\\frame_game.png");
	frame.setTexture(frame_tex);
	heart_tex.loadFromFile("Textures\\Chapter1\\heart_mini_palyer.png");
	heart.setTexture(heart_tex);
	heart.setOrigin(heart.getGlobalBounds().width, heart.getGlobalBounds().height);
	background_tex.loadFromFile("Textures\\Chapter1\\background_game.png");
	background.setTexture(background_tex);
	background.setOrigin(background.getGlobalBounds().width / 2, background.getGlobalBounds().height / 2);

	frame.setOrigin(frame.getGlobalBounds().width / 2, frame.getGlobalBounds().height / 2);
	frame.setPosition(400,300+150-25);
	background.setPosition(frame.getPosition());
	modelPosition.x = frame.getPosition().x;
	modelPosition.y = frame.getPosition().y;

	groundY = background.getPosition().y - background.getGlobalBounds().height + 300 + 150 - 34;
	groundCheck();
}

void MiniGame::run() 
{
	isGameRunning = true;
}

void MiniGame::stop()
{
	isGameRunning = false;
}

void MiniGame::update(sf::Event& event)
{
	if (!isGameRunning) return;
	

	groundCheck();
	playerController(event);
	if (modelPosition.x <  background.getGlobalBounds().left + heart.getGlobalBounds().width) {
		modelPosition.x = background.getGlobalBounds().left + heart.getGlobalBounds().width;
	}

	if (modelPosition.x > background.getGlobalBounds().getPosition().x + background.getGlobalBounds().width) {
		modelPosition.x = background.getGlobalBounds().getPosition().x + background.getGlobalBounds().width;
	}

	heart.setPosition(modelPosition);
	
}

void MiniGame::draw(sf::RenderWindow& window)
{

	overlay.setSize(sf::Vector2f(window.getSize()));
	window.draw(overlay);

	window.draw(background);
	window.draw(frame);
	window.draw(heart);
}

void MiniGame::playerController(sf::Event& event)
{
	sf::Event ev;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
		isGameRunning = false;
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		modelPosition.x -= move_sp;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {

		modelPosition.x += move_sp;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		if (isOnGround) {
			velocityY += jumpPower;
			isOnGround = false;
		}
		jump = true;
	}
	velocityY += gravity;
	modelPosition.y += velocityY;

	// chec earth
	groundCheck();
	

	
}

void MiniGame::groundCheck()
{
	if (modelPosition.y >= groundY)
	{
		modelPosition.y = groundY;
		velocityY = 0;    
		isOnGround = true;
	}
}

bool MiniGame::isOpen()
{
	return isGameRunning;
}

MiniGame::~MiniGame()
{
}
