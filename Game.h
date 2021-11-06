#pragma once
#include "MainMenuState.h"

class Game
{
private:
	StateData stateData;
	sf::RenderWindow *window;
	sf::Event sfEvent; // sfml events
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	bool fullscreen;

	Clock dtClock; // page 29 in book
	float dt; // delta time -> keeps track of the time of one update/render -> verification method

	std::stack<State*> states; // State is an abstract class, cant create objects of states, only pointers and refs

	
	std::map<string, int> supportedKeys;

	float gridSize;

	// Resources
	//std::map<std::string, sf::Texture*> textures;
	void initVariables();
	void initWindow();
	void initKeys();
	void initStateData();
	void initStates();
	///void initWorld();
	///void initGUI();
	///void initPlayer();
	
	// World
	///sf::Texture worldBgTex;
	///sf::Sprite worldBg;

public:

	Game();
	virtual ~Game();

//////////////////////////// Functions
	void EOA(); // End of Application
	// updating Functions
	void updateSFMLEvents();
	void updateDt();
	///void updatePollEvent(); // updates SFML events
	///void updatePlayer(); // points to player->update which then updates everything of player
	///void updateCombat(); // currently deletes bullets that passes the screen
	///void updateCollision(); // currently updates player touching the ground

	///void updateUI();

	void update();


	// rendering Functions
	///void renderWorld();
	///void renderPlayer();
	void render();
	const sf::RenderWindow* getWindow() const; // access it to get its state

	void runApplication(); // RUNS GAME -> INITIALIZE, UPDATE, RENDER -> SAME PATTERN FOR ALL CLASSES
};
