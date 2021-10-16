#include "stdafx.h"
#include "Game.h"

int main()
{
	srand(time(0));

	Game game; // Start the game object

	while (game.getWindow().isOpen()) // modify soon to create a main menu.
	{ // create object -> update it, render it. 
		game.update(); // see game.cpp for all updates
		game.render(); // see game.cpp for all renders
	}

	//EOA
	return 0;
}

/* controls schemes for now:
* Movement: WASD, Space
*/