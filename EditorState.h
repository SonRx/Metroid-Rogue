#pragma once
#include "State.h"
//#include "Button.h"
#include "Gui.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "EditorMode.h"

#include "DefaultEditorMode.h"
#include "EnemyEditorMode.h"

// Forward declarations
class State;
class stateData;
class Gui;
class PauseMenu;
class TileMap;
class Tile;
class EditorMode;
class DefaultEditorMode;
class EditorStateData;
class EnemyEditorMode;

enum EditorModes {DEFAULT_EDITOR_MODE = 0, ENEMY_EDITOR_MODE};

class EditorState :
    public State
{
private:
    EditorStateData editorStateData;

    // Text variables
    Font font;

    PauseMenu* menu;

    // Camera variables
    sf::View view;
    int camSpeed;

    // map buttons
    std::map<std::string, gui::Button*> buttons;

    // Tile
    TileMap* tileMap;
 
    std::vector<EditorMode*> modes;
    unsigned activeMode;
    

    // init
    void initVariables();
    void initEditorStateData();
    void initView();
    //void initBackground();
    void initFonts();
   // void initText();
    void initkeybinds();
    void initPauseMenu();
    void initButtons();
    void initTileMap();
    void initGui();

    void initModes();

public:
    EditorState(StateData* state_data);
    virtual ~EditorState();

    // Functions

    void updateInput(const float& dt);
    void updateEditorInput(const float& dt);
    void updateButtons();
    void updateGui(const float& dt);
    void updatePause();
    void updateModes(const float& dt);
    void update(const float& dt);
    void renderButtons(RenderTarget& target);
    void renderGui(RenderTarget& target);
    void renderModes(RenderTarget& target);
    void render(RenderTarget* target = NULL);
};

