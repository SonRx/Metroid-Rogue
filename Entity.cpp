#include "stdafx.h"
#include "Entity.h"

void Entity::initVariables()
{
	this->hitbox = NULL;
	this->movementSpeed = 100.f;
}

Entity::Entity()
{
	this->initVariables();
}

Entity::~Entity()
{
	delete this->hitbox;
}

// Components
void Entity::createSprite(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Entity::createHitbox(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height)
{
	this->hitbox = new Hitbox(sprite, offset_x, offset_y, width, height);
}

// Accessors
const sf::Vector2f& Entity::getPosition() const
{
	if (this->hitbox)
		return this->hitbox->getPosition();

	return this->sprite.getPosition();
}

const sf::FloatRect Entity::getGlobalBounds() const
{
	if (this->hitbox)
		return this->hitbox->getGlobalBounds();

	return this->sprite.getGlobalBounds();
}


// mutators
void Entity::setPosition(const float x, const float y)
{
	if (this->hitbox)
	{
		this->hitbox->setPosition(x, y);
	}
}

void Entity::move(const float & dt, const float dirx, const float diry)
{
	if (&this->sprite) // if sprite exists
	{
		this->sprite.move(dirx * this->movementSpeed * dt, diry * this->movementSpeed * dt);
	}
}

void Entity::update(const float& dt)
{
	
}

void Entity::render(sf::RenderTarget& target)
{
}
