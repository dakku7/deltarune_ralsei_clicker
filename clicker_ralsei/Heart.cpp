#include "Heart.h"
#include "Player.h"

Heart::Heart(AssetManager& assets)
	: ass_mgr(assets)
{
	init();
}

void Heart::init()
{
	initTextures();
	initSprites();
	
}

void Heart::initTextures() {
	ass_mgr.loadTexture(TextureID::Heart_empty);
	ass_mgr.loadTexture(TextureID::Heart);



	font.loadFromFile("Data\\sans.otf");
	lvl_text.setFont(font);
}

void Heart::initSprites() {
	sprite.setTexture(ass_mgr.getTexture(TextureID::Heart_empty));
	sprite_fill.setTexture(ass_mgr.getTexture(TextureID::Heart));

	//heart position
	sf::FloatRect heartBounds = sprite.getLocalBounds();
	sprite.setOrigin(heartBounds.width / 2.f, heartBounds.height / 2.f);
	sprite.setPosition(150, 200);
	sprite_fill.setOrigin(heartBounds.width / 2.f, heartBounds.height / 2.f);
	sprite_fill.setPosition(150, 200);
	
//---------------------------------------------------------------


	lvl_text.setString(std::to_string(lvl));
	//text_lvl position
	sf::FloatRect textRect = lvl_text.getLocalBounds();
	lvl_text.setOrigin(textRect.left + textRect.width / 2.f,
		textRect.top + textRect.height / 2.f);
	lvl_text.setPosition(sprite.getPosition().x-2, sprite.getPosition().y);
}

void Heart::heartFillingUp()
{
	sf::IntRect fillRectangle(0, sprite.getGlobalBounds().getSize().y - height_fill, sprite.getGlobalBounds().getSize().x, height_fill);

	sprite_fill.setTextureRect(fillRectangle);
	sprite_fill.setOrigin(sprite.getOrigin().x, sprite.getOrigin().y); // точка привязки низ спрайта
	sprite_fill.setPosition(sprite.getPosition().x, sprite.getPosition().y  + (ass_mgr.getTexture(TextureID::Heart_empty).getSize().y - height_fill));
}

void Heart::syncWithPlayer(Player& p)
{
	if (this->lvl != p.getLevel()) {
		this->lvl = p.level;
	}

	auto f = [this, &p]() {
		float fillPercent = static_cast<float>(p.Get_clickCount()) / p.click_equivalent_level(p.level);
		sf::Vector2u textureSize = ass_mgr.getTexture(TextureID::Heart).getSize();
		fillPercent = std::clamp(fillPercent, 0.f, 1.f);

		int filledHeight = static_cast<int>(textureSize.y * fillPercent);
		this->height_fill = filledHeight;
		};

	f();
}

void Heart::update(float dt)
{
	lvl_text.setString(std::to_string(lvl));
	heartFillingUp();
}

void Heart::render(sf::RenderTarget* target)
{
	target->draw(sprite);
	target->draw(sprite_fill);
	target->draw(lvl_text);
}

sf::Vector2f Heart::getPosition()
{
	return sprite.getPosition();
}