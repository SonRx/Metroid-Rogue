#pragma once

enum TileTypes {DEFAULT = 0, DAMAGING};

class Tile
{
private:
	//sf::Sprite sprite;
	//const bool damaging;

protected:
	sf::RectangleShape shape;
	bool collision;
	short type;

public:
	//Constructors
	Tile();
	Tile(unsigned grid_x, unsigned grid_y, float gridSizeF,const sf::Texture& texture, const sf::IntRect& tex_rect, bool collision = false, short type = TileTypes::DEFAULT);
	//Tile(sf::Texture& texture_sheet, sf::IntRect texture_rect, bool damaging = false);

	virtual ~Tile();

	// Accessors
	const sf::FloatRect getGlobalBounds() const;
	const std::string getAsString() const;

	//Modifers
	void update();

	//Rendering
	void render(sf::RenderTarget& target);
};
