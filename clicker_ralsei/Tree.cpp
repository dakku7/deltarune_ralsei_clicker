#include "Tree.h"

Tree::Tree(AssetManager& manager)
    : ass_mgr(manager)
{
    initSprites(ass_mgr);
    initAnimations();

	tree.setTexture(tree_tex[0]);
    tree.setOrigin(tree.getGlobalBounds().width / 2, tree.getGlobalBounds().height / 2);
    tree.setScale(sf::Vector2f(0.9f, 0.9f));


}

void Tree::initSprites(AssetManager& asset_mgr)
{
    for (int i = 0; i < 20; i++)
    {
        TextureID id = static_cast<TextureID>(static_cast<int>(TextureID::Tree_1) + i);
        asset_mgr.loadTexture(id);
        frames_tex.push_back(&asset_mgr.getTexture(id));
    }
}

void Tree::initAnimations()
{
    idleAnimation = std::make_unique<Anim>(&tree, frames_tex, frameTime);
}

void Tree::update(float dt) {
    if (idleAnimation) {
        idleAnimation->update(dt);
    }
}


void Tree::render(sf::RenderTarget* target)
{
    target->draw(this->tree);
}

void Tree::setPosition(sf::Vector2f pos)
{
    tree.setPosition(pos);
}

sf::Vector2f Tree::getPosition() {
    return tree.getPosition();
}

Tree::~Tree()
{
}
