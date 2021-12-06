#pragma once

#include "State.h"
#include "TileMap.h"
#include "Gui.h"

class State;
class StateData;
class TileMap;
class Tile;

class EditorStateData
{
public:
    EditorStateData() {};

    // variables
    View* view;

    Font* font;

    float* keytime, * keytimeMax;
    std::map<std::string, int>* keybinds;

    sf::Vector2i* mousePosScreen;
    sf::Vector2i* mousePosWindow;
    sf::Vector2f* mousePosView;
    sf::Vector2i* mousePosGrid;
};

class EditorMode
{
private:

protected:
	StateData* stateData;
    EditorStateData* editorStateData;
    TileMap* tileMap;

public:
	EditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
	virtual ~EditorMode();

    // Accessors
    const bool getKeytime();

	// Functions

    /* update / render */
    virtual void updateInput(const float& dt) = 0;
    virtual void updateGui(const float& dt) = 0;
    virtual  void update(const float& dt) = 0;

    virtual void renderGui(RenderTarget& target) = 0;
    virtual void render(RenderTarget& target) = 0;
};

