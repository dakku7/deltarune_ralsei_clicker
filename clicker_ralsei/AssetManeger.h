#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <iostream>

enum class TextureID {
	//scene
	Background,
	center_tex,

	//ralsei skins
	Ralsei_Main,
	Ralsei_skin_1st,
	Ralsei_skin_2nd,
	Ralsei_skin_3rd,

	//locked frames
	Ralsei_skin_1st_locked,
	Ralsei_skin_2nd_locked,
	Ralsei_skin_3rd_locked,

	//unlocked frames
	Ralsei_skin_1st_frame,
	Ralsei_skin_2nd_frame,
	Ralsei_skin_3rd_frame,

	//heart
	Heart,
	Heart_empty,

	//trees
	Tree_1,
	Tree_2,
	Tree_3,
	Tree_4,
	Tree_5,
	Tree_6,
	Tree_7,
	Tree_8,
	Tree_9,
	Tree_10,
	Tree_11,	
	Tree_12,
	Tree_13,
	Tree_14,
	Tree_15,
	Tree_16,
	Tree_17,
	Tree_18,
	Tree_19,
	Tree_20,

};

class AssetManager {
public:
	bool loadTexture(TextureID id);
	const sf::Texture getTexture(TextureID);
private:
	std::unordered_map<TextureID, std::unique_ptr<sf::Texture>> textures;

	std::string getPath(TextureID id);
};