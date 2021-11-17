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

public:

	Game();
	virtual ~Game();

//////////////////////////// Functions
	void EOA(); // End of Application

	// updating Functions
	void updateSFMLEvents();
	void updateDt();
	void update();


	// rendering Functions
	///void renderWorld();
	///void renderPlayer();
	void render();
	const sf::RenderWindow* getWindow() const; // access it to get its state

	void runApplication(); // RUNS GAME -> INITIALIZE, UPDATE, RENDER -> SAME PATTERN FOR ALL CLASSES
};
