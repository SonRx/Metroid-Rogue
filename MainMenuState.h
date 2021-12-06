#pragma once
#include "GameState.h"
#include "EditorState.h"
//#include "Button.h"
#include "Gui.h"

class MainMenuState :
    public State
{
private:
    // Variables
    sf::Texture bgTexture;
    sf::RectangleShape background;
    Font font;
    sf::Text mouseText; // debugging where mouse is
    sf::Text name; // name of game on bg

   // Button* gameState_btn;
    std::map<std::string, gui::Button*> buttons;

    // init
    void initVariables();
    void initBackground();
    void initFonts();
    void initkeybinds();
    void initButtons();

public:
    MainMenuState(StateData* state_data);
    virtual ~MainMenuState();

    // Functions

    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(RenderTarget& target);
    void render(RenderTarget* target = NULL);
};

