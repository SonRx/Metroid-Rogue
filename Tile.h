#pragma once

enum TileTypes {DEFAULT = 0, DAMAGING, OVERTILE, ENEMYSPAWNER};

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
	Tile(short type, int grid_x, int grid_y, float gridSizeF,const sf::Texture& texture, const sf::IntRect& tex_rect, const bool collision);
	//Tile(sf::Texture& texture_sheet, sf::IntRect texture_rect, bool damaging = false);

	virtual ~Tile();

	// Accessors
	virtual const sf::FloatRect getGlobalBounds() const;
	virtual const std::string getAsString() const = 0;
	virtual const sf::Vector2f& getPosition() const;
	virtual const bool intersects(const sf::FloatRect bounds) const;
	virtual const bool& getCollision() const;

	const short& getType() const; // is used in TileMap::Render()

	//Modifers
	
	virtual void update() = 0;

	//Rendering
	virtual void render(sf::RenderTarget& target) = 0;
};
