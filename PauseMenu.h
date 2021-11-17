#pragma once
//#include "Button.h"
#include "Gui.h"

class PauseMenu
{
private:
	sf::Font& font;
	sf::Text menuText;

	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, gui::Button*> buttons;


public:
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~PauseMenu();

	// Accessors
	std::map<std::string, gui::Button*> & getButtons();

	const bool isButtonPressed(const std::string key);
	void addbutton(const std::string key, float y, const std::string text);

	// Update
	void update(const sf::Vector2i& mousePosWindow);
	// Render
	void render(sf::RenderTarget& target);

};

