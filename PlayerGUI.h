#pragma once
#include "Player.h"
#include "Gui.h"
using namespace gui;
class Player; // forward declaration
class sf::RectangleShape;

class PlayerGUI
{
private:
	Player* player; // referencing to the only player 

	sf::Font font;

	// HP Bar
	gui::ProgressBar* hpBar;
	//string hpBarString;
	//sf::Text hpBarText;
	//float playerHpBarMaxWidth;
	//RectangleShape playerHpBar;
	//RectangleShape playerHpBarBack;

	void initFont();
	void initHPbar();

public:
	PlayerGUI(Player* player);
	virtual ~PlayerGUI();

	// update
	void updateHPbar();
	void update(const float& dt);

	void renderHPbar(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

