#include "stdafx.h"
#include "GameState.h"

// Initialization

void GameState::initPostRender()
{
	this->renderTexture.create(this->window->getSize().x, this->window->getSize().y);
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(sf::IntRect(0, 0,
		this->window->getSize().x, this->window->getSize().y));
}

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

void GameState::initView()
{
	this->view.setCenter(sf::Vector2f(this->window->getSize().x / 2.f, this->window->getSize().y / 2.f));
	//this->view.setCenter(sf::Vector2f(this->window->getSize().x , this->window->getSize().y));
	//this->view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
	this->view.setSize(sf::Vector2f(this->window->getSize().x + 200, this->window->getSize().y + 200));
	//this->view.setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y));


//	view.setSize(640, 480); // Creates a smaller view space.
//	view.zoom(0.5f); // Also creates a smaller view space.
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
	if (!this->worldBgTex.loadFromFile("Textures/castle_bg.jpg"))  // LOOK IN TEXTURE FOLDER @ B ..\Metro Rogue\textures
		std::cout << "ERROR::GAME::COULD NOT LOAD BG THEME" << "\n";
	this->worldBg.setTexture(this->worldBgTex); // worldBgTex is the object of class Texture created in game.h
	this->worldBg.scale(3.2f, 2.67f); // .setTexture and .scale is the functions of class texture
	//this->worldBg.setPosition(0.f, 225.f);
}

void GameState::initGUI()
{
}

void GameState::initPlayer()
{
	this->player = new Player();
	isOnGround = false;
}

void GameState::initTileMap()
{
	//this->tileMap = new TileMap(this->stateData->gridSize, 50, 50, "Textures/tilesheet1.png");
	this->tileMap = new TileMap(this->stateData->gridSize, 400, 100, "Textures/tile_castle.png");
	this->tileMap->loadFile("text.slmp");
}

// constructor / destructor

GameState::GameState(StateData* state_data)
	: State(state_data)
{
	this->initPostRender();
	this->initKeybinds();
	this->initView();
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

// Update

void GameState::updateView(const float& dt)
{
	this->view.setCenter(std::floor(this->player->getPosition().x), std::floor(this->player->getPosition().y));
	//this->view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
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

void GameState::updateTileMap(const float& dt)
{
	this->tileMap->update();
	this->tileMap->updateCollision(this->player);
}

void GameState::updatePlayer(const float& dt)
{
	this->player->update(dt);
}

void GameState::updateCombat()
{
	for (size_t i = 0; i < this->player->getLasers().size(); i++)
	{
		int laserDistTraveled = this->player->getLasers()[i].getPos().x;
		int playerPosition = this->player->getPosition().x;
		int posDifference = abs(laserDistTraveled - playerPosition);
		cout << posDifference;
		if (posDifference > 600)
		//if (laserDistTraveled > abs(this->player->getPosition().x == 200))
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
			this->window->getSize().y - 0.85*this->player->getGlobalBounds().height
		);
		isOnGround = true;
		cout << "\t\t" << isOnGround;
	}
	else if (this->player->getPosition().y + this->player->getGlobalBounds().height < this->window->getSize().y) // In the air
	{
		isOnGround = false;
		cout << "\t\t" << isOnGround;
		cout << "getcanjump: " << this->player->getCanJump();//basically a trigger disconnect, if this wasnt here the player could fly forever
	}
}

void GameState::update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateKeyTime(dt);
	this->updateInput(dt);

	if (!this->paused) // pause game state
	{
		this->updateView(dt);
		this->updatePlayerInput(dt);
		std::cout << "\r\t\t\t\t\t\t\t Currently in Game State";

		this->updatePlayer(dt);
		this->updateCombat();
		this->updateCollision();
		this->updateTileMap(dt);
	}
	else // update pause menu
	{
		this->menu->update(this->mousePosWindow);
		this->updatePause();
	}
}

void GameState::renderWorld()
{
	this->window->draw(this->worldBg);
}

// Render

void GameState::renderPlayer()
{
	this->player->render(this->renderTexture);
}

void GameState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;
	this->renderTexture.clear();

	this->renderTexture.setView(this->view);
//	this->renderWorld(); // just the bg
	
	
	//target->setView(this->view);
	this->tileMap->render(this->renderTexture); // render tile under player
	this->player->render(this->renderTexture); // render player over tile
	
	if (this->paused) // pause menu render
	{
		this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->menu->render(this->renderTexture);
	}

	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}
