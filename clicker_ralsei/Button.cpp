#include "Button.h"

Button::Button(ClickType type,
	TextureID button_tex, TextureID button_tex_light,
	TextureID button_lock_tex, TextureID button_lock_light_tex,
	RalseiSkins skin_tex, AssetManager* asset)
	: Clickable(type), ass_mgr(asset),
	id(button_tex), id_light(button_tex_light), 
	id_lock(button_lock_tex), id_lock_light(button_lock_light_tex), skin(skin_tex)
{
	initSprite();
}

void Button::initSprite()
{
	ass_mgr->loadTexture(id);
	ass_mgr->loadTexture(id_light);

	button.setTexture(ass_mgr->getTexture(id));
}

void Button::setHovered(bool exprs)
{
	isHovered = exprs;
	if (isHovered) {
		if (isEnabled) {
			button.setTexture(ass_mgr->getTexture(id_lock_light));
		}
		else button.setTexture(ass_mgr->getTexture(id_light));
	}
	else {
		if (isEnabled) {
			button.setTexture(ass_mgr->getTexture(id_lock));
		} 
		else button.setTexture(ass_mgr->getTexture(id));
	}
}

void Button::setEnabled(bool exprs)
{
	isEnabled = exprs;
}

void Button::setCallback(Callback func)
{
	callback = func;
}

bool Button::contains(sf::Vector2f point) const
{
	return this->button.getGlobalBounds().contains(point);
}

void Button::clicked()
{
	if (isEnabled) {
		return;
	}
	if (callback) {
		callback();
	}
}


void Button::update(float dt)
{
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->button);
}

sf::Sprite& Button::getSprite()
{
	return button;
}

RalseiSkins Button::getSkin()
{
	return skin;
}

void Button::setPosition(const sf::Vector2f& pos)
{
	button.setPosition(pos);
}

sf::Vector2f Button::getPosition()
{
	return button.getPosition();
}
