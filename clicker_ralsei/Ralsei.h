#pragma once
#include "SFML/Graphics.hpp"
#include "AssetManager.h"
#include "Clickable.h"
#include "RalseiSkins.h"


class Ralsei : public Clickable {
private:
	sf::Sprite ralsei_sp;
	bool isClicked = false;
	std::map<RalseiSkins, sf::Texture*> skins;
	RalseiSkins currentSkinID = RalseiSkins::Default;

	AssetManager& ass_mgr;

	//anim part
	float duration = 3.0f;
	float scale_ralsei_x = 0.0f;
	float scale_ralsei_y = 0.0f;
	float angle_ralsei = 0.0f;

	float frame_time = 0.15f;
	float timer = 0.f;

	sf::Music click_sound;
public:
	Ralsei(AssetManager& assets, ClickType type)
		: Clickable(type), ass_mgr(assets)
	{
		initTextures();
		initSprite();
		initSound();
	}	
	
	void initSprite();
	void initTextures();
	void initSound();

	void clickAnimation();
	void updateClickAnimation(float dt);
	void setSkin(RalseiSkins skin);
	void setHovered(bool expr) override;

	void update(float dt) override;
	void render(sf::RenderTarget* target) override;
	bool contains(sf::Vector2f point) const override;
	void clicked() override;
	sf::Vector2f getPosition() override;


	void setPosition(sf::Vector2f pos);

	RalseiSkins getCurrentSkinID();
};