#include "stdafx.h"
#include "Enemy.h"

// init
void Enemy::initVariables()
{

}

void Enemy::initAnimations()
{
	this->animationComponent->addAnimation("IDLE", 15.f, 0, 0, 8, 0, 64, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 1, 3, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 11.f, 4, 1, 7, 1, 64, 64);
	//this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 8, 1, 11, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 1, 1, 5, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_UP", 11.f, 12, 1, 15, 1, 64, 64);
	this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 1, 2, 64, 64);
}

// Constructor / Destructor
Enemy::Enemy(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->createHitbox(this->sprite, 12.f, 10.f, 40.f, 54.f);
	this->createMovementComponent(200.f, 1600.f, 1000.f);
	this->createAnimationComponent(texture_sheet);


	this->setPosition(x, y);
	this->initAnimations();
}

Enemy::~Enemy()
{

}

void Enemy::updateAnimation(const float& dt)
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

void Enemy::update(const float& dt, sf::Vector2f& mouse_pos_view)
{
	this->movementComponent->update(dt);
	//this->updateAttack();
	this->updateAnimation(dt);
	this->hitbox->update();
}

void Enemy::render(sf::RenderTarget& target, const bool show_hitBox)
{

	// render player -> called in game class
	target.draw(this->sprite);

	// RenderGUI
	//target.draw(this->playerHpBarBack);
	//target.draw(this->playerHpBar);

	// hitbox
	if (show_hitBox)
		this->hitbox->render(target);
}