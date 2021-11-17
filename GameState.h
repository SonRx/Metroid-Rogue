#pragma once
#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "tinyxml2.h"
#include "Level.h"

// Forward Declare
class PauseMenu;
class Player;
class TileMap;
class sf::View;
class sf::Font;
class sf::RenderTexture;

class GameState :
    public State
{
private:
    // init player
    Player* player;

    // init font
    Font font;

    // init pause menu
    PauseMenu* menu;

    // animation for player
    short animState;

    // World
    sf::Texture worldBgTex;
    sf::Sprite worldBg;

    // init camera view
    sf::View view;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    // init tileMap
    TileMap* tileMap;

    //init
    void initKeybinds();
    void initView();
    void initTextures();
    void initPauseMenu();
    void initWorld();
    void initGUI();
    void initPlayer();
    void initTileMap();

public:
    GameState(StateData* state_data);
    virtual ~GameState();

    // Functions

    // update/render
    void updateView(const float& dt);
    void updateInput(const float& dt);
    void updatePlayerInput(const float& dt);
    void updatePause();
    void updatePlayer(const float& dt);
    void updateCombat();
    void updateCollision();
    void update(const float& dt);

    void renderWorld();
    void renderPlayer();
    void render(RenderTarget* target = NULL);
};

