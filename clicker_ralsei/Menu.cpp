#include "Menu.h"

Menu::Menu()
	: isActive(false), isHeartActive(false)
{
	back_buttons_tex.loadFromFile("Textures\\back_menu.png");
	back_buttons.setTexture(back_buttons_tex);
	back_buttons.setPosition(0, 0);
	pause_font.loadFromFile("Data\\sans.otf");
	paused.setFont(pause_font);
	paused.setString("PAUSED");
	paused.setCharacterSize(48);

	sf::FloatRect temp = paused.getGlobalBounds();
	paused.setOrigin(temp.width / 2.f, temp.height / 2.f);
	paused.setPosition(400, 50);
	overlay.setFillColor(sf::Color(0, 0, 0, 150));
	overlay.setSize(sf::Vector2f(800, 600));
	overlay.setPosition(0, 0);
	
	buttons_text[0].setString("RESUME");
	buttons_text[1].setString("OPTIONS");
	buttons_text[2].setString("CLOSE GAME");

	
	buttons_frame_lightened.loadFromFile("Textures\\frame_menu_light.png");
	sf::Vector2f vector_to_setup = sf::Vector2f(200, 100);
	for (int i = 0; i < 3; i++)
	{
		buttons_frame[i].loadFromFile("Textures\\frame_menu.png");
		buttons[i].setTexture(buttons_frame[i]); 
		buttons[i].setScale(0.9, 0.9);
		buttons[i].setPosition(vector_to_setup);

		buttons_text[i].setFont(pause_font);
		temp = buttons_text[i].getGlobalBounds();
		buttons_text[i].setOrigin(temp.width / 2.f, temp.height / 2);
		buttons_text[i].setPosition(sf::Vector2f(buttons[i].getPosition().x + buttons[i].getGlobalBounds().width / 2, buttons[i].getPosition().y + buttons[i].getGlobalBounds().height / 2 - 10));
		vector_to_setup.y += 25 + 148;
	}	

	top_layer_tex.loadFromFile("Textures\\top_layer_menu.png");
	top_layer.setTexture(top_layer_tex);

	bottom_layer_tex.loadFromFile("Textures\\bottom_layer_menu.png");
	bottom_layer.setTexture(bottom_layer_tex);

	click.openFromFile("Audio\\snd_item.wav");
	heart_tex.loadFromFile("Textures\\heart_opt.png");
	heart.setTexture(heart_tex);
	heart.setPosition(buttons[0].getPosition().x + buttons[0].getGlobalBounds().width - 34 - 40, buttons[0].getPosition().y + buttons[0].getLocalBounds().height / 2 - 25);
}


void Menu::draw(Player& player, sf::RenderWindow& window)
{
	isActive = true;
	startAnim();
	float t;	
	sf::Event ev;

	while (isActive && window.isOpen())
	{
		while (window.pollEvent(ev))
		{
			switch (ev.type) {
			case sf::Event::Closed:
				window.close();
				isActive = false;
				break;

			case sf::Event::KeyPressed:
				if (ev.key.code == sf::Keyboard::X) {
					isActive = false;
				}
				if (ev.key.code == sf::Keyboard::Z) {
					button_action(window, ev);
				}
				arrowControl(window, ev);
				break;
			case sf::Event::MouseButtonPressed:
				button_action(window, ev);
				break;

				
			}		
		}
		checkHoverButton(window, buttons);
		updateAnim();
		for (int i = 0; i < 3; i++)
		{
			hoverButton(window, buttons[i]);
		}

		window.draw(overlay);
		drawAnim(&window);
		window.draw(back_buttons);
		window.draw(paused);
		for (auto iter : buttons)
		{
			window.draw(iter);
		}
		for (auto iter : buttons_text)
		{
			window.draw(iter);

		}
		window.draw(heart);
		window.display();
	}	
}

void Menu::button_action(sf::RenderWindow& window, sf::Event& ev)
{
	if ((ev.key.code == sf::Mouse::Left)) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Vector2f translatedPos = window.mapPixelToCoords(mousePos, window.getView());
		click.play();

		if (buttons[0].getGlobalBounds().contains(translatedPos)) {
			isActive = false;
		}
		else if (buttons[1].getGlobalBounds().contains(translatedPos)) {
			options.draw(window);
		}
		else if (buttons[2].getGlobalBounds().contains(translatedPos)) {
			window.close();
		}
	}

	if (ev.key.code == sf::Keyboard::Z) {

		sf::Vector2f heart_Temp= heart.getPosition();
		click.play();
		if (buttons[0].getGlobalBounds().contains(heart_Temp)) {
			isActive = false;
		}
		else if (buttons[1].getGlobalBounds().contains(heart_Temp)) {
			options.draw(window);
		}
		else if (buttons[2].getGlobalBounds().contains(heart_Temp)) {
			window.close();
		}
		
	}
	
}

void Menu::startAnim()
{
	bottom_layer.setPosition(10, 10);
	top_layer.setPosition(0, 0);

	anim_clock.restart();
}

