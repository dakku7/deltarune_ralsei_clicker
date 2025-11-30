#include "Game.h"
//#define DEBUG

Game::Game()
	: window(sf::VideoMode({ 800, 600 }), "CLICK", sf::Style::Default),
	main_view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_WIDTH))
{
#ifdef DEBUG
	std::cout << "Booleans skins: off: " + std::to_string(player.getRalseiSkinstatus(1)) + ", dino: " + std::to_string(player.getRalseiSkinstatus(2)) + ", rock: " + std::to_string(player.getRalseiSkinstatus(3)) + '\n';
#endif // DEBUG

	backup.loadupFiles(player);
	player.setVariables();

#ifdef DEBUG
	std::cout << "Booleans skins: off: " + std::to_string(player.getRalseiSkinstatus(1)) + ", dino: " + std::to_string(player.getRalseiSkinstatus(2)) + ", rock: " + std::to_string(player.getRalseiSkinstatus(3)) + '\n';
#endif // TEST

	backup.setTextures(player, ralsei, background, ralsei_texture, background_tex, skins_tex_orig, skins_tex_button, skins, heartLvl, heart_texture, heartEmpty, heartEmpty_texture, menu_guide);
	
	
	center_tex.loadFromFile("Textures\\chp1.png");
	center.setTexture(center_tex);
	center.setOrigin(
		static_cast<float>(center_tex.getSize().x) / 2.f,
		static_cast<float>(center_tex.getSize().y) / 2.f
	);
	center.setPosition(
		static_cast<float>(window.getSize().x) / 2.f,
		static_cast<float>(window.getSize().y) / 2.f
	);
	ralseiGroundOffset =200;
	setPositionRalsei();
	theme.openFromFile("Audio\\lantern.wav");
	theme.setLoop(true);
	theme.setVolume(20);
}



