#include "Options.h"

Options::Options()
	: activeOpt(false), isHeartChosen(false)
{
	font.loadFromFile("Data\\sans.otf");

	overlay.setPosition(0, 0);
	overlay.setSize(sf::Vector2f(800, 600));
	overlay.setFillColor(sf::Color::Black);

	opt_text.setString("OPTIONS");
	opt_text.setFont(font);
	opt_text.setCharacterSize(42);
	dialogue.setFont(font);
	dialogue.setCharacterSize(20);

	for (int i = 0; i < 3; ++i)
	{
		text_button[i].setFont(font);
		text_button[i].setCharacterSize(35);
	}
	text_button[0].setString("Binds");
	text_button[1].setString("Volume");
	text_button[2].setString("Codes");

	sf::FloatRect temp = opt_text.getGlobalBounds();
	opt_text.setOrigin(temp.width / 2, temp.height / 2);
	opt_text.setPosition(800 - (800/3) - 50, 50);
	
	button_options_light_tex.loadFromFile("Textures\\frame_opt_light.png");
	button_options_tex.loadFromFile("Textures\\frame_opt.png");
	description_tex.loadFromFile("Textures\\main_text_banner_opt.png");
	ralsei_mini_tex.loadFromFile("Textures\\ralsei_mini_opt.png");
	ralsei_mini_blushy.loadFromFile("Textures\\ralsei_mini_opt_blushy.png");
	ralsei_mini_sad.loadFromFile("Textures\\ralsei_mini_opt_sad.png");
	back_button_tex.loadFromFile("Textures\\opt_back.png");
	back_button_light.loadFromFile("Textures\\opt_back_light.png");
	heart_tex.loadFromFile("Textures\\heart_opt.png");
	back_button_heart.loadFromFile("Textures\\opt_back_heart.png");
	click.openFromFile("Audio\\snd_item.wav");

	float height = opt_text.getPosition().y * 2;

	for (int i = 0; i < 3; ++i)
	{
		button_options[i].setTexture(button_options_tex);
		button_options[i].setPosition(0, height);
		height += 136;

		text_button[i].setPosition(button_options[i].getPosition().x + 30, button_options[i].getPosition().y + button_options[i].getGlobalBounds().height / 2 - 25);
	}

	description.setTexture(description_tex);
	description.setPosition(sf::Vector2f(button_options[0].getPosition().x + button_options[0].getGlobalBounds().width + 10, button_options[0].getPosition().y));

	ralsei_mini.setTexture(ralsei_mini_tex);
	ralsei_mini.setPosition(0+25, 0+10);
	dialogue.setPosition(sf::Vector2f(ralsei_mini.getPosition().x + ralsei_mini.getGlobalBounds().width + 5, 10));

	back_button.setTexture(back_button_tex);
	back_button.setPosition(button_options[2].getPosition().x+5, button_options[2].getPosition().y + button_options[2].getGlobalBounds().height + (15/2));

	heart.setTexture(heart_tex);
}

void Options::check_action(sf::RenderWindow& window, sf::Event& ev)
{
	if ((ev.key.code == sf::Mouse::Left)) {
		heart.setScale(sf::Vector2f(1, 1));
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Vector2f translatedPos = window.mapPixelToCoords(mousePos, window.getView());

		if (button_options[0].getGlobalBounds().contains(translatedPos)) {
			light_up_button(window, button_options[0]);
			ralsei_mini.setTexture(ralsei_mini_blushy);
			heart.setPosition(
				button_options[0].getPosition().x + button_options[0].getGlobalBounds().width - 70.f,
				button_options[0].getPosition().y + button_options[0].getGlobalBounds().height / 4.f + 15.f
			);
			description_tex.loadFromFile("Textures\\main_text_banner_opt_bindings.png");
			description.setTexture(description_tex);
			dialogue.setString("Funny buttons,\n aren't they?");
		}
		else if (button_options[1].getGlobalBounds().contains(translatedPos)) {
			light_up_button(window, button_options[1]);
			ralsei_mini.setTexture(ralsei_mini_sad);
			heart.setPosition(
				button_options[1].getPosition().x + button_options[1].getGlobalBounds().width - 70.f,
				button_options[1].getPosition().y + button_options[1].getGlobalBounds().height / 4.f + 15.f
			);
			description_tex.loadFromFile("Textures\\main_text_banner_opt_volume.png");
			description.setTexture(description_tex);
			dialogue.setString("Are you going,\n to turn me down?");
		}
		else if (button_options[2].getGlobalBounds().contains(translatedPos)) {
			light_up_button(window, button_options[2]);
			heart.setPosition(
				button_options[2].getPosition().x + button_options[2].getGlobalBounds().width - 70.f,
				button_options[2].getPosition().y + button_options[2].getGlobalBounds().height / 4.f + 15.f
			);
			ralsei_mini.setTexture(ralsei_mini_tex);
			description_tex.loadFromFile("Textures\\main_text_banner_opt_codes.png");
			description.setTexture(description_tex);
			dialogue.setString("Even I don't,\n know what's this!");
		}
		else if (back_button.getGlobalBounds().contains(translatedPos)) {
			activeOpt = false;

		}
		click.play();
	}

	if (ev.key.code == sf::Keyboard::Z) {

		sf::Vector2f tempHeart = heart.getPosition();

		if (button_options[0].getGlobalBounds().contains(tempHeart)) {
			light_up_button(window, button_options[0]);
			ralsei_mini.setTexture(ralsei_mini_blushy);
			description_tex.loadFromFile("Textures\\main_text_banner_opt_bindings.png");
			description.setTexture(description_tex);
			dialogue.setString("Funny buttons,\n aren't they?");
		}
		else if (button_options[1].getGlobalBounds().contains(tempHeart)) {
			light_up_button(window, button_options[1]);
			ralsei_mini.setTexture(ralsei_mini_sad);
			description_tex.loadFromFile("Textures\\main_text_banner_opt_volume.png");
			description.setTexture(description_tex);
			dialogue.setString("Are you going,\n to turn me down?");
		}
		else if (button_options[2].getGlobalBounds().contains(tempHeart)) {
			light_up_button(window, button_options[2]);
			ralsei_mini.setTexture(ralsei_mini_tex);
			description_tex.loadFromFile("Textures\\main_text_banner_opt_codes.png");
			description.setTexture(description_tex);
			dialogue.setString("Even I don't,\n know what's this!");
		}
		else if (back_button.getGlobalBounds().contains(tempHeart)) {
			activeOpt = false;
	
		}
		click.play();
	}

}

