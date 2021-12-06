#include "stdafx.h"
#include "Rat.h"

//Init

void Rat::initVariables()
{

}

void Rat::initAnimations()
{
	this->animationComponent->addAnimation("IDLE", 25.f, 0, 0, 3, 0, 60, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 1, 3, 1, 60, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 11.f, 0, 2, 3, 2, 60, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 0, 3, 3, 3, 60, 64);
	this->animationComponent->addAnimation("WALK_UP", 11.f, 0, 4, 3, 4, 60, 64);
	this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 1, 2, 60, 64);
}

// Constructor / Destructor

Rat::Rat(float x, float y, sf::Texture& texture_sheet)
	:Enemy()
{
	this->initVariables();
	this->createHitbox(this->sprite, 13.f, 39.f, 30.f, 30.f);
	this->createMovementComponent(50.f, 1600.f, 1000.f);
	this->createAnimationComponent(texture_sheet);
	this->setPosition(x, y);
	this->initAnimations();
}

Rat::~Rat()
{
}

void Rat::updateAnimation(const float& dt)
{
	if (this->movementComponent->getState(IDLEE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
}

void Rat::update(const float& dt, sf::Vector2f& mouse_pos_view)
{
	this->movementComponent->update(dt);
	//this->updateAttack();
	this->updateAnimation(dt);
	this->hitbox->update();
}

void Rat::render(sf::RenderTarget& target, const bool show_hitBox)
{
	target.draw(this->sprite);

	if (show_hitBox)
		this->hitbox->render(target);
	
}