#include "Tree.h"

Tree::Tree()
{
	for (int i = 0; i < 20; i++)
	{
		tree_tex[i].loadFromFile("Textures\\Chapter1\\Trees\\tree__" + std::to_string(i + 1) + ".png");
    }

	tree.setTexture(tree_tex[0]);
    tree.setOrigin(tree.getGlobalBounds().width / 2, tree.getGlobalBounds().height / 2);
    tree.setScale(sf::Vector2f(0.9f, 0.9f));


}

void Tree::anim()
{
	float dt = clock.getElapsedTime().asSeconds();
    if (dt >= frameTime)
    {
        currentFrame++;

        if (currentFrame >= 20)
            currentFrame = 0;

        tree.setTexture(tree_tex[currentFrame]);

        clock.restart();
    }

}

void Tree::draw(sf::RenderWindow& window) 
{
    window.draw(tree);
}

void Tree::setTree(sf::Vector2f pos)
{
    tree.setPosition(pos);
}

Tree::~Tree()
{
}
