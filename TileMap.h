#pragma once
#include "Tile.h"

class TileMap
{
private:
	float gridSizeF;	// float
	unsigned gridSizeU; // unsigned
	sf::Vector2u maxSize;
	unsigned layers;
	vector< vector< vector <Tile*> > > map; // x y z

	// init texture file locator
	string textureFile;		
	sf::Texture tileSheet;

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
	void update();

	// render
	void render(sf::RenderTarget& target);
};

