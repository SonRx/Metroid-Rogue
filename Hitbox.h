#pragma once

class Hitbox
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	sf::FloatRect nextPosition;
	float offsetX;
	float offsetY;

public:
	Hitbox(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
	virtual ~Hitbox();

	// Accessors
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);

	// Modifiers
	/* Overloading setPosition */
	void setPosition(const sf::Vector2f& position);
	void setPosition(const float x, const float y);

	bool intersects(const sf::FloatRect& frect);

	// Update
	void update();

	// Render
	void render(sf::RenderTarget& target);
};


