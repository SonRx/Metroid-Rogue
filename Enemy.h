#pragma once
#include "Entity.h"

#include "SpawnerTile.h"

class Entity;
class SpawnerTile;

class Enemy :
    public Entity
{
private:
   // Spawner& enemySpawner;


    // init functions
    virtual void initVariables() = 0;
    virtual void initAnimations() = 0;

public:
    /*Enemy(float x, float y, sf::Texture& texture_sheet);*/
    Enemy();
    virtual ~Enemy();

    // update / render
    /*virtual void updateAnimation(const float& dt) = 0;*/
    virtual void update(const float& dt, sf::Vector2f& mouse_pos_view) = 0;
    virtual void render(sf::RenderTarget& target, const bool show_hitBox) = 0;
};

