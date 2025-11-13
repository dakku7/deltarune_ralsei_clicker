#include "Player.h"
#include "Game.h"



bool Player::click(sf::Sprite& ralsei, sf::RenderWindow& window, const sf::Event& event, sf::View main_view)
{
	if (event.mouseButton.button == sf::Mouse::Button::Left) {
		auto mouse_pos = sf::Mouse::getPosition(window);
		auto translated_pos = window.mapPixelToCoords(mouse_pos, main_view); 
		if (ralsei.getGlobalBounds().contains(translated_pos)) {
			// Rectangle-contains-point check
			int click_buf = 1 * clickPower;
			clickCount += click_buf;
			updateText(count_text, clickCount);
			return true;
		}
		else return false;
		
	}
	else return false;
}



bool Player::click(sf::Sprite& ralsei, sf::RectangleShape& button, sf::RenderWindow& window, const sf::Event& event,sf::View& main_view, int skinIndex, std::map<int, sf::Texture>& skinTexturesOrig)
{
	if (event.mouseButton.button != sf::Mouse::Left) return false;

	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f translatedPos = window.mapPixelToCoords(mousePos, main_view);

	if (button.getGlobalBounds().contains(translatedPos)) {
		if (getRalseiSkinstatus(skinIndex)) {
			currentSkinIndex = skinIndex;                 
			ralsei.setTexture(skinTexturesOrig[skinIndex]); 
//			std::cout << "Skin " << skinIndex << " is loaded up!\n";
			return true;
		}
		else {
//			std::cout << "Skin " << skinIndex << " is locked!\n";
			return false;
		}
	}
	return false;
}



int Player::Get_clickCount()
{
	return clickCount;
}

void Player::Add_clickCount(int data)
{
	clickCount += data;
}

void Player::Set_clickCount(int data)
{
	clickCount = data;
}

void Player::updateText(sf::Text& count_text, int data)
{
	std::string ctr_buf;
	ctr_buf = std::to_string(data);
	std::cout << ctr_buf;
	count_text.setString(ctr_buf);


	count_text.setOrigin(rc.width / 2, rc.height / 2);
}

void Player::updateSkins(std::map<int, sf::Texture>& skins_tex_orig, std::map<int, sf::Texture>& skins_tex_button, sf::RectangleShape* skins)
{
	for (int i = 1; i <= 3; ++i)
	{
		std::string origFile = "Textures\\rals" + std::to_string(i) + ".png";
		std::string skinFile = "Textures\\skin" + std::to_string(i) + ".png";
		std::string lockFile = "Textures\\skin" + std::to_string(i) + "lock.png";

		// грузим оригинал
		if (!skins_tex_orig[i].loadFromFile(origFile)) {
			std::cerr << "Error orig text " << skinFile << std::endl;
		}

		// грузим кнопку (открытая или закрытая)
		if (this->getRalseiSkinstatus(i)) {
			skins_tex_button[i].loadFromFile(skinFile);
		}
		else {
			skins_tex_button[i].loadFromFile(lockFile);
		}


		skins[i - 1].setTexture(&skins_tex_button[i]);
	}
}

void Player::updateTextClick(sf::Text& count_text)
{
	std::string clickStr;
	clickStr = std::to_string(clickCount);
	std::cout << clickStr;
	count_text.setString(clickStr);
}

void Player::levelUp()
{
	level += 1;
}

bool Player::countToLevelCheck()
{
	switch (level)
	{
	case 0:
		if (clickCount >= 150) {
			levelUp();
			return true;
		}
		else return false;

		break;
	case 1:
		if (clickCount >= 1000) {
			levelUp();
			return true;
		}
		else return false;
		break;
	case 2:
		if (clickCount >= 5000) {
			levelUp();
			return true;
		}
		else return false;

		break;
	case 3:
		if (clickCount >= 15000) {
			levelUp();
			return true;
		}
		else return false;

		break;
	default:
		 return false;

		break;
	}

	return false;
}

int Player::click_equivalent_level(int& level) {
	switch (level)
	{
	case 0:
		return 150;
	case 1:
		return 1000;
	case 2:
		return 5000;
	case 3:
		return 15000;
	default:
		break;
	}
}

unsigned int Player::getLevel()
{
	return level;
}



void Player::setVariables()
{
	if (level < 1) {
		ralseiSuitOff = false;
		ralseiSuitDino = false;
		ralseiSuitRock = false;
	}
	else if (level < 2) {
		ralseiSuitDino = false;
		ralseiSuitRock = false;
	}
	else if (level < 3) {
		ralseiSuitRock = false;
	}
}

void Player::setSkinStatus(int status)
{
	currentSkinIndex = status;
}

bool Player::getRalseiSkinstatus(int skin_count)
{
	switch (skin_count)
	{
	case 0:
		return false;
	case 1:
		
		return ralseiSuitOff;
	case 2:
		return ralseiSuitDino;
	case 3:
		return ralseiSuitRock;
	default:
		break;
	}
	return false;
}

void Player::Set_clickPower(int data)
{
	clickPower = data;
}

int Player::get_clickPower()
{
	return clickPower;
}

void Player::levelCheck(int& level_F)
{
	switch (level_F)
	{
	case 0:
		clickPower = 1;
		break;
	case 1:
		clickPower = 3;
		ralseiSuitOff = true;
		break;
	case 2:
		clickPower = 5;
		ralseiSuitDino = true;
		break;
	case 3:
		clickPower = 10;
		ralseiSuitRock = true;
		break;
	default:
		
		break;
	}
}
