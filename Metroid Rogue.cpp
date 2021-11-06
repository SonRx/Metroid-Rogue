#include "stdafx.h"
#include "Game.h"

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