void Menu::updateAnim()
{
	const float dt = anim_clock.restart().asSeconds();
	if (dt <= 0.f) return;

	// движение по диагонали 45 градусов; будем использовать симметрию:
	// top: движетс€ вниз вправо; bottom: вверх влево Ч создают эффект расхождени€
	const float diag = (layer_speed * dt) / std::sqrt(2.f);

	top_offset.x += diag;
	top_offset.y += diag;

	bottom_offset.x -= diag;
	bottom_offset.y -= diag;

	// ќграничение смещений по размеру текстур (чтобы корректно тайлить)
	if (top_layer_tex.getSize().x > 0 && top_layer_tex.getSize().y > 0) {
		const float tw = static_cast<float>(top_layer_tex.getSize().x);
		const float th = static_cast<float>(top_layer_tex.getSize().y);
		top_offset.x = std::fmod(top_offset.x, tw);
		top_offset.y = std::fmod(top_offset.y, th);
		// fmod может вернуть отрицательное значение -> нормируем в диапазон [ -tw, tw ]
		if (top_offset.x < -tw) top_offset.x += tw * std::ceil((-top_offset.x) / tw);
		if (top_offset.y < -th) top_offset.y += th * std::ceil((-top_offset.y) / th);
	}

	if (bottom_layer_tex.getSize().x > 0 && bottom_layer_tex.getSize().y > 0) {
		const float tw = static_cast<float>(bottom_layer_tex.getSize().x);
		const float th = static_cast<float>(bottom_layer_tex.getSize().y);
		bottom_offset.x = std::fmod(bottom_offset.x, tw);
		bottom_offset.y = std::fmod(bottom_offset.y, th);
		if (bottom_offset.x < -tw) bottom_offset.x += tw * std::ceil((-bottom_offset.x) / tw);
		if (bottom_offset.y < -th) bottom_offset.y += th * std::ceil((-bottom_offset.y) / th);
	}
}

void Menu::drawAnim(sf::RenderWindow* s_window)
{
	if (!s_window) return;
	sf::RenderWindow& window = *s_window;

	// –исуем bottom layer (темна€ сетка) первым
	if (bottom_layer_tex.getSize().x > 0 && bottom_layer_tex.getSize().y > 0) {
		const float tw = static_cast<float>(bottom_layer_tex.getSize().x);
		const float th = static_cast<float>(bottom_layer_tex.getSize().y);
		const sf::Vector2u winSz = window.getSize();
		const int cols = static_cast<int>(std::ceil(winSz.x / tw)) + 2;
		const int rows = static_cast<int>(std::ceil(winSz.y / th)) + 2;

		for (int i = -1; i < cols; ++i) {
			for (int j = -1; j < rows; ++j) {
				bottom_layer.setPosition(i * tw + bottom_offset.x, j * th + bottom_offset.y);
				window.draw(bottom_layer);
			}
		}
	}

	// –исуем top layer (светла€ сетка) поверх
	if (top_layer_tex.getSize().x > 0 && top_layer_tex.getSize().y > 0) {
		const float tw = static_cast<float>(top_layer_tex.getSize().x);
		const float th = static_cast<float>(top_layer_tex.getSize().y);
		const sf::Vector2u winSz = window.getSize();
		const int cols = static_cast<int>(std::ceil(winSz.x / tw)) + 2;
		const int rows = static_cast<int>(std::ceil(winSz.y / th)) + 2;

		for (int i = -1; i < cols; ++i) {
			for (int j = -1; j < rows; ++j) {
				top_layer.setPosition(i * tw + top_offset.x, j * th + top_offset.y);
				window.draw(top_layer);
			}
		}
	}
}

void Menu::checkHoverButton(sf::RenderWindow& window, sf::Sprite buttons[3])
{
	for (int i = 0; i < 3; i++)
	{

		sf::Vector2i mousePos = sf::Mouse::getPosition(window);

		float x1 = buttons[i].getPosition().x;
		float y1 = buttons[i].getPosition().y;
		float x2 = x1 + buttons[i].getTexture()->getSize().x;
		float y2 = y1 + buttons[i].getTexture()->getSize().y;

		if ((mousePos.x >= x1) && (mousePos.x <= x2) && (mousePos.y >= y1) && (mousePos.y <= y2)) {
			buttons[i].setTexture(buttons_frame_lightened);
		}
		else {
			buttons[i].setTexture(buttons_frame[0]);
		}
	}
}

void Menu::hoverButton(sf::RenderWindow& window, sf::Sprite& button)
{
	sf::FloatRect temp = button.getGlobalBounds();
	sf::Vector2f hearttemp = heart.getPosition();
	if (temp.contains(hearttemp)) {
		button.setTexture(buttons_frame_lightened);
	}
}

void Menu::arrowControl(sf::RenderWindow& window, sf::Event& ev)
{
	if (ev.type != sf::Event::KeyPressed) return;

	if (button_count < 0) button_count = 0;
	if (button_count > 2) button_count = 2;

	if (ev.key.code == sf::Keyboard::Down) {
		if (button_count < 2) ++button_count;

		for (int i = 0; i < 3; ++i) buttons[i].setTexture(buttons_frame[0]);
		buttons[button_count].setTexture(buttons_frame_lightened);

		heart.setPosition(
			buttons[button_count].getPosition().x + buttons[button_count].getGlobalBounds().width - 34 - 40,
			buttons[button_count].getPosition().y + buttons[button_count].getGlobalBounds().height / 2.f - 20.f
		);

		return;
	}

	if (ev.key.code == sf::Keyboard::Up) {
		if (button_count > 0) --button_count;

		for (int i = 0; i < 3; ++i) buttons[i].setTexture(buttons_frame[0]);
		buttons[button_count].setTexture(buttons_frame_lightened);

		heart.setPosition(
			buttons[button_count].getPosition().x + buttons[button_count].getGlobalBounds().width - 34 - 40,
			buttons[button_count].getPosition().y + buttons[button_count].getGlobalBounds().height / 2.f - 20.f
		);

		return;
	}

}

Menu::~Menu()
{
}
