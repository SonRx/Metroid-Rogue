#pragma once
#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
//enum PLAYER_ANIMATION_STATES { IDLE = 0, MOVING_LEFT, MOVING_RIGHT, JUMPING, FALLING };

class GameState :
    public State
{
private:

    Player* player;
   // sf::Event ev; // sfml events
    Font font;
    PauseMenu* menu;

    //animation 
    short animState;

    // World
    sf::Texture worldBgTex;
    sf::Sprite worldBg;

    TileMap* tileMap;

    //init
    void initKeybinds();
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

