#include "stdafx.h"
#include "MainMenuState.h"

// Initilizations

void MainMenuState::initVariables()
{
}

void MainMenuState::initBackground()
{
	// background
	this->background.setSize(sf::Vector2f(
		static_cast<float>(this->window->getSize().x), 
		static_cast<float>(this->window->getSize().y))
	);
	if (!this->bgTexture.loadFromFile("Textures/mainmenu.jpg"))
		throw "ERROR::MAINMENUSTATE::FAILED TO LOAD MAINMENU BACKGROUND TEXTURE";
	

	this->background.setTexture(&this->bgTexture);

}

void MainMenuState::initFonts()
{
	this->font.loadFromFile("Fonts/Dosis-Light.ttf");

	// Debugging purposes
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);

	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	// NAME
	name.setPosition(100,10);
	name.setFont(this->font);
	name.setCharacterSize(50);
	name.setFillColor(Color::Green);
	name.setString("Metroid Rogue\nSoftware Engineering Video Game Project\nDeveloped by team A");
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("Config/MainmenuStateKeys.ini");
	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keyBinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new gui::Button(100.f, 300.f, 200.f, 50.f, &this->font, "Start Game", 30,
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EDITOR_STATE"] = new gui::Button(100.f, 400.f, 200.f, 50.f, &this->font, "Map Maker", 30,
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 0),
		Color(70, 70, 70, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0));

	this->buttons["EXIT_STATE"] = new gui::Button(100.f, 500.f, 200.f, 50.f, &this->font, "Quit Game", 30,
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		Color(70, 70, 70, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0));
}

// CONSTRUCTOR / DESTRUCTOR

MainMenuState::MainMenuState(StateData* state_data)
	:State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}

MainMenuState::~MainMenuState()
{
	//delete this->gameState_btn;
	auto i = this->buttons.begin();
	for (i = this->buttons.begin(); i != this->buttons.end(); ++i)
	{
		delete i->second;
	}
}

// UPDATE / RENDER

void MainMenuState::updateInput(const float& dt)
{
	//this->checkQuit();
}

void MainMenuState::updateButtons()
{
	// updates all buttons within the mainmenu state and handles functionality
	for (auto& i : this->buttons)
	{
		i.second->update(this->mousePosWindow);
	}

	// New game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->stateData));
	}

	// MAP EDITOR
	if (this->buttons["EDITOR_STATE"]->isPressed())
	{
		this->states->push(new EditorState(this->stateData));
	}

	// Quit the game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateButtons();
}

void MainMenuState::renderButtons(RenderTarget& target)
{
	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}
}

void MainMenuState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->background);

	this->renderButtons(*target);

	target->draw(mouseText);
	target->draw(name);
}
