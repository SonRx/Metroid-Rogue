#include "stdafx.h"
#include "SpawnerTile.h"


SpawnerTile::SpawnerTile(int grid_x, int grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& tex_rect,
	 int enemy_type, int enemy_amount, int enemy_time_to_spawn, float enemy_max_distance)
	: Tile(TileTypes::ENEMYSPAWNER, grid_x, grid_y, gridSizeF, texture, tex_rect, false)
{
	//this->shape.setSize(sf::Vector2f(grid_size, grid_size));
	//this->shape.setFillColor(sf::Color::Red);

	//this->gridPosition = grid_position;
	this->enemnyType = enemy_type;
	this->enemyAmount = enemy_amount;
	this->enemyTimeToSpawn = enemy_time_to_spawn;
	this->enemyMaxDistance = enemy_max_distance;
	this->spawned = false;
}

SpawnerTile::~SpawnerTile()
{

}

const std::string SpawnerTile::getAsString() const
{
	std::stringstream ss; /* x,y,z,    type    rectx,recty,		enemy type, enemy amount, enemy tts, enemy max distance */


	ss << this->type << " " << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " " <<
		this->enemnyType << " " << this->enemyAmount << " " << this->enemyTimeToSpawn << " " << this->enemyMaxDistance;
	cout << ss.str() << endl;

	return ss.str();
}

const bool& SpawnerTile::getSpawned() const
{
	return this->spawned;
}

/* modifiers */
void SpawnerTile::setSpawned(const bool spawned)
{
	this->spawned = spawned;
}

/* update / render*/
void SpawnerTile::update()
{

}

void SpawnerTile::render(sf::RenderTarget& target)
{
	target.draw(shape);
}
