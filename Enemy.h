#pragma once
#include "Entity.h"

class Enemy :
    public Entity
{
private:



    // init functions
    void initVariables();
    void initAnimations();

public:
    Enemy(float x, float y, sf::Texture& texture_sheet);
    virtual ~Enemy();

    // update / render
    void updateAnimation(const float& dt);
    void update(const float& dt, sf::Vector2f& mouse_pos_view);
    void render(sf::RenderTarget& target, const bool show_hitBox);
};

