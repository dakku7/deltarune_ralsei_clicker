#include "Animation.h"


Animation::Animation()
	: timeIsActive(false), timeSparkle(false) {
	 meow.openFromFile("Audio/meow.mp3");
	 meow.setVolume(4.0f);
	 sparkle_texture.loadFromFile("Textures\\star.png");
	 sparkle.setTexture(sparkle_texture);

	 sparkle_rect.left = 0;
	 sparkle_rect.top = 0;
	 sparkle_rect.width = 350;
	 sparkle_rect.height = 330;

	 fog_texture.loadFromFile("Textures\\123.png");
	 fog_texture.setSmooth(false);
	 fog_texture.setRepeated(true);
	 fog.setTexture(fog_texture);
	 fog.setTextureRect({ 0,0,800,600 });
	 fog.setColor(sf::Color(255, 255, 255, 20));
	 fog.setScale(2, 2);
	 sparkle.setTextureRect(sparkle_rect);
	 sparkle.setScale(0.1,0.1);
	 timeAnim = false;

//	 light_texture.loadFromFile("Textures\\light.png");
//	 light.setTexture(light_texture);
//	 light.setScale(0.5, 0.5);
//	 light.setOrigin(light_texture.getSize().x / 2.f, light_texture.getSize().y / 2.f);

	 srand(static_cast<unsigned>(std::time(0)));

}



void Animation::startClicked(sf::Sprite& ralsei)
 {
	 if (!timeIsActive) {
		 Bscale_ralsei_x = ralsei.getScale().x;
		 Bscale_ralsei_y = ralsei.getScale().y;
		 Bangle_ralsei = ralsei.getRotation();

		 meow.play();
		 ralsei.setScale(ralsei.getScale().x * 1.05f, ralsei.getScale().x * 1.05f);
		 ralsei.setRotation(2.0f);
		 clock.restart();
		 timeIsActive = true;
	 }
 }

 void Animation::updateModels(sf::Sprite& ralsei)
 {
	

	 if (timeIsActive && clock.getElapsedTime().asSeconds() >= 0.05f) {
		 ralsei.setScale(ralsei.getScale().x * 1.05f, ralsei.getScale().x * 1.05f);

	 }

	 if (timeIsActive && clock.getElapsedTime().asSeconds() >= 0.1f) {
		 ralsei.setScale(Bscale_ralsei_x, Bscale_ralsei_y);
		 ralsei.setRotation(Bangle_ralsei);
		 timeIsActive = false;
		 
	 }
 }



 void Animation::startLevelUp(int level)
 {

	 timeAnim = true;
	 clock.restart();

	 levelup_font.loadFromFile("Data/tennafont.ttf");

	 levelup.setFont(levelup_font);
	 levelup.setCharacterSize(60);
	 levelup.setFillColor(sf::Color(255, 255, 255, 0));
	 levelup.setString("LEVEL " + std::to_string(level));

	 sf::FloatRect bounds = levelup.getLocalBounds();
	 levelup.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	 overlay.setSize(sf::Vector2f(800,600));
	 overlay.setFillColor(sf::Color(0, 0, 0, 0));
 }

 void Animation::updateLevelUp(sf::RenderWindow& window)
 {
	 if (!timeAnim) return;

	 float t = clock.getElapsedTime().asSeconds() / duration;

	 float alphaFactor;
	 if (t < 0.5f)
		 alphaFactor = t / 0.5f; 
	 else
		 alphaFactor = 1.f - (t - 0.5f) / 1.5f; 

	 sf::Uint8 textA = static_cast<sf::Uint8>(std::clamp(alphaFactor * 255.f, 0.f, 255.f));
	 levelup.setFillColor(sf::Color(255, 255, 255, textA));

	 sf::Uint8 overlayA = static_cast<sf::Uint8>(std::clamp(alphaFactor * 80.f, 0.f, 80.f));
	 overlay.setFillColor(sf::Color(0, 0, 0, overlayA));

	
	 levelup.setFillColor(sf::Color(255, 255, 255, textA));
	
	 float scale = 1.f + 0.2f * sin(t * 3.14f);
	 levelup.setScale(scale, scale);

	if (clock.getElapsedTime().asSeconds() > 3) {
		 timeAnim = false;
		 window.setMouseCursorVisible(true); // hide cursor
		 sf::Mouse::setPosition(sf::Vector2i(400, 300), window); // reset position if needed
	 } 
 }

 void Animation::draw(sf::RenderWindow& window)
 {
	 if (!timeAnim)
	 {
		 window.setMouseCursorVisible(true); // hide cursor
		 sf::Mouse::setPosition(sf::Vector2i(400, 300), window); // reset position if needed
		 return;
	 }
	
	 window.setMouseCursorVisible(false); // hide cursor
	 sf::Mouse::setPosition(sf::Vector2i(0, 0), window); // reset position if needed
	 overlay.setSize((sf::Vector2f)window.getSize());

	 levelup.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);

	 window.draw(overlay);
	 window.draw(levelup);
 }