//main process
bool Game::run()
{
	if (window.isOpen()) {
		backup.loadupFiles(player);
	}
	else return false;
	theme.play();

	sf::FloatRect heartBounds = heartEmpty.getLocalBounds();
	heartEmpty.setOrigin(heartBounds.width / 2.f, heartBounds.height / 2.f);
	heartEmpty.setPosition(150, 200);
	heartLvl.setOrigin(heartBounds.width / 2.f, heartBounds.height / 2.f);
	heartLvl.setPosition(150, 200);
	centerLvl(player.level_text);
	player.count_text.setPosition(400, 500);
	menu_guide.setPosition(0 + 5, 600 - menu_guide.getCharacterSize() - 5);
	first_tree.setTree(sf::Vector2f(185, 155));
	second_tree.setTree(sf::Vector2f(800 - 185, 160-5));


	auto size = window.getSize();
	auto pos = window.getPosition();

	for (int i = 0, j = 0; i < 3; ++i)
	{
		skins[i].setSize(sf::Vector2f(100.0f,100.0f));
		skins[i].setPosition(sf::Vector2f(800-100, j));
		skins[i].setFillColor(sf::Color::White);
		j += 100;
	}
	window.setFramerateLimit(60);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) {
			if (game_ev.isOpen()) {
				continue;
			}

			switch (event.type)
			{

			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				checkWindowSize();
				applyIntegerScaling();
				break;
			case sf::Event::MouseButtonPressed:
				if (player.click(ralsei, window, event, main_view)) {
					anim.startClicked(ralsei);
				}
				
				for (int i = 0; i < 3; i++) {
					player.click(ralsei, skins[i], window, event, main_view, i + 1, skins_tex_orig, i);
				}
#ifdef DEBUG
				std::cout << "Booleans skins: off: " + std::to_string(player.getRalseiSkinstatus(1)) + ", dino: " + std::to_string(player.getRalseiSkinstatus(2)) + ", rock: " + std::to_string(player.getRalseiSkinstatus(3)) + '\n';
#endif // !TEST
				break;

				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
				
				if (event.key.code == sf::Keyboard::C && !isKeyPressed && !levelUpState) {
					isKeyPressed = true;
					player.Add_clickCount(event);
					anim.startClicked(ralsei);
				}

				if (event.key.code == sf::Keyboard::Z) {
					menu_.draw(player, window);
				}
				
				if (event.key.code == sf::Keyboard::Num0) {
					player.Add_clickCount(999);
					
					player.updateText(player.count_text, player.Get_clickCount());
				}

				if (event.key.code == sf::Keyboard::F1) {
					player.reset(skins_tex_orig, skins_tex_button, skins);
					backup.backupFiles(player);
					ralsei.setTexture(ralsei_texture);
					centerLvl(player.level_text);
					setPositionRalsei();
				}

				if (event.key.code == sf::Keyboard::Num9) {
					ralsei.setTexture(ralsei_texture);					
					setPositionRalsei();
				//	ralsei.setPosition(sf::Vector2f(ralsei.getPosition().x, ralsei.getGlobalBounds().top - 20));
				}

				if (event.key.code == sf::Keyboard::F2) {
					game_ev.run();
				}
				
				if (event.key.code == sf::Keyboard::Enter &&
					(event.key.alt || sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)))
				{
					drawFullScreen();
				}
				
				break;
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::C) {
					isKeyPressed = false;
				}
				break;
			default:
				break;
			}	
		}	
		if (game_ev.isOpen()) {
			game_ev.update(event);
		}

		anim.updateModels(ralsei);
		updateHeart(player);

		if (player.countToLevelCheck()) {
			player.levelCheck(player.level);
			anim.startLevelUp(player.level, levelUpState);
			player.updateText(player.level_text, player.level);
			player.updateSkins(skins_tex_orig, skins_tex_button, skins);
			
			centerLvl(player.level_text);
		}
		
		ButtonHover(skins, 3,window);
		if (anim.timeAnim) {
			anim.updateLevelUp(window, levelUpState);
		}
		anim.fogUpdate();
		anim.sparkleSpawn();
		anim.sparkleUpdate();
		anim.lightSpawn();
		anim.lightUpdate();
		first_tree.anim();
		second_tree.anim();

		render();
	}

	backup.backupFiles(player);
	return false;
}


void Game::render()
{
	background.setPosition(sf::Vector2f(0, 0));

	main_view.setCenter(center.getPosition());
	window.clear();
	window.draw(background);
	window.setView(main_view);
	first_tree.draw(window);
	second_tree.draw(window);
//	anim.fogDraw(window);
//	anim.sparkeDraw(window);
//	anim.lightDraw(window);

//main char
	window.draw(ralsei);
	
	ResizeView(window, main_view);
//window.setView(window.getDefaultView());
	player.count_text.setPosition(400 - player.count_text.getCharacterSize(), 500);

//obj
	player.count_text.setCharacterSize((window.getSize().x / window.getSize().y) * 24);
	window.draw(heartEmpty);
	window.draw(heartLvl);
	updateHeart(player);

//text
	window.draw(player.count_text);
	window.draw(player.level_text);
	window.draw(menu_guide);
	
	for (int i = 0; i < 3; i++)
	{
		window.draw(skins[i]);
	}
	if (anim.timeAnim) {
		anim.draw(window);
	}
//	window.draw(center);

	if (game_ev.isOpen()) {
		game_ev.draw(window);
	}
	window.display();
}

void Game::setPositionRalsei()
{
    // выставл€ем origin у текущей текстуры ralsei на bottom-center
    if (ralsei.getTexture()) {
        const sf::Texture* tex = ralsei.getTexture();
        ralsei.setOrigin(static_cast<float>(tex->getSize().x) / 2.f, static_cast<float>(tex->getSize().y) );
    }

    // позици€ "дна" равна позиции center плюс дополнительный оффсет (если нужен)
    sf::Vector2f centerPos = center.getPosition();
    float groundY = centerPos.y + ralseiGroundOffset;

    // позиционируем ralsei так, чтобы его нижн€€ точка оказалась на groundY
    ralsei.setPosition(centerPos.x, groundY);
}

