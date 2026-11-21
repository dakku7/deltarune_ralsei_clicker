#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include <map>

class Anim {
private:
	sf::Sprite* sprite;
	std::vector<sf::Texture*>& frames;
	sf::Clock clock;

	float timer = 0.f;
	int currentFrame = 0;
	float frameTime = 0.f;

public:
	Anim(sf::Sprite* target, std::vector<sf::Texture*>& target_frames, float frame_time);
	void update(float dt);
};