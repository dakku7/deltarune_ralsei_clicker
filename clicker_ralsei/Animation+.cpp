#include "Animation+.h"

Anim::Anim(sf::Sprite* target, std::vector<sf::Texture*>& target_frames, float frame_time)
    : sprite(target), frames(target_frames), frameTime(frame_time)
{
    if (!frames.empty()) {
        sprite->setTexture(*frames[0]);
    }
}

void Anim::update(float dt)
{
    timer += dt;
    if (timer >= frameTime)
    {
        currentFrame++;

        if (currentFrame >= frames.size()) {
            currentFrame = 0;
        }

            sprite->setTexture(*frames[currentFrame]);

            timer = 0.f;
    }
}
