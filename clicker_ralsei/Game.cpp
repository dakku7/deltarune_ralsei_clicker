#include "Game.h"
#include "Ralsei.h"
#include "Heart.h"
//#define DEBUG

Game::Game()
	: window(sf::VideoMode({ 800, 600 }), "CLICK", sf::Style::Default),
	main_view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_WIDTH)),
	game_scene(assets, player)
{
	handleResize();
	loadTextures();
	initSprites();
#ifdef DEBUG
	std::cout << "Booleans skins: off: " + std::to_string(player.getRalseiSkinstatus(1)) + ", dino: " + std::to_string(player.getRalseiSkinstatus(2)) + ", rock: " + std::to_string(player.getRalseiSkinstatus(3)) + '\n';
#endif // DEBUG

	backup.loadupFiles(player);
	player.setVariables();

#ifdef DEBUG
	std::cout << "Booleans skins: off: " + std::to_string(player.getRalseiSkinstatus(1)) + ", dino: " + std::to_string(player.getRalseiSkinstatus(2)) + ", rock: " + std::to_string(player.getRalseiSkinstatus(3)) + '\n';
#endif // TEST
	
	center.setOrigin(
		static_cast<float>(assets.getTexture(TextureID::center_tex).getSize().x) / 2.f,
		static_cast<float>(assets.getTexture(TextureID::center_tex).getSize().y) / 2.f
	);
	center.setPosition(
		static_cast<float>(window.getSize().x) / 2.f,
		static_cast<float>(window.getSize().y) / 2.f
	);
	ralseiGroundOffset =200;

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

	ResizeView(window, main_view);
	
	
	theme.play();
	player.count_text.setPosition(400, 500);
	menu_guide.setPosition(0 + 5, 600 - menu_guide.getCharacterSize() - 5);

	window.setFramerateLimit(60);
	while (window.isOpen())
	{
		float dt = clock.restart().asSeconds();
		sf::Event event;
		while (window.pollEvent(event)) {
			if (game_ev.isOpen()) {
				continue;
			}
			handleEvents(event);
		}	

		if (player.countToLevelCheck()) {
			player.levelCheck(player.level);
			anim.startLevelUp(player.level, levelUpState);
			player.updateText(player.level_text, player.level);
		}
		
		if (anim.timeAnim) {
			anim.updateLevelUp(window, levelUpState);
		}

	//new 
		update(dt, &window);
		render();
	}

	backup.backupFiles(player);
	return false;
}

//loop
void Game::render()
{
	float dt = clock.restart().asSeconds();

	background.setPosition(sf::Vector2f(0, 0));

	main_view.setCenter(center.getPosition());
	window.clear();
	window.draw(background);
	window.setView(main_view);

//main char
	game_scene.render(&window);
	
//window.setView(window.getDefaultView());
	player.count_text.setPosition(400 - player.count_text.getCharacterSize(), 500);

//obj
	player.count_text.setCharacterSize((window.getSize().x / window.getSize().y) * 24);
	window.draw(player.count_text);

//text
	window.draw(menu_guide);
	
	
	if (anim.timeAnim) {
		anim.draw(window);
	}
//	window.draw(center);

	if (game_ev.isOpen()) {
		game_ev.draw(window);
	}
	window.display();
}

void Game::update(float dt, sf::RenderWindow* window)
{

	game_scene.update(dt, *window);

}

//textrs
void Game::initSprites()
{
	center.setTexture(assets.getTexture(TextureID::center_tex));
	background.setTexture(assets.getTexture(TextureID::Background));

	game_scene.init(window.getSize());
}

