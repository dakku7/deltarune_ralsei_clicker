#include <fstream>
#include "Player.h"

class Backup {
private:
	sf::Font game_font;
public:
	Backup();

	void backupFiles(Player& player);
	void loadupFiles(Player& player);
	void setTextures(Player& player, sf::Sprite& ralsei, sf::Sprite& background, sf::Texture& ralsei_tex, sf::Texture& background_tex, std::map<int, sf::Texture>& skins_tex_orig, std::map<int, sf::Texture>& skins_tex_button, sf::RectangleShape* skins, sf::Sprite& heartlvl, sf::Texture& heart_texture, sf::Sprite& heartEmpty, sf::Texture& heartEmpty_texture, sf::Text& menu_guide_text);

	~Backup();
};