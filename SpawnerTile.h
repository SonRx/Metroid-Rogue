#pragma once
#include "Enemy.h"
#include "Tile.h"

class Tile;

class SpawnerTile
	: public Tile
{
private:
	sf::RectangleShape shape;
	//sf::Vector2f position;
	sf::Vector2i gridPosition;
	int enemnyType, enemyAmount, enemyTimeToSpawn, enemyMaxDistance;
	bool spawned;

public:
	SpawnerTile(int grid_x, int grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& tex_rect,
		 int enemy_type, int enemy_amount, int enemy_time_to_spawn, float enemy_max_distance);
	virtual ~SpawnerTile();

	// Accessors

	virtual const std::string getAsString() const;
	const bool& getSpawned() const;

	// modifiers
	void setSpawned(const bool spawned);

	// update / render
	void update();
	void render(sf::RenderTarget& target);
};

