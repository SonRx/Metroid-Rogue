#include "stdafx.h"
#include "Game.h"

void Game::initVariables()
{
	this->window = NULL;
	//this->fullscreen = false;
	this->dt = 0.f;

	this->gridSize = 50.f;
}

void Game::initWindow()
{
	/*Create an SFML window using options from Config/window.ini file */
	std::ifstream ifs("Config/window.ini");
	this->videoModes = sf::VideoMode::getFullscreenModes();


	std::string title = "none";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode(); // local variables 
	
	bool fullscreen = false;
	unsigned framerate_limit = 60;
	bool vertical_sync_enabled = false;
	unsigned antialiasing_level = 0;

	if (ifs.is_open()) // Reads a note file and returns data from each line
	{
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> fullscreen;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enabled;
		ifs >> antialiasing_level;
	}
	ifs.close(); // close file after reading

	// place local variables as the parameters
	this->fullscreen = fullscreen;
	this->windowSettings.antialiasingLevel = antialiasing_level;

	if(this->fullscreen)
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, windowSettings);
	else
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);

	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initKeys()
{

	std::ifstream ifs("Config/supportedKeys.ini");
	if (ifs.is_open())
	{
		std::string key = "";
		int keyValue = 0;

		while (ifs >> key >> keyValue)
		{
			this->supportedKeys[key] = keyValue;
		}
	}
	
	ifs.close();

	//DEBUG
	//for (auto i : this->supportedKeys)
	//	cout << i.first << " " << i.second << "\r\n";
}

void Game::initStateData()
{
	this->stateData.window = this->window;
	this->stateData.supportedKeys = &this->supportedKeys;
	this->stateData.states = &this->states;
	this->stateData.gridSize = this->gridSize;
}

void Game::initStates()
{
	this->states.push(new MainMenuState(&this->stateData));
	//this->states.push(new GameState(this->window, &this->supportedKeys));
}

//void Game::initWorld()
//{
//	if (!this->worldBgTex.loadFromFile("Textures/dung.jpg"))  // LOOK IN TEXTURE FOLDER @ B ..\Metro Rogue\textures
//		std::cout << "ERROR::GAME::COULD NOT LOAD BG THEME" << "\n";
//	this->worldBg.setTexture(this->worldBgTex); // worldBgTex is the object of class Texture created in game.h
//	this->worldBg.scale(.416f, .722f); // .setTexture and .scale is the functions of class texture
//}

//void Game::initGUI()
//{
//	this->font.loadFromFile("Fonts/PixellettersFull.ttf");
//}

//void Game::renderWorld() // called by render()
//{
//	this->window->draw(this->worldBg);
//}

//void Game::initPlayer()
//{
//	this->player = new Player();
//}

Game::Game() // constructor
{
	this->initVariables();
	this->initWindow();
	this->initKeys();
	this->initStateData();
	this->initStates();
	///this->initWorld();
	//this->initGUI();
	///this->initPlayer();
}

Game::~Game() // destructor
{
	//delete this->player;
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

void Game::EOA()
{
	cout << "\nending application";
}

void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
	}
}

void Game::updateDt()
{
	this->dt = this->dtClock.getElapsedTime().asSeconds(); // page 30 in book

	//system("cls"); 
	cout <<"\r delta time: "<< dt;
}

//void Game::updatePollEvent()
//{
//	// Polling window events
//	while (this->window->pollEvent(ev))
//	{
//		if (ev.type == sf::Event::Closed) // exit window upon clicking the red x
//			window->close();
//		else if (ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape) // if escape is pressed. window will close
//			window->close();
//
//		if (ev.type == sf::Event::KeyReleased && // setting movement butons
//			(
//				this->ev.key.code == sf::Keyboard::A ||
//				this->ev.key.code == sf::Keyboard::D ||
//				this->ev.key.code == sf::Keyboard::W ||
//				this->ev.key.code == sf::Keyboard::S
//				)
//			)
//		{
//			this->player->resetAnimationTimer();
//		}
//	}
//}

//void Game::updatePlayer()
//{
//	this->player->update();
//}

//void Game::updateCombat()
//{
//	/////////////////////////////////////////////////////////////// Delete lasers when passes the border of screen
//	for (size_t i = 0; i < this->player->getLasers().size(); i++)
//	{
//		if (this->player->getLasers()[i].getPos().x > this->window->getSize().x)
//		{
//			this->player->getLasers().erase(this->player->getLasers().begin() + i);
//			cout << "\r\t\t\t\t\tlaser[" << i << "] deleted";
//			break;
//		}
//	}
//}
//
//void Game::updateCollision()
//{
//	// Collision bottom of screen				// gets dimensions of player		// gets dimensions of window
//	if (this->player->getPosition().y + this->player->getGlobalBounds().height > this->window->getSize().y)
//	{
//		this->player->resetVelocityY();
//		this->player->setPosition(
//			this->player->getPosition().x,
//			this->window->getSize().y - this->player->getGlobalBounds().height
//		);
//	}
//	// collision of any object such as a wall or monster, 
//	// if player collides with monster then player takes damage. (future)
//}

void Game::update()
{
	this->updateSFMLEvents();
	// update states
	if (!this->states.empty()) // check if not empty, then
	{
		this->states.top()->update(this->dt); // update top of stack

		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	else // EOA
	{
		this->EOA();
		this->window->close();
	}

	 // PLACE ALL OBJECT UPDATES HERE ...
	///this->updatePollEvent();
	/*
	this->updatePlayer();

	this->updateCombat();

	this->updateCollision();

	this->updateUI();*/
}


void Game::render() // clear then render then display
{
	this->window->clear(); // first

	// Render items
	if (!this->states.empty()) // check if not empty, then
	{
		this->states.top()->render(this->window); // render top of stack
	}

	//Render game
	///this->renderWorld();

	///this->renderPlayer();

	// this-> renderMonster(); (example)

	this->window->display(); // last
}

// accessor function 
const sf::RenderWindow* Game::getWindow() const
{
	// TODO: insert return statement here
	return this->window;
}

void Game::runApplication()
{
	while (this->window->isOpen()) // modify soon to create a main menu.
	{ // create object -> update it, render it. 
		updateDt();
		update(); // see game.cpp for all updates
		render(); // see game.cpp for all renders
	}
}