void Animation::sparkleSpawn()
{	
	
	if (waitTime.getElapsedTime().asSeconds() < 3) {
		sparkle_rect.left = 1050;
		sparkle_rect.top = 1050;
		return;
	}

	if (timeSparkle) return;

	x1 = rand() % 800 + 125;
	y1 = rand() % 600 + 125;
	sparkle_rect.left = 0;
	sparkle_rect.top = 0;
	sparkle.setTextureRect(sparkle_rect);

	sparkle.setPosition(x1 - 125, y1 - 125);
	timeSparkle = true;
	sparkleClock.restart();
	
}

void Animation::sparkleUpdate()
{
	if (!timeSparkle) return;

	float gap = 0.4;


	if (count_sparkle >= 8 && sparkleClock.getElapsedTime().asSeconds() >= gap) {

		timeSparkle = false;
		count_sparkle = 1;
	}

	if (count_sparkle == 7 ) {
		sparkle_rect.left = 0;
		sparkle_rect.top = 0;
		sparkle.setTextureRect(sparkle_rect);
		count_sparkle++;
		waitTime.restart();
	}

	if (count_sparkle == 3) {
		sparkle_rect.left = 0;
		sparkle_rect.top += 350;
		count_sparkle++;
		sparkle.setTextureRect(sparkle_rect);
	}

	if (sparkleClock.getElapsedTime().asSeconds() >= gap) {
		count_sparkle++;
		sparkle_rect.left += 350;
		sparkle.setTextureRect(sparkle_rect);
		sparkleClock.restart();
	}

}

void Animation::fogUpdate()
{
	fog_x1 += 10.f * 0.016f;
	fog_y1 += 6.f * 0.016f;
	fog.setTextureRect({ static_cast<int>(fog_x1), static_cast<int>(fog_y1), 800, 600 });

	fog_time += 0.016f;
	float alpha = std::max(static_cast<float>(0), 0 + std::max(0.f, std::sin(fog_time * 0.5f) * 20));
	fog.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
}

void Animation::fogDraw(sf::RenderWindow& window)
{
	window.clear(sf::Color(30, 30, 30));
	window.draw(fog);
}

void Animation::lightSpawn()
{
	if (TimeLight) return;

	l_x = rand() % 800 + 125;
	l_y = rand() % 600 + 125;
	
	sparkle.setTextureRect(sparkle_rect);

	if (l_x > 800 - light_texture.getSize().x) {
		l_x = static_cast<float>(800 - light_texture.getSize().x);
	}
	if (l_y > 600 - light_texture.getSize().y) {
		l_y = 600 - (static_cast<float>(light_texture.getSize().y));
	}

	light.setPosition(300, 300);
	TimeLight = true;
	time_light.restart();
}

void Animation::lightUpdate() {

		
	if (!TimeLight) {
		return;
	}

	float dt = time_light.getElapsedTime().asSeconds();
	time += dt;
	
	float alpha = (std::sin(time * fadeSpeed) * 0.5f + 0.5f) * (alphaMax - alphaMin) + alphaMin;

	
	float scale = 0.f + std::sin((time/2) * scalePulseSpeed) * scaleAmplitude;

	light.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
	light.setScale(scale, scale);

}

void Animation::lightDraw(sf::RenderWindow& window) {
	window.draw(light);
}

void Animation::sparkeDraw(sf::RenderWindow& window) {
	window.draw(sparkle);
}

Animation::~Animation() 
{

}