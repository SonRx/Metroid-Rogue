#include "stdafx.h"
#include "GameState.h"

void GameState::initKeybinds()
{
	std::ifstream ifs("Config/GameStateKeys.ini");
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

void GameState::initTextures()
{
	this->font.loadFromFile("Fonts/Dosis-Light.ttf");
}

void GameState::initPauseMenu()
{
	this->menu = new PauseMenu(*this->window, this->font);
	this->menu->addbutton("QUIT", 200.f, "QUIT");
}

void GameState::initWorld()
{
	if (!this->worldBgTex.loadFromFile("Textures/dung.jpg"))  // LOOK IN TEXTURE FOLDER @ B ..\Metro Rogue\textures
		std::cout << "ERROR::GAME::COULD NOT LOAD BG THEME" << "\n";
	this->worldBg.setTexture(this->worldBgTex); // worldBgTex is the object of class Texture created in game.h
	this->worldBg.scale(1.f, 1.f); // .setTexture and .scale is the functions of class texture
	this->worldBg.setPosition(0.f, 225.f);
}

void GameState::initGUI()
{
}

void GameState::initPlayer()
{
	this->player = new Player();
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 50, 50);
}

// constructor / destructor
GameState::GameState(StateData* state_data)
	: State(state_data)
{
	this->initKeybinds();
	this->initTextures();
	this->initPauseMenu();
	this->initWorld();
	this->initGUI();
	this->initPlayer();
	this->initTileMap();
}

GameState::~GameState()
{
	delete this->menu;
	delete this->player;
	delete this->tileMap;
}

void GameState::updateView(const float& dt)
{
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) && this->getKeytime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void GameState::updatePlayerInput(const float& dt)
{
	//Update player input
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("Left"))))
		this->player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("Right"))))
		this->player->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("Up"))))
		this->player->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("Down"))))
		this->player->move(0.f, 1.f);*/
	
	//if (sf::Event::KeyReleased && // setting movement butons
	//	(
	//		 sf::Keyboard::A ||
	//		 sf::Keyboard::D ||
	//		 sf::Keyboard::W ||
	//		 sf::Keyboard::S
	//		)
	//	)
	//{
	//	this->player->resetAnimationTimer();
	//}

	//// Polling window events
	//while (this->window->pollEvent(ev))
	//{
	//	if (ev.type == sf::Event::Closed) // exit window upon clicking the red x
	//		window->close();
	//	else if (ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape) // if escape is pressed. window will close
	//		window->close();

	//	if (ev.type == sf::Event::KeyReleased && // setting movement butons
	//		(
	//			this->ev.key.code == sf::Keyboard::A ||
	//			this->ev.key.code == sf::Keyboard::D ||
	//			this->ev.key.code == sf::Keyboard::W ||
	//			this->ev.key.code == sf::Keyboard::S
	//			)
	//		)
	//	{
	//		this->player->resetAnimationTimer();
	//	}
	//}
}

void GameState::updatePause()
{
	if (this->menu->isButtonPressed("QUIT"))
		this->endState();
}

void GameState::updatePlayer(const float& dt)
{
	this->player->update(dt);
}

void GameState::updateCombat()
{
	for (size_t i = 0; i < this->player->getLasers().size(); i++)
	{
		if (this->player->getLasers()[i].getPos().x > this->window->getSize().x)
		{
			this->player->getLasers().erase(this->player->getLasers().begin() + i);
			cout << "\r\t\t\t\t\tlaser[" << i << "] deleted";
			break;
		}
	}
}

void GameState::updateCollision()
{
	// Collision bottom of screen				// gets dimensions of player		// gets dimensions of window
	if (this->player->getPosition().y + this->player->getGlobalBounds().height > this->window->getSize().y)
	{
		this->player->resetVelocityY();
		this->player->setPosition(
			this->player->getPosition().x,
			this->window->getSize().y - this->player->getGlobalBounds().height
		);
	}
}

void GameState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateKeyTime(dt);
	this->updateInput(dt);

	if (!this->paused) // pause game state
	{
		this->updatePlayerInput(dt);
		std::cout << "\r\t\t\t\t\t\t\t Currently in Game State";

		this->updatePlayer(dt);
		this->updateCombat();
		this->updateCollision();
	}
	else // update pause menu
	{
		this->menu->update(this->mousePosView);
		this->updatePause();
	}
}

void GameState::renderWorld()
{
	this->window->draw(this->worldBg);
}

void GameState::renderPlayer()
{
	this->player->render(this->window);
}

void GameState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;
	this->renderWorld();

	//this->tileMap->render(*target);

	this->player->render(target);

	if (this->paused) // pause menu render
	{
		this->menu->render(*target);
	}
}
