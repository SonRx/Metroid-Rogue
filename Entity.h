#pragma once
#include "Hitbox.h"

class Hitbox;

class Entity
{
private:
	void initVariables();

	sf::Vector2f velocity;
	float velocityMax;
	float velocityMin;
	float acceleration;
	float drag;
	float gravity;		// Gravity may need to be fixed because character is not able to jump properly
	float velocityMaxY;

protected: // child class can access any member here
	sf::Texture* texture;
	sf::Sprite sprite;

	Hitbox* hitbox;

	//RectangleShape shape;
	float movementSpeed;

public:
	Entity();
	virtual ~Entity();

	// Components
	void createSprite(sf::Texture& texture);
	void createHitbox(sf::Sprite& sprite,float offset_x, float offset_y, float width, float height);

	// Accessors
	virtual const sf::Vector2f& getPosition() const;
	virtual const sf::Vector2i getGridPosition(const int gridSizeI) const;
	virtual const sf::FloatRect getGlobalBounds() const;
	virtual const sf::FloatRect& getNextPosBounds(const float& dt) const;
	virtual const sf::Vector2f& getVelocity() const;


	//mutators
	virtual void setPosition(const float x, const float y);
	virtual void move(const float& dt, const float x, const float y);

	virtual void resetVelocity();
	virtual void resetVelocityX();
	virtual void resetVelocityY();

	// Update
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target) = 0;
};

