#include "stdafx.h"
#include "Weapon.h"
/*
Weapon::Weapon(Texture* texture, Vector2f position, Vector2f maxVelocity)
{
	this->texture = texture;
	this->sprite.setTexture(*this->texture);
	this->maxVelocity = maxVelocity;
}
*/
Weapon::Weapon(Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, 
	float movement_speed, float scalex, float scaley)
{
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(pos_x, pos_y);
	this->direction.x = dir_x;
	this->direction.y = dir_y;
	this->movementSpeed = movement_speed;
	this->sprite.scale(scalex,scaley);
}

Weapon::Weapon(Texture* texture, Vector2f position, Vector2f dir, float maxVel, float accel, float scale)
{
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(position);
	this->direction = dir;
	this->maxVelocity = maxVel;
	this->accel = scale*3.0; //0.5
	this->sprite.setScale(0.4*scale,0.4f);
}

Weapon::~Weapon()
{
}
// Accessors
const FloatRect Weapon::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const Vector2f Weapon::getPos() const
{
	return this->sprite.getPosition();
}

// Functions
void Weapon::update()
{
	if (this->accel > 0.f)
	{
		if (this->curVelocity.x < this->maxVelocity)
			this->curVelocity.x += this->accel * this->direction.x;

		if (this->curVelocity.y < this->maxVelocity)
			this->curVelocity.y += this->accel * this->direction.y;
	}

	else
	{
		this->curVelocity = Vector2f(
			this->maxVelocity * this->direction.x,
			this->maxVelocity * this->direction.y);
	}
	this->sprite.move(this->curVelocity);
}

void Weapon::render(RenderTarget* target)
{
	target->draw(this->sprite);
}
