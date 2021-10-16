#pragma once
class Tile
{
private:
	sf::Sprite sprite;
	const bool damaging;

public:
	//Constructors
	Tile();
	Tile(sf::Texture& texture_sheet, sf::IntRect texture_rect, bool damaging = false);

	// Accessor
	const sf::FloatRect getGlobalBounds() const;

	//Modifers

	void update();


	//Rendering
	void render(sf::RenderTarget& target);
};
