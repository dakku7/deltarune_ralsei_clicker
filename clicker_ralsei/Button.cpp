#include "Button.h"

Button::Button(TextureID button_tex, TextureID button_tex_light, AssetManager* asset)
{
	ass_mgr = asset;
	this->id = button_tex;
	this->id_light = button_tex_light;
}

void Button::initSprite()
{
	ass_mgr->loadTexture(id);
	ass_mgr->loadTexture(id_light);

	button.setTexture(ass_mgr->getTexture(id));
}

void Button::buttonHover(Player& p, sf::RenderWindow& window)
{
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);

		float x1 = button.getPosition().x;
		float y1 = button.getPosition().y;
		float x2 = x1 + button.getTexture()->getSize().x;
		float y2 = y1 + button.getTexture()->getSize().y;

		if ((mousePos.x >= x1) && (mousePos.x <= x2) && (mousePos.y >= y1) && (mousePos.y <= y2)) {
			button.setTexture(ass_mgr->getTexture(id_light));
		}
		else {
			button.setTexture(ass_mgr->getTexture(id));
		}
}

sf::Sprite& Button::getSprite()
{
	return button;
}

void Button::setPosition(sf::Vector2f& pos)
{
	button.setPosition(pos);
}
