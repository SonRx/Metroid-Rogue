#include "stdafx.h"
#include "Entity.h"

void Entity::initVariables()
{
	this->hitbox = NULL;
	this->movementComponent = NULL;
	this->animationComponent = NULL;
	//this->skills = NULL;
	this->movementSpeed = 100.f;
}

Entity::Entity()
{
	this->initVariables();
}

Entity::~Entity()
{
	delete this->hitbox;
	delete this->movementComponent;
	delete this->animationComponent;
	//delete this->skills;
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
void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture & texture_sheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

// init Skills
void Entity::createSkills(const unsigned level)
{
	this->skills = new Skills(level);
}

// Accessors
const sf::Vector2f& Entity::getPosition() const
{
	if (this->hitbox)
		return this->hitbox->getPosition();

	return this->sprite.getPosition();
}

const sf::Vector2i Entity::getGridPosition(const int gridSizeI) const
{
	if (this->hitbox)
		return sf::Vector2i(static_cast<int>(this->hitbox->getPosition().x) / gridSizeI,
							static_cast<int>(this->hitbox->getPosition().y) / gridSizeI);

	return sf::Vector2i(static_cast<int>(this->sprite.getPosition().x) / gridSizeI,
						static_cast<int>(this->sprite.getPosition().y) / gridSizeI);
}

const sf::FloatRect Entity::getGlobalBounds() const
{
	if (this->hitbox)
		return this->hitbox->getGlobalBounds();

	return this->sprite.getGlobalBounds();
}

const sf::FloatRect& Entity::getNextPosBounds(const float& dt) const
{
	if (this->hitbox)
	{
		return this->hitbox->getNextPosition(this->getVelocity() * dt);
	}
	return FloatRect(-1.f,-1.f,-1.f,-1.f); // return new position
}

const sf::Vector2f& Entity::getVelocity() const
{
	return this->velocity;
}

MovementComponent* Entity::getMovementComponent()
{
	return this->movementComponent;
}

AnimationComponent* Entity::getAnimationComponent()
{
	return this->animationComponent;
}

// mutators
void Entity::setPosition(const float x, const float y)
{
	if (this->hitbox)
	{
		this->hitbox->setPosition(x, y);
	}
	else
		this->sprite.setPosition(x, y);
}

void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
	if (this->movementComponent)
		this->movementComponent->move(dir_x, dir_y, dt); //Sets velocity
}

void Entity::resetVelocity()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocity();
}

void Entity::resetVelocityX()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityX();
}

void Entity::resetVelocityY()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityY();
}

void Entity::update(const float& dt, sf::Vector2f& mouse_pos_view)
{
	
}

void Entity::render(sf::RenderTarget& target, const bool show_hitbox)
{
}