sf::Vector2f Game::GetRalseiPosition() 
{
	return ralsei.getPosition();
	 
}

void Game::ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = static_cast<float>(window.getSize().x) /
		static_cast<float>(window.getSize().y);

	//float aspectRatio = float(window.getSize().x / float(window.getSize().y));
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

void Game::checkWindowSize()
{
	if (window.getSize().x != 800) {
		window.setSize(sf::Vector2u(800, window.getSize().y));
	}
	if (window.getSize().y != 600) {
		window.setSize(sf::Vector2u(window.getSize().x, 600));

	}
}

void Game::ButtonHover(sf::RectangleShape* skins, int count, sf::RenderWindow& window)
{
	for (int i = 0; i < count; i++)
	{

		sf::Vector2i mousePos = sf::Mouse::getPosition(window);

		float x1 = skins[i].getPosition().x;
		float y1 = skins[i].getPosition().y;
		float x2 = x1 + skins[i].getSize().x;
		float y2 = y1 + skins[i].getSize().y;

		if ((mousePos.x >= x1) && (mousePos.x <= x2) && (mousePos.y >= y1) && (mousePos.y <= y2)) {
			skins[i].setFillColor(sf::Color(255, 255, 255, 150)); 
		}
		else {
			skins[i].setFillColor(sf::Color::White); 
		}
	}
}

void Game::updateHeart(Player& player)
{
	float fillPercent = static_cast<float>(player.Get_clickCount()) / player.click_equivalent_level(player.level);
	sf::Vector2u textureSize = heartLvl.getTexture()->getSize();
	fillPercent = std::clamp(fillPercent, 0.f, 1.f);

	int filledHeight = static_cast<int>(textureSize.y * fillPercent);

	sf::IntRect fillRectangle(0, textureSize.y - filledHeight, textureSize.x, filledHeight);

	
	heartLvl.setTextureRect(fillRectangle);
	heartLvl.setOrigin(textureSize.x / 2.f, textureSize.y); // точка прив€зки низ спрайта
	heartLvl.setPosition(heartEmpty.getPosition().x, heartEmpty.getPosition().y + heartEmpty_texture.getSize().y / 2 + (heartEmpty_texture.getSize().y - filledHeight));

}

void Game::centerLvl(sf::Text& level_text)
{
	sf::FloatRect textRect = player.level_text.getLocalBounds();
	player.level_text.setOrigin(textRect.left + textRect.width / 2.f,
		textRect.top + textRect.height / 2.f);
	player.level_text.setPosition(heartEmpty.getPosition());
}

void Game::applyIntegerScaling()
{
	int screenW = window.getSize().x;
	int screenH = window.getSize().y;

	float scaleX = (float)screenW / 800;
	float scaleY = (float)screenH / 600;

	float finalScale = std::floor(std::min(scaleX, scaleY));

	float finalWidth = 800 * finalScale;
	float finalHeight = 600 * finalScale;

	float offsetX = (screenW - finalWidth) / 2.f;
	float offsetY = (screenH - finalHeight) / 2.f;

	main_view.setViewport(sf::FloatRect(
		offsetX / screenW,
		offsetY / screenH,
		finalWidth / screenW,
		finalHeight / screenH
	));
}

void Game::drawFullScreen()
{
	isFullscreen = !isFullscreen;

	window.close();

	if (isFullscreen)
	{
		
		window.create(
			sf::VideoMode::getDesktopMode(),
			"CLICK",
			sf::Style::None // !!! ключ !!
		);
	}
	else
	{
		window.create(
			sf::VideoMode(800, 600),
			"CLICK",
			sf::Style::Default
		);
	}

	window.setFramerateLimit(60);

	applyIntegerScaling();
}

void Game::initSprites()
{
	
}

void Game::loadTextures()
{

}


Game::~Game()
{
}

