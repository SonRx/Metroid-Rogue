#pragma once
#include "Tile.h"
#include "Entity.h"
#include "Player.h"
#include "RegularTile.h"
#include "EnemySystem.h"

class Tile; // forward declaration
class Entity;
class Player;
class SpawnerTile;


class TileMap
{
private:
	float gridSizeF;	// float
	int gridSizeI;		// int
	unsigned layers;

	sf::Vector2i maxSizeGrid; // of the grid
	sf::Vector2f maxSizeWorld; // of the world

	vector< vector< vector <vector <Tile*> > > > map; // x y z k
	stack<Tile*> queueRenderStack;

	// init texture file locator
	string textureFile;		
	sf::Texture tileSheet;
	sf::RectangleShape collisionBox;

	// Culling
	int fromX, toX, fromY, toY, layer;
	void clear();

public:
	TileMap(float gridSize, int width, int height, std::string texture_file);
	TileMap(const std::string file_name);
	virtual ~TileMap();

	// Accessors
	const sf::Texture* getTileSheet() const;
	const int getLayerSize(const int x, const int y, const int layer) const;
	const sf::Vector2i& getMaxSizeGrid() const;
	const sf::Vector2f& getMaxSizeWorld() const;
	const bool isTileEmpty(const int x, const int y, const int z) const;
	const bool checkType(const int x, const int y, const int z, const int type) const;

	// Mutators
	void addTile(const int x, const int y, const int z, const sf::IntRect& tex_rect, const bool collision, const short& type);
	void addTile(const int x, const int y, const int z, const sf::IntRect& tex_rect, const int enemy_type, const int enemy_am, const int enemy_tts, const int enemy_md);
	void removeTile(const int x, const int y, const int z, const int type = -1);

	// Save Editor to game
	void saveFile(const std::string file_name);
	void loadFile(const std::string file_name);

	// update
	//void updateCollision(Entity* entity, const float& dt);
	void updateWorldBoundsCollision(Entity* entity, const float& dt); // check aorund screen
	void updateTileCollision(Entity* entity, const float& dt);
	void updateTiles(Entity* entity, const float& dt, EnemySystem& enemySystem);
	void update(Entity* entity, const float& dt);
	//virtual void update();

	// render
	void render(RenderTarget& target, const Vector2i& gridPos, const bool show_collision = false);
	void queueRender(RenderTarget& target);
};