void Game::loadTextures()
{
	assets.loadTexture(TextureID::Ralsei_Main);
	assets.loadTexture(TextureID::Ralsei_skin_1);
	assets.loadTexture(TextureID::Ralsei_skin_1_locked);
	assets.loadTexture(TextureID::Ralsei_skin_1_frame);
	assets.loadTexture(TextureID::Ralsei_skin_1_locked_light);
	assets.loadTexture(TextureID::Ralsei_skin_2);
	assets.loadTexture(TextureID::Ralsei_skin_2_locked);
	assets.loadTexture(TextureID::Ralsei_skin_2_locked_light);
	assets.loadTexture(TextureID::Ralsei_skin_2_frame);
	assets.loadTexture(TextureID::Ralsei_skin_3);
	assets.loadTexture(TextureID::Ralsei_skin_3_frame);
	assets.loadTexture(TextureID::Ralsei_skin_3_locked);
	assets.loadTexture(TextureID::Ralsei_skin_3_locked_light);

	assets.loadTexture(TextureID::Background);
	assets.loadTexture(TextureID::Heart);
	assets.loadTexture(TextureID::Heart_empty);
	assets.loadTexture(TextureID::center_tex);

}



//fullscreen
void Game::ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = static_cast<float>(window.getSize().x) /
		static_cast<float>(window.getSize().y);

	//float aspectRatio = float(window.getSize().x / float(window.getSize().y));
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

void Game::toggleFullScreen()
{
	FULLSCREEN = !FULLSCREEN;
	window.close();

	if (FULLSCREEN) {
		window.create(
			sf::VideoMode::getDesktopMode(),
			"CLICK",
			sf::Style::Fullscreen
		);

	}
	else if (!FULLSCREEN) {
		window.create(
			sf::VideoMode(VIEW_WIDTH, VIEW_HEIGHT),
			"CLICK",
			sf::Style::Titlebar | sf::Style::Close
		);
	}

	window.setFramerateLimit(60);
	handleResize();
}


//handlers
void Game::handleResize()
{
	sf::Vector2u windowSize = window.getSize();

	if (windowSize.x == 0 || windowSize.y == 0) return;

	main_view.setSize(800.f, 600.f);
	main_view.setCenter(400.f, 300.f);

	float windowRatio = static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y);
	float gameRatio = 800.f / 600.f; 

	float sizeX = 1.f;
	float sizeY = 1.f;
	float posX = 0.f;
	float posY = 0.f;

	if (windowRatio > gameRatio)
	{
		sizeX = gameRatio / windowRatio;
		posX = (1.f - sizeX) / 2.f;
	}
	else
	{
		sizeY = windowRatio / gameRatio;
		posY = (1.f - sizeY) / 2.f;
	}

	main_view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
	window.setView(main_view);
	window.setFramerateLimit(60);
}

void Game::handleEvents(sf::Event& ev)
{
	switch (ev.type)
	{

	case sf::Event::Closed:
		window.close();
		break;

	case sf::Event::MouseButtonPressed:
		handleClick(ev);
		break;

		break;
	case sf::Event::KeyPressed:
		if (ev.key.code == sf::Keyboard::Escape) {
			window.close();
		}

		if (ev.key.code == sf::Keyboard::C && !isKeyPressed && !levelUpState) {
			isKeyPressed = true;
			player.Add_clickCount(ev);
			handleClick(ev);

		}

		if (ev.key.code == sf::Keyboard::Z) {
			menu_.draw(player, window);
		}

		if (ev.key.code == sf::Keyboard::Num0) {
			player.Add_clickCount(999);

			player.updateText(player.count_text, player.Get_clickCount());
		}

		if (ev.key.code == sf::Keyboard::F1) {
			player.reset();
			game_scene.resetSkin();
			backup.backupFiles(player);
		}

		if (ev.key.code == sf::Keyboard::Num9) {
			game_scene.resetSkin();

		}

		if (ev.key.code == sf::Keyboard::F2) {
			game_ev.run();
		}

		if (ev.key.code == sf::Keyboard::Enter && ev.key.alt)
		{
			toggleFullScreen();
		}

		break;
	case sf::Event::KeyReleased:
		if (ev.key.code == sf::Keyboard::C) {
			isKeyPressed = false;
		}
		break;
	default:
		break;
	}
}

void Game::handleClick(sf::Event& ev)
{
	sf::Vector2i mouse_pos = sf::Vector2i(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
	sf::Vector2f world_pos = window.mapPixelToCoords(mouse_pos, main_view);

	if (world_pos.x < 0 || world_pos.x > 800 || world_pos.y < 0 || world_pos.y > 600) {
		return;
	}
	game_scene.handleClick(world_pos, player, window, ev);
}

Game::~Game()
{
}

