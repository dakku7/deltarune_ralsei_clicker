#include "Backup.h"


Backup::Backup()
{
	game_font.loadFromFile("Data\\sans.otf");
}

void Backup::backupFiles(Player& player)
{
	std::ofstream saveFile("Data\\data.txt");
	saveFile << player.Get_clickCount() << std::endl;
	saveFile << player.level << std::endl;
	saveFile << player.get_clickPower();
}

void Backup::loadupFiles(Player& player)
{
	std::vector<int> data;
	std::ifstream saveData("Data\\data.txt");
	int click_buf;

	while (saveData >> click_buf)
	{	
		data.push_back(click_buf);
	}
	
	if (data.size() >= 3) {
		player.Set_clickCount(data[0]);
		player.level = data[1];
		player.Set_clickPower(data[2]);
	}

	player.updateText(player.count_text, player.Get_clickCount());
	player.updateText(player.level_text, player.level);
}

void Backup::setTextures(Player& player, sf::Sprite& ralsei, sf::Sprite& background, sf::Texture& ralsei_tex, sf::Texture& background_tex, std::map<int, sf::Texture>& skins_tex_orig, std::map<int, sf::Texture>& skins_tex_button, sf::RectangleShape* skins, sf::Sprite& heartlvl, sf::Texture& heart_texture, sf::Sprite& heartEmpty, sf::Texture& heartEmpty_texture, sf::Text& menu_guide_text)
{
	ralsei_tex.loadFromFile("Textures\\rals.png");
	background_tex.loadFromFile("Textures\\background.png");
	heart_texture.loadFromFile("Textures\\heart.png");
	heartEmpty_texture.loadFromFile("Textures\\heart_empty.png");
	heartlvl.setTexture(heart_texture);
	heartEmpty.setTexture(heartEmpty_texture);
	ralsei.setTexture(ralsei_tex);
	background.setTexture(background_tex);
	menu_guide_text.setFont(game_font);
	menu_guide_text.setString("Press Z - to open menu");
	
	for (int i = 1; i <= 3; ++i)
	{
		std::string origFile = "Textures\\rals" + std::to_string(i) + ".png";
		std::string skinFile = "Textures\\skin" + std::to_string(i) + ".png";
		std::string lockFile = "Textures\\skin" + std::to_string(i) + "lock.png";

		// грузим оригинал
		if (!skins_tex_orig[i].loadFromFile(origFile)) {
			std::cerr << "Error orig text " << skinFile << std::endl;
		}

		// грузим кнопку (открытая или закрытая)
		if (player.getRalseiSkinstatus(i)) {
			skins_tex_button[i].loadFromFile(skinFile);
		} 
		else {
			skins_tex_button[i].loadFromFile(lockFile);
		}


		skins[i - 1].setTexture(&skins_tex_button[i]);
	}
}



Backup::~Backup()
{
}
