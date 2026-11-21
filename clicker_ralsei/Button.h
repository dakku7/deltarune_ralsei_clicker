#pragma once
#include <functional>
#include "SFML/Graphics.hpp"
#include "AssetManager.h"
#include "Clickable.h"
#include "RalseiSkins.h"


class Player;

class Button : public Clickable {
public:
	using Callback = std::function<void()>;

private:
	sf::Sprite button;
	TextureID id;
	TextureID id_light;
	TextureID id_lock;
	TextureID id_lock_light;
	RalseiSkins skin;

	AssetManager* ass_mgr;
	bool isHovered = false;
	bool isEnabled = false;

	//callback for click method
	Callback callback;
public:
	Button(ClickType type, 
		TextureID button_tex, TextureID button_tex_light, 
		TextureID button_lock_tex, TextureID button_lock_light_tex,
		RalseiSkins skin_tex, AssetManager* asset);
	void initSprite();

	void setHovered(bool exprs) override;
	void setEnabled(bool exprs);
	void setCallback(Callback func);
	bool contains(sf::Vector2f point) const override;
	void clicked() override;
	
	void update(float dt) override;
	void render(sf::RenderTarget* target) override;

	sf::Sprite& getSprite();
	RalseiSkins getSkin();
	void setPosition(const sf::Vector2f& pos);
	sf::Vector2f getPosition() override;
};