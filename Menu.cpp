#include "Menu.h"

Menu::Menu()
{
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

	
}


void Menu::draw(Player& player, sf::RenderWindow& window)
{
	isActive = true;
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
				if (ev.key.code == sf::Keyboard::Z) {
					isActive = false;
					break;
				}
			case sf::Event::MouseButtonPressed:
				button_action(window, ev);
			}
		}
		

		window.draw(overlay);
		window.draw(paused);
		for (auto iter : buttons)
		{
			window.draw(iter);
		}
		for (auto iter : buttons_text)
		{
			window.draw(iter);

		}
		window.display();
	}


	
}

void Menu::button_action(sf::RenderWindow& window, sf::Event& ev)
{
	if (!(ev.key.code == sf::Mouse::Left)) {
		return;
	}

	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f translatedPos = window.mapPixelToCoords(mousePos, window.getView());

	if (buttons[0].getGlobalBounds().contains(translatedPos)) {
		isActive = false;
	}
	else if (buttons[1].getGlobalBounds().contains(translatedPos)) {
		std::cout << "\nOptions\n";
	}
	else if (buttons[2].getGlobalBounds().contains(translatedPos)) {
		window.close();
	}
}

Menu::~Menu()
{
}
