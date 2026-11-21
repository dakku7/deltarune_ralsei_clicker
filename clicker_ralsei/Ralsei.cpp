#include "Ralsei.h"
#include "Constants.h"

void Ralsei::initSprite()
{
//	auto it = skins.find(TextureID::Ralsei_Main);
	ralsei_sp.setTexture(ass_mgr.getTexture(TextureID::Ralsei_Main));

	auto bounds = ralsei_sp.getLocalBounds();
	ralsei_sp.setOrigin(
		bounds.width / 2.f,
		bounds.height / 2.f
	);
	scale_ralsei_x = ralsei_sp.getScale().x;
	scale_ralsei_y = ralsei_sp.getScale().y;
	angle_ralsei = ralsei_sp.getRotation();
}

void Ralsei::initTextures()
{
		for (int i = 0; i < 4; i++)
		{
			TextureID texID =
				static_cast<TextureID>(static_cast<int>(TextureID::Ralsei_Main) + i);

			ass_mgr.loadTexture(texID);

			RalseiSkins skinID = static_cast<RalseiSkins>(i);

			skins.emplace(skinID, &ass_mgr.getTexture(texID));
		}
}

void Ralsei::initSound()
{
	click_sound.openFromFile("Audio\\click.wav");
}





void Ralsei::update(float dt)
{
	updateClickAnimation(dt);
	
}

void Ralsei::render(sf::RenderTarget* target)
{
	target->draw(ralsei_sp);
}

void Ralsei::clickAnimation()
{
	if (isClicked)
		return;

	isClicked = true;
	timer = 0.f;

	
}

void Ralsei::updateClickAnimation(float dt)
{

	if (!isClicked) {
		return;
	}
	float multipl = 0.025f;



	timer += dt;
	if (isClicked && timer >= 0.05f && timer < 0.15f) {
		
		ralsei_sp.setScale(ralsei_sp.getScale().x + multipl, ralsei_sp.getScale().x + multipl);
		ralsei_sp.setRotation(1.5f);

	}

	if (isClicked&& timer >= 0.25f) {
		ralsei_sp.setScale(scale_ralsei_x, scale_ralsei_y);
		ralsei_sp.setRotation(angle_ralsei);
		isClicked = false;
		timer = 0.f;	
	}
}

void Ralsei::setSkin(RalseiSkins skin)
{
	auto it = skins.find(skin);
	if (it != skins.end()) {
		this->currentSkinID = skin;
		this->ralsei_sp.setTexture(*it->second);
	}
}

void Ralsei::setHovered(bool expr)
{
}

RalseiSkins Ralsei::getCurrentSkinID()
{
	return currentSkinID;
}

bool Ralsei::contains(sf::Vector2f point) const {
	return this->ralsei_sp.getGlobalBounds().contains(point);
}

void Ralsei::clicked() {
	clickAnimation();
	click_sound.play();
}

sf::Vector2f Ralsei::getPosition() {
	return ralsei_sp.getPosition();
}

void Ralsei::setPosition(sf::Vector2f pos)
{
	this->ralsei_sp.setPosition(pos);
}
