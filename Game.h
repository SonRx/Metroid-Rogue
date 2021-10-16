#pragma once
#include "Player.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Event ev;

	Font font;


	Player *player; // raw pointer

	// Resources
	//std::map<std::string, sf::Texture*> textures;

	void initWindow();
	void initWorld();
	void initGUI();

	//void initGUI();
	void initPlayer();
	
	// World
	sf::Texture worldBgTex;
	sf::Sprite worldBg;

public:

	Game();
	virtual ~Game();

	//////////////////////////////////////////// Functions
	// updating Functions
	void updatePlayer();
	void updateCombat();
	void updateCollision();

	void updateUI();

	void update();


	// rendering Functions
	void renderWorld();
	void renderPlayer();
	void render();
	const sf::RenderWindow& getWindow() const; // access it to get its state
};
