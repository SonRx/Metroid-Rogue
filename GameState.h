#pragma once
#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"

// Forward Declare
class PauseMenu;
class Player;
class TileMap;
class PlayerGUI;
class sf::View;
class sf::Font;
class sf::RenderTexture;
class Enemy;

class GameState :
    public State
{
private:
    // init player
    Player* player;
    PlayerGUI* playerGUI;

    bool isOnGround;

    // init Enemy
   // Enemy* testEnemy;             // single enemy
    vector<Enemy*> activeEnemies; // multiple enemies
    EnemySystem* enemySystem;

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
    sf::Vector2i viewGridPos;

    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    // init tileMap
    TileMap* tileMap;

    //init
    void initPostRender();
    void initkeybinds();
    void initView();
    void initTextures();
    void initPauseMenu();
    void initWorld();
    void initGUI();
    void initPlayer();
    void initEnemySystem();
    void initPlayerGUI();
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
    void updateTileMap(const float& dt);
    void updatePlayer(const float& dt);
    void updateEnemies(const float& dt);
    void updatePlayerGUI(const float& dt);
    void updateCombat();
    void updateCollision();
    void update(const float& dt);

    void renderWorld();
    void renderPlayer();
    void render(RenderTarget* target = NULL);
};

