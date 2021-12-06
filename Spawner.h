#pragma once
#include "Enemy.h"
#include "Tile.h"

class Tile;

class Spawner
	: public Tile
{
private:
	sf::RectangleShape shape;
	//sf::Vector2f position;
	sf::Vector2i gridPosition;
	int enemnyType, enemyAmount, enemyTimeToSpawn, enemyMaxDistance;

public:
	Spawner(int grid_x, int grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& tex_rect,
		 int enemy_type, int enemy_amount, int enemy_time_to_spawn, float enemy_max_distance);
	virtual ~Spawner();

	// Accessor

	virtual const std::string getAsString() const;

	// modifiers


	// update / render
	void update();
	void render(sf::RenderTarget& target);
};

