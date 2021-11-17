#include "stdafx.h"
#include "Entity.h"

void Entity::initVariables()
{
	this->texture = NULL;
	this->sprite = NULL;
	this->movementSpeed = 100.f;
}

Entity::Entity()
{
	this->initVariables();
}

Entity::~Entity()
{
	delete this->sprite;
}

// Components
void Entity::createSprite(sf::Texture* texture)
{
	this->texture = texture;
	this->sprite->setTexture(*this->texture);
}

// Accessors
const sf::Vector2f& Entity::getPosition() const
{
	return this->sprite->getPosition();
}


// mutators
void Entity::setPosition(const float x, const float y)
{
	if (this->sprite)
	{
		this->sprite->setPosition(x, y);
	}
}

void Entity::move(const float & dt, const float dirx, const float diry)
{
	if (this->sprite) // if sprite exists
	{
		this->sprite->move(dirx * this->movementSpeed * dt, diry * this->movementSpeed * dt);
	}
}

void Entity::update(const float& dt)
{
	
}

void Entity::render(sf::RenderTarget* target)
{
	if (this->sprite) // if sprite exists
	{
		target->draw(*this->sprite);
	}
}
