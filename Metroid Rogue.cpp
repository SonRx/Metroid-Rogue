#include "stdafx.h"
#include "Game.h"
#include "Level.h"

//#define GAME_DEBUG 
//used to specify if you want to boot straight into the game or not
//comment out if you want to boot into the menu

#ifdef GAME_DEBUG
void Game::initStates()//boots into game
{
	this->states.push(new GameState(&this->stateData));
}
#else
void Game::initStates()//boots into menu
{
	this->states.push(new MainMenuState(&this->stateData));
}
#endif

int main()
{
	srand(time(0));

	Game game; // Start the game object

	game.runApplication();

	return 0; //EOA
}

/* controls schemes for now:
* Movement:				WASD, Space
* Shoot:				Left Click
*/