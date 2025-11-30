#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Game;

class Player {
public:
//-----TEXT-----------
	sf::Text count_text;
	sf::Text level_text;
	//std::string clickStr = "Current count of clicks: ";
	std::string levelStr = "LEVEL: ";

	 int level = 0;
	 
private:
	int clickCount;
	int clickPower = 1;

//-----FONT-----------
	sf::Font click_count_font;
	sf::FloatRect rc = count_text.getLocalBounds();

//-----LEVEL BOOL VARIABELS----------
	bool ralseiSuitDino = true;
	bool ralseiSuitRock = true;
	bool ralseiSuitOff = true;
	sf::IntRect skin3_rect;
	sf::Sprite skin3;
	sf::Texture skin3_tex;
private:
	int currentSkinIndex;
	void levelUp();


public:
	Player()
		: clickCount(0) { 
		click_count_font.loadFromFile("Data\\sans.otf");
		level_text.setFont(click_count_font);
		count_text.setFont(click_count_font);

		skin3_tex.loadFromFile("Textures\\rals3.png");
		skin3.setTexture(skin3_tex);
		skin3.setTextureRect(skin3_rect);

		updateText(level_text, level);
		updateText(count_text, clickCount);
		level_text.setCharacterSize(30);
		count_text.setCharacterSize(24);
		level_text.setFillColor(sf::Color::White);
		count_text.setFillColor(sf::Color::White);	
		
	}

	bool click(sf::Sprite& ralsei, sf::RenderWindow& window, const sf::Event& event, sf::View main_view);
	bool click(sf::Sprite& ralsei,
		sf::RectangleShape& button,
		sf::RenderWindow& window,
		const sf::Event& event,
		sf::View& main_view,
		int skinIndex,
		std::map<int, sf::Texture>& skinTexturesOrig,
		int& i);
	//bool click(sf::Sprite& button, sf::RenderWindow& window, const sf::Event& event, sf::View& main_view);

	int Get_clickCount();
	void Add_clickCount(int data);
	void Add_clickCount(sf::Event& event);
	void Set_clickCount(int data);
	void updateText(sf::Text& count_text, int data);
	void updateSkins(std::map<int, sf::Texture>& skins_tex_orig, std::map<int, sf::Texture>& skins_tex_button, sf::RectangleShape* skins);
	void updateTextClick(sf::Text& count_text);
	void levelCheck(int& level);
	bool countToLevelCheck();
	unsigned int getLevel();
	int click_equivalent_level(int& level);
	void setVariables();
	void setSkinStatus(int status);
	bool getRalseiSkinstatus(int level);
	void Set_clickPower(int data);
	int get_clickPower();
	void reset(std::map<int, sf::Texture>& skins_tex_orig, std::map<int, sf::Texture>& skins_tex_button, sf::RectangleShape* skins);
	~Player() {}

};