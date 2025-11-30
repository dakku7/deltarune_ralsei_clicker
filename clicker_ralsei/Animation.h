#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <ctime>
#include <iostream>

class Animation
{
public:
	bool timeAnim;
	bool timeSparkle;
private:
	sf::Music meow;
	bool timeIsActive;
	sf::Clock clock;
	sf::Font levelup_font;
	sf::Text levelup;
	sf::RectangleShape overlay;
//============================================================================
	sf::Sprite sparkle;
	sf::Texture sparkle_texture;
	int x1 = 0, y1 = 0;
	sf::IntRect sparkle_rect;
	int count_sparkle = 1;
	sf::Clock sparkleClock;
	sf::Clock waitTime;
//============================================================================
	float duration = 3.0f;
	float Bscale_ralsei_x = 0.0f;
	float Bscale_ralsei_y = 0.0f;
	float Bangle_ralsei = 0.0f;

//============================================================================
	sf::Texture fog_texture;
	sf::Sprite fog;
	float fog_time = 0;
	float fog_x1 = 0, fog_y1 = 0;
//============================================================================


	sf::Sprite light;
	sf::Texture light_texture;
	sf::Clock time_light;
	bool TimeLight;
	float l_x = 0, l_y = 0;
	float time = 0.f;
	float fadeSpeed = 1.1f;      // скорость появления/угасания
	float scalePulseSpeed = 0.5f; // скорость пульсации
	float scaleAmplitude = 0.05f; // амплитуда пульсации (5%)
	float alphaMin = 50;         // минимальная прозрачность
	float alphaMax = 255;        // максимальная прозрачность


	sf::Music snd_levelup;
public:
	Animation();
	void startLevelUp(int level, bool& secureClick);
	void updateLevelUp(sf::RenderWindow& window, bool& secureClick);
	void draw(sf::RenderWindow& window);
//============================================================================
	void idleAnimation(sf::Sprite& ralsei);
	void startClicked(sf::Sprite& ralsei);
	void updateModels(sf::Sprite& ralsei);
//============================================================================
	void sparkleSpawn();
	void sparkleUpdate();
	void sparkeDraw(sf::RenderWindow& window);
//===========================================================================
	void fogUpdate();
	void fogDraw(sf::RenderWindow& window);
//=============================================================================
	void lightSpawn();
	void lightUpdate();
	void lightDraw(sf::RenderWindow& window);

	~Animation();
private:
};

