#pragma once
#include "State.h"
#include "Button.h"
#include "PauseMenu.h"
#include "TileMap.h"

// Forward declarations
class State;
class PauseMenu;
class TileMap;

class EditorState :
    public State
{
private:
    // Variables
    Font font;
    PauseMenu* menu;

   // Button* gameState_btn;
    std::map<std::string, Button*> buttons;
    Text mouseText;

    TileMap* tileMap;

    sf::RectangleShape selectorRect;


    // init
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initPauseMenu();
    void initButtons();
    void initGui();
    void initTileMap();

public:
    EditorState(StateData* state_data);
    virtual ~EditorState();

    // Functions

    void updateInput(const float& dt);
    void updateButtons();
    void updateGui();
    void updatePause();
    void update(const float& dt);
    void renderButtons(RenderTarget& target);
    void renderGui(RenderTarget& target);
    void render(RenderTarget* target = NULL);
};

