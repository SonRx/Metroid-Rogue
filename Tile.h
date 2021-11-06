#pragma once

class Tile
{
private:
	//sf::Sprite sprite;
	//const bool damaging;

protected:
	sf::RectangleShape shape;

public:
	//Constructors
	Tile();
	Tile(float x, float y, float gridSizeF);
	//Tile(sf::Texture& texture_sheet, sf::IntRect texture_rect, bool damaging = false);

	virtual ~Tile();

	// Accessors
	const sf::FloatRect getGlobalBounds() const;

	//Modifers
	void update();

	//Rendering
	void render(sf::RenderTarget& target);
};