void Options::light_up_button_hover(sf::RenderWindow& window, sf::Sprite* button)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f translatedPos = window.mapPixelToCoords(mousePos, window.getView());
	sf::Vector2f heartTemp = heart.getPosition();

	for (int i = 0; i < 3; i++)
	{
		if (button_options[i].getGlobalBounds().contains(translatedPos) || button_options[i].getGlobalBounds().contains(heartTemp)) {
			button[i].setTexture(button_options_light_tex);
		}
		else button[i].setTexture(button_options_tex);
	}

	if (back_button.getGlobalBounds().contains(translatedPos) || back_button.getGlobalBounds().contains(heartTemp)) {
		back_button.setTexture(back_button_heart);
	}
	else back_button.setTexture(back_button_tex);

}

void Options::light_up_button(sf::RenderWindow& window, sf::Sprite& button)
{
	if (!isHeartChosen) isHeartChosen = true;
	button.setTexture(button_options_light_tex);
	heart.setPosition(sf::Vector2f(button.getPosition().x + button.getGlobalBounds().width - 70, button.getPosition().y + button.getGlobalBounds().height / 4 + 15));
}

void Options::draw(sf::RenderWindow& window)
{
	activeOpt = true;
	sf::Event ev;
	isHeartChosen = true;
	heart.setPosition(
		back_button.getPosition().x + back_button.getGlobalBounds().width - 70.f,
		back_button.getPosition().y + back_button.getGlobalBounds().height / 4.f + 15.f);
	heart.setScale(sf::Vector2f(0, 0));
	back_button.setTexture(back_button_heart);


	while (activeOpt && window.isOpen())
	{
		while (window.pollEvent(ev)) {
			switch (ev.type)
			{
			case sf::Event::Closed:
				window.close();
				activeOpt = false;
				break;
			case sf::Event::KeyPressed:
				if (ev.key.code == sf::Keyboard::X) {
					activeOpt = false;
				}
				if (ev.key.code == sf::Keyboard::Z) {
					check_action(window, ev);
				}
				arrowControl_opt(window, ev);
				break;
			case sf::Event::MouseButtonPressed:
				check_action(window, ev);
				break;
			default:
				break;
			}
		}
		light_up_button_hover(window, button_options);
		window.draw(overlay);
		window.draw(opt_text);
		window.draw(ralsei_mini);
		for (auto it : button_options)
		{
			window.draw(it);
		}
		for (auto it : text_button)
		{
			window.draw(it);
		}
		window.draw(description); 
		window.draw(back_button);
		if (isHeartChosen) {
			window.draw(heart);
		}
		window.draw(dialogue);
		window.display();
	}
	ralsei_mini.setTexture(ralsei_mini_tex);
	dialogue.setString("");
	isHeartChosen = false;
	description_tex.loadFromFile("Textures\\main_text_banner_opt.png");
	description.setTexture(description_tex);
}

void Options::arrowControl_opt(sf::RenderWindow& window, sf::Event& ev) {
	if (ev.type != sf::Event::KeyPressed) return;

	if (heart.getScale() == sf::Vector2f(0, 0)) {
		heart.setScale(sf::Vector2f(1, 1));
	}

	// вниз / вверх измен€ют индекс в диапазоне [0..3]
	if (ev.key.code == sf::Keyboard::Down) {
		if (button_count < 3) ++button_count;
	}
	else if (ev.key.code == sf::Keyboard::Up) {
		if (button_count > 0) --button_count;
	}
	else {
		return;
	}

	// —бросить все подсветки
	for (int i = 0; i < 3; ++i) button_options[i].setTexture(button_options_tex);
	back_button.setTexture(back_button_tex);

	// ѕрименить подсветку и позицию сердца дл€ текущего индекса
	if (button_count >= 0 && button_count <= 2) {
		button_options[button_count].setTexture(button_options_light_tex);
		heart.setPosition(
			button_options[button_count].getPosition().x + button_options[button_count].getGlobalBounds().width - 70.f,
			button_options[button_count].getPosition().y + button_options[button_count].getGlobalBounds().height / 4.f + 15.f
		);
	}
	else { // button_count == 3 -> back_button
		back_button.setTexture(back_button_light);
		heart.setPosition(
			back_button.getPosition().x + back_button.getGlobalBounds().width - 70.f,
			back_button.getPosition().y + back_button.getGlobalBounds().height / 4.f + 15.f
		);
	}

	isHeartChosen = true;
	if (button_count == 3) {
		heart.setScale(sf::Vector2f(0,0));
	}
}

Options::~Options()
{
}
