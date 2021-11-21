#pragma once
#include "Tile.h"
#include "Entity.h"

class Tile; // forward declaration
class Entity;

class TileMap
{
private:
	float gridSizeF;	// float
	unsigned gridSizeU; // unsigned

	sf::Vector2u maxSizeGrid; // of the grid
	sf::Vector2f maxSizeWorld; // of the world

	unsigned layers;
	vector< vector< vector <Tile*> > > map; // x y z

	// init texture file locator
	string textureFile;		
	sf::Texture tileSheet;
	sf::RectangleShape collisionBox;
	void clear();

public:
	TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file);
	virtual ~TileMap();

	// Accessors
	const sf::Texture* getTileSheet() const;

	// Mutators
	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& tex_rect, const bool collision, const short type);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);

	// Save Editor to game
	void saveFile(const std::string file_name);
	void loadFile(const std::string file_name);

	// update
	void updateCollision(Entity* entity);
	void update();

	// render
	void render(sf::RenderTarget& target, Entity* entity = NULL);
};

