#pragma once
#include "SpawnerTile.h"
#include "Enemy.h"
#include "Rat.h"

enum EnemyTypes { RAT = 0, BIRD};

class EnemySystem
{
private:
	std::map<std::string, sf::Texture>& textures;

	std::vector<Enemy*>& activeEnemies;

	//Entity& player;

public:
	EnemySystem(std::vector<Enemy*>& activeEnemies,
		std::map<std::string, sf::Texture>& textures);// , Entity& player);
	virtual ~EnemySystem();


	//Modifiers
	void createEnemy(const short type, const float xPos, const float yPos);//, SpawnerTile& spawner_tile);
	void removeEnemy(const int index);

	// update / render

	void update(const float& dt);
	void render(sf::RenderTarget* target);
};
