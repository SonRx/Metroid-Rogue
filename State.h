#pragma once
#include "Player.h"

class Player;
class State;

class StateData
{
public:
	StateData() {};

	// variables
	float gridSize;
	RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::stack<State*>* states;
};

class State
{
private:
	
protected:
	StateData* stateData;
	std::stack<State*>* states; // stack of stake pointers
	RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keyBinds;
	bool quit, paused;
	float keytime, keytimeMax;
	float gridSize;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2i mousePosGrid;

	// resources
	std::map<std::string, sf::Texture> textures;

	// Init
	virtual void initKeybinds() = 0;

public:
	// constructor / destructor
	State(StateData* state_data);
	virtual ~State();

	// Accessors
	const bool& getQuit() const { return this->quit; }
	const bool getKeytime();

	// Modifiers
	void endState();
	void pauseState();
	void unpauseState();

	// Update / Render
	virtual void updateMousePositions(sf::View* view = NULL);
	virtual void updateKeyTime(const float& dt);
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0; // pure virtual function
						//if theres no parameter below, window will still run
	virtual void render(RenderTarget* target = NULL) = 0; // predefined to mainmenu 0 for future 
};

