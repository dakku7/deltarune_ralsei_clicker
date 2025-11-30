#include "AssetManeger.h"

bool AssetManager::loadTexture(TextureID id)
{
    if (textures.count(id)) {
        return true;
    }

    auto tex = std::make_unique<sf::Texture>();

    if (!tex->loadFromFile(getPath(id)))
    {
        std::cout << "Error loading texture: " << getPath(id) << "\n";
        return false;
    }

    textures[id] = std::move(tex);
    return true;
}

std::string AssetManager::getPath(TextureID id) 
{
    switch (id)
    {
        // -------- scene --------
    case TextureID::Background: return "Textures/Chapter1/background.png";
    case TextureID::center_tex: return "Textures/center.png";

        // -------- ralsei skins --------
    case TextureID::Ralsei_Main:        return "Textures/ralss.png";
    case TextureID::Ralsei_skin_1st:    return "Textures/ralss1.png";
    case TextureID::Ralsei_skin_2nd:    return "Textures/ralss2.png";
    case TextureID::Ralsei_skin_3rd:    return "Textures/ralss3.png";

        // -------- locked frames --------
    case TextureID::Ralsei_skin_1st_locked: return "Textures/skin1lock.png";
    case TextureID::Ralsei_skin_2nd_locked: return "Textures/skin2lock.png";
    case TextureID::Ralsei_skin_3rd_locked: return "Textures/skin3lock.png";

        // -------- unlocked button frames --------
    case TextureID::Ralsei_skin_1st_frame: return "Textures/skin1.png";
    case TextureID::Ralsei_skin_2nd_frame: return "Textures/skin2.png";
    case TextureID::Ralsei_skin_3rd_frame: return "Textures/skin3.png";

        // -------- heart --------
    case TextureID::Heart:       return "Textures/heart.png";
    case TextureID::Heart_empty: return "Textures/heart_empty.png";

        // -------- trees 1–20 --------
    case TextureID::Tree_1: return "Textures/trees/tree__1.png";
    case TextureID::Tree_2: return "Textures/trees/tree__2.png";
    case TextureID::Tree_3: return "Textures/trees/tree__3.png";
    case TextureID::Tree_4: return "Textures/trees/tree__4.png";
    case TextureID::Tree_5: return "Textures/trees/tree__5.png";
    case TextureID::Tree_6: return "Textures/trees/tree__6.png";
    case TextureID::Tree_7: return "Textures/trees/tree__7.png";
    case TextureID::Tree_8: return "Textures/trees/tree__8.png";
    case TextureID::Tree_9: return "Textures/trees/tree__9.png";
    case TextureID::Tree_10: return "Textures/trees/tree__10.png";
    case TextureID::Tree_11: return "Textures/trees/tree__11.png";
    case TextureID::Tree_12: return "Textures/trees/tree__12.png";
    case TextureID::Tree_13: return "Textures/trees/tree__13.png";
    case TextureID::Tree_14: return "Textures/trees/tree__14.png";
    case TextureID::Tree_15: return "Textures/trees/tree__15.png";
    case TextureID::Tree_16: return "Textures/trees/tree__16.png";
    case TextureID::Tree_17: return "Textures/trees/tree__17.png";
    case TextureID::Tree_18: return "Textures/trees/tree__18.png";
    case TextureID::Tree_19: return "Textures/trees/tree__19.png";
    case TextureID::Tree_20: return "Textures/trees/tree__20.png";
    }
    return "";
}

const sf::Texture AssetManager::getTexture(TextureID)
{
    return sf::Texture();
}
