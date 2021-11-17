#pragma once
#include "State.h"
//#include "Button.h"
#include "Gui.h"
#include "PauseMenu.h"
#include "TileMap.h"

// Forward declarations
class State;
class stateData;
class Gui;
class PauseMenu;
class TileMap;
class Tile;

class EditorState :
    public State
{
private:
    // Text variables
    Font font;
    Text cursorText;    // text that follows mouse within editor state
    PauseMenu* menu;

    // Camera variables
    sf::View view;
    int camSpeed;

    // map buttons
    std::map<std::string, gui::Button*> buttons;

    sf::RectangleShape sidebar;

    // Tile
    TileMap* tileMap;
    sf::IntRect textureRect;
    sf::RectangleShape selectorRect;

    gui::TextureSelector* textureSelector;

    bool collision;
    short type;

    // init
    void initVariables();
    void initView();
    void initBackground();
    void initFonts();
    void initText();
    void initKeybinds();
    void initPauseMenu();
    void initButtons();
    void initTileMap();
    void initGui();

public:
    EditorState(StateData* state_data);
    virtual ~EditorState();

    // Functions

    void updateInput(const float& dt);
    void updateEditorInput(const float& dt);
    void updateButtons();
    void updateGui(const float& dt);
    void updatePause();
    void update(const float& dt);
    void renderButtons(RenderTarget& target);
    void renderGui(RenderTarget& target);
    void render(RenderTarget* target = NULL);
};

