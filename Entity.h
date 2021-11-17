#pragma once

class Entity
{
private:
	void initVariables();

protected: // child class can access any member here
	sf::Texture* texture;
	sf::Sprite *sprite;

	//RectangleShape shape;
	float movementSpeed;

public:
	Entity();
	virtual ~Entity();

	// Components
	void createSprite(sf::Texture* texture);

	// Accessors
	virtual const sf::Vector2f& getPosition() const;

	//mutators
	virtual void setPosition(const float x, const float y);
	virtual void move(const float& dt, const float x, const float y);

	// Update
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
};

