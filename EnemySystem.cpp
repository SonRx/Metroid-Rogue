#include "stdafx.h"
#include "EnemySystem.h"

EnemySystem::EnemySystem(std::vector<Enemy*>& activeEnemies, std::map<std::string, sf::Texture>& textures)
	: textures(textures), activeEnemies(activeEnemies)
{
	this->textures = textures;
	this->activeEnemies = activeEnemies;
}

EnemySystem::~EnemySystem()
{
}

void EnemySystem::createEnemy(const short type, const float xPos, const float yPos)//, SpawnerTile& spawner_tile)
{
	switch (type)
	{
		case EnemyTypes::RAT:
			this->activeEnemies.push_back(new Rat(xPos, yPos, this->textures["RAT1_SHEET"]));
			break;
		default:
			cout << "DOES NOT EXIST" << "\n";
			break;
	}
}

void EnemySystem::update(const float& dt)
{
}

void EnemySystem::render(sf::RenderTarget* target)
{
}
