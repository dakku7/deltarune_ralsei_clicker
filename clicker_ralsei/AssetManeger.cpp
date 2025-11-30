#include "AssetManager.h"

bool AssetManager::loadTexture(TextureID id)
{
    if (textures.find(id) != textures.end())
        return true;

    auto tex = std::make_unique<sf::Texture>();
    std::string path = getPath(id);
    if (path.empty()) {
        std::cout << "No path for TextureID=" << static_cast<int>(id) << "\n";
        return false;
    }

    if (!tex->loadFromFile(path)) {
        std::cout << "Error loading texture: " << path << "\n";
        return false;
    }
    textures.emplace(id, std::move(tex));
    return true;
}

std::string AssetManager::getPath(TextureID id) 
{
    switch (id)
    {
        // -------- scene --------
    case TextureID::Background: return "Textures\\Chapter1\\background.png";
    case TextureID::center_tex: return "Textures\\chp1.png";

        // -------- ralsei skins --------
    case TextureID::Ralsei_Main:        return "Textures\\ralss.png";
    case TextureID::Ralsei_skin_1:    return "Textures\\ralss1.png";
    case TextureID::Ralsei_skin_2:    return "Textures\\ralss2.png";
    case TextureID::Ralsei_skin_3:    return "Textures\\ralss3.png";

        // -------- locked frames --------
    case TextureID::Ralsei_skin_1_locked: return "Textures\\skin1lock.png";
    case TextureID::Ralsei_skin_2_locked: return "Textures\\skin2lock.png";
    case TextureID::Ralsei_skin_3_locked: return "Textures\\skin3lock.png";

        // -------- unlocked button frames --------
    case TextureID::Ralsei_skin_1_frame: return "Textures\\skin_1_frame.png";
    case TextureID::Ralsei_skin_1_lighted: return "Textures\\skin_1_lighted.png";
    case TextureID::Ralsei_skin_2_frame: return "Textures\\skin2.png";
    case TextureID::Ralsei_skin_3_frame: return "Textures\\skin3.png";

        // -------- heart --------
    case TextureID::Heart:       return "Textures\\heart.png";
    case TextureID::Heart_empty: return "Textures\\heart_empty.png";

        // -------- trees 1–20 --------
    case TextureID::Tree_1: return "Textures\\Chapter1\\Trees\\tree__1.png";
    case TextureID::Tree_2: return "Textures\\Chapter1\\Trees\\tree__2.png";
    case TextureID::Tree_3: return "Textures\\Chapter1\\Trees\\tree__3.png";
    case TextureID::Tree_4: return "Textures\\Chapter1\\Trees\\tree__4.png";
    case TextureID::Tree_5: return "Textures\\Chapter1\\Trees\\tree__5.png";
    case TextureID::Tree_6: return "Textures\\Chapter1\\Trees\\tree__6.png";
    case TextureID::Tree_7: return "Textures\\Chapter1\\Trees\\tree__7.png";
    case TextureID::Tree_8: return "Textures\\Chapter1\\Trees\\tree__8.png";
    case TextureID::Tree_9: return "Textures\\Chapter1\\Trees\\tree__9.png";
    case TextureID::Tree_10: return "Textures\\Chapter1\\Trees\\tree__10.png";
    case TextureID::Tree_11: return "Textures\\Chapter1\\Trees\\tree__11.png";
    case TextureID::Tree_12: return "Textures\\Chapter1\\Trees\\tree__12.png";
    case TextureID::Tree_13: return "Textures\\Chapter1\\Trees\\tree__13.png";
    case TextureID::Tree_14: return "Textures\\Chapter1\\Trees\\tree__14.png";
    case TextureID::Tree_15: return "Textures\\Chapter1\\Trees\\tree__15.png";
    case TextureID::Tree_16: return "Textures\\Chapter1\\Trees\\tree__16.png";
    case TextureID::Tree_17: return "Textures\\Chapter1\\Trees\\tree__17.png";
    case TextureID::Tree_18: return "Textures\\Chapter1\\Trees\\tree__18.png";
    case TextureID::Tree_19: return "Textures\\Chapter1\\Trees\\tree__19.png";
    case TextureID::Tree_20: return "Textures\\Chapter1\\Trees\\tree__20.png";
    }
    return "";
}

const sf::Texture& AssetManager::getTexture(TextureID id)
{
    auto it = textures.find(id);
    if (it == textures.end()) {
        std::cout << "Requested texture not loaded: " << static_cast<int>(id) << "\n";
    }
    return *(it->second);
}
