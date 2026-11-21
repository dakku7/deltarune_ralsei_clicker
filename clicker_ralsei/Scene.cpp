#include "Scene.h"

Scene::Scene(AssetManager& assets, Player& p)
	: ass_mgr(assets), player(p)
{
}

void Scene::init(const sf::Vector2u& size)
{
	initMainCharacter(size);
	initBackground();	
	initButtons();
	initLvlSprite();
	initText();

}

void Scene::initMainCharacter(const sf::Vector2u& size)
{
	//Main Character
	auto ralsei = std::make_unique<Ralsei>(ass_mgr, ClickType::AddClick);
	ralsei_ptr = ralsei.get();

	ralsei->setPosition(sf::Vector2f(size.x / 2, size.y / 2 - 35));
	
	addClickable(ralsei.get());

	std::unique_ptr<Entity> ralseiEntity = std::move(ralsei);
	addEntity(std::move(ralseiEntity));
}

void Scene::initBackground()
{
	//Background Objects
	auto first_tree = std::make_unique<Tree>(ass_mgr);
	auto second_tree = std::make_unique<Tree>(ass_mgr);

	first_tree->setPosition(sf::Vector2f(185, 155));
	second_tree->setPosition(sf::Vector2f(800 - 185, 160 - 5));

	addEntity(std::move(first_tree));
	addEntity(std::move(second_tree));
}

void Scene::initButtons()
{
	//Buttons
	for (int i = 0, height = 1, locked = 6, unlocked = 12, skin = 1; i < 3; i++)
	{
		RalseiSkins skin_id = static_cast<RalseiSkins>(skin);


		auto button = std::make_unique<Button>(ClickType::Default,
			static_cast<TextureID>(unlocked), static_cast<TextureID>(unlocked + 1),
			static_cast<TextureID>(locked), static_cast<TextureID>(locked + 1),
			static_cast<RalseiSkins>(skin), &ass_mgr);

		button->setPosition(sf::Vector2f(800 - button->getSprite().getGlobalBounds().width, height));
		height += button->getSprite().getGlobalBounds().height;

		if (!player.getRalseiSkinstatus(i + 1)) {
			button->setEnabled(true);
		}
			
		button->setCallback([this, skin_id]() {
			if (this->player.getRalseiSkinstatus(static_cast<int>(skin_id))) {
				ralsei_ptr->setSkin(skin_id);
			}
			});
		
		addClickable(button.get());
		addEntity(std::move(button));

		locked += 2;
		unlocked += 2;
		skin += 1;
		int temp = static_cast<int>(skin_id);
		++temp;
		skin_id = static_cast<RalseiSkins>(temp);
	}
}

void Scene::initText()
{
	std::string ctr_buf;
	ctr_buf = std::to_string(player.Get_clickCount());
	click_text.setString(ctr_buf);
	click_text.setCharacterSize(800.f / 600.f);
}

void Scene::initLvlSprite()
{
	auto heart = std::make_unique<Heart>(ass_mgr);
	addEntity(std::move(heart));
}

void Scene::addEntity(std::unique_ptr<Entity> target) {
	entities.push_back(std::move(target));
}

void Scene::addClickable(Clickable* target) {
	clickables.push_back(std::move(target));
}

void Scene::update(float dt, sf::RenderWindow& window) {

	sf::Vector2f mousepos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	for (auto& it : entities) {
		it->update(dt);
		it->syncWithPlayer(player);
	}

	for (auto& it : clickables) {
		//fix dynamic cast in future, coz of its unpredictable behaviour
		if (auto* btn = dynamic_cast<Button*>(it))
			btn->setEnabled(!player.getRalseiSkinstatus(static_cast<int>(btn->getSkin())));

		bool hover = it->contains(mousepos);
		it->setHovered(hover);
		it->update(dt);
	}
}

void Scene::render(sf::RenderWindow* window) {
	for (auto& it : entities) {
		it->render(window);
	}

	for (auto& it : clickables) {
		it->render(window);
	}

	
}

void Scene::handleClick(sf::Vector2f& pos, Player& p, sf::RenderWindow& window, sf::Event& ev) {
	for (auto& it : clickables) {
		if (it->contains(pos)) {
			it->clicked();
			switch (it->getClickType())
			{
			case ClickType::Default:
				return;
				break;
			case ClickType::AddClick:
				p.addClick();
				break;
			default:
				break;
			}
		}
	}
}

void Scene::handleLvlChange(){
	if (player.countToLevelCheck()) {
		player.levelCheck(player.level);
//		anim.startLevelUp(player.level, levelUpState);
		player.updateText(player.level_text, player.level);
//		centerLvl(player.level_text);
		
	}
	
}

void Scene::setUpdateButtonFunc(std::function<void()> f)
{
	update_buttons = f;
}

void Scene::resetSkin() {
	if (ralsei_ptr) {
		ralsei_ptr->setSkin(RalseiSkins::Default);
	}
}