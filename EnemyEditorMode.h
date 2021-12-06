#pragma once
#include "EditorMode.h"
//#include "EnemySpawnerTile.h"

class State;
class StateData;
class EditorMode;
class TileMap;
class Tile;
class Spawner;

class EnemyEditorMode :
    public EditorMode
{
private:
	sf::Text cursorText;
	sf::RectangleShape sidebar;
	sf::RectangleShape selectorRect;
	sf::IntRect textureRect;

	int type;
	int amount;
	int timeToSpawn;
	float maxDistance;

	void initVariables();
	void initGui();

public:
	/* constructor / destructor*/
	EnemyEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
	virtual ~EnemyEditorMode();

	/* update / render */
	void updateInput(const float& dt);
	void updateGui(const float& dt);
	void update(const float& dt);

	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);

};

