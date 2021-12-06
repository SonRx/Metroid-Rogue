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

void GameState::initkeybinds()
{
	std::ifstream ifs("Config/GameStateKeys.ini");
	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
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

	if (!this->textures["PLAYER_SHEET"].loadFromFile("Textures/player_sheet.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}

	if (!this->textures["RAT1_SHEET"].loadFromFile("Textures/rat1_60x64.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_RAT1_TEXTURE";
	}
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

void GameState::initEnemySystem()
{
	this->enemySystem = new EnemySystem(this->activeEnemies, this->textures);
}

void GameState::initPlayerGUI()
{
	this->playerGUI = new PlayerGUI(this->player);
}

void GameState::initTileMap()
{
	//this->tileMap = new TileMap(this->stateData->gridSize, 160, 40, "Textures/tile_castle.png");
	//this->tileMap->loadFile("text3.slmp");
	//this->tileMap = new TileMap(this->stateData->gridSize, 400, 100, "Textures/tile_castle.png");
	//this->tileMap->loadFile("text.slmp");

	this->tileMap = new TileMap("text3.slmp");
}

// constructor / destructor

GameState::GameState(StateData* state_data)
	: State(state_data)
{
	this->initPostRender();
	this->initkeybinds();
	this->initView();
	this->initTextures();
	this->initPauseMenu();
	this->initWorld();
	this->initGUI();
	this->initPlayer();
	this->initEnemySystem();
	this->initPlayerGUI();
	this->initTileMap();
						//960,540
	//this->testEnemy = new Enemy(400.f, 1000.f, this->textures["PLAYER_SHEET"]);
	//this->activeEnemies.push_back(new Rat(200.f, 100.f, this->textures["RAT1_SHEET"]));
	//this->activeEnemies.push_back(new Rat(500.f, 200.f, this->textures["RAT1_SHEET"]));
	//this->activeEnemies.push_back(new Rat(600.f, 300.f, this->textures["RAT1_SHEET"]));
	//this->activeEnemies.push_back(new Rat(400.f, 500.f, this->textures["RAT1_SHEET"]));
	//this->activeEnemies.push_back(new Rat(200.f, 800.f, this->textures["RAT1_SHEET"]));

}

GameState::~GameState()
{
	delete this->menu;
	delete this->player;
	delete this->playerGUI;
	delete this->tileMap;
	delete this->enemySystem;
	//delete this->testEnemy;

	for (size_t i = 0; i < this->activeEnemies.size(); i++)
	{
		delete this->activeEnemies[i];
	}
}

// Update

void GameState::updateView(const float& dt)
{
	this->view.setCenter(
		std::floor(this->player->getPosition().x + (static_cast<float>(this->mousePosWindow.x) - static_cast<float>(this->window->getSize().x / 2)) / 8.f),
		std::floor(this->player->getPosition().y + (static_cast<float>(this->mousePosWindow.y) - static_cast<float>(this->window->getSize().y / 2)) / 8.f));
	//this->view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

	if (this->tileMap->getMaxSizeWorld().x >= this->view.getSize().x)
	{
		if (this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f)
		{
			this->view.setCenter(0.f + this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
		else if (this->view.getCenter().x + this->view.getSize().x / 2.f >= this->tileMap->getMaxSizeWorld().x)
		{
			this->view.setCenter(this->tileMap->getMaxSizeWorld().x - this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
	}

	//if (this->tileMap->getMaxSizeWorld().y >= this->view.getSize().y)
	//{
	//	if (this->view.getCenter().y - this->view.getSize().y / 2.f < 0.f)
	//	{
	//		this->view.setCenter(this->view.getCenter().x, 0.f + this->view.getSize().y / 2.f);
	//	}
	//	else if (this->view.getCenter().y + this->view.getSize().y / 2.f > this->tileMap->getMaxSizeWorld().y)
	//	{
	//		this->view.setCenter(this->view.getCenter().x, this->tileMap->getMaxSizeWorld().y - this->view.getSize().y / 2.f);
	//	}
	//}
	this->viewGridPos.x = static_cast<int>(this->view.getCenter().x) / static_cast<int>(this->stateData->gridSize);
	this->viewGridPos.y = static_cast<int>(this->view.getCenter().y) / static_cast<int>(this->stateData->gridSize);
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
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Left"))))
		this->player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Right"))))
		this->player->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Up"))))
		this->player->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Down"))))
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

void GameState::updateTileMap(const float& dt) // this replaces update collision in line ~205
{
	this->tileMap->updateWorldBoundsCollision(this->player,dt);
	this->tileMap->updateTileCollision(this->player, dt);
	this->tileMap->updateTiles(this->player, dt, *this->enemySystem);
	//this->tileMap->update(this->player, dt);
	//this->tileMap->updateCollision(this->testEnemy, dt);
	//for (auto* i : this->activeEnemies)
	//{
	//	this->tileMap->updateWorldBoundsCollision(i, dt);
	//	this->tileMap->updateTileCollision(i, dt);
	//	//this->tileMap->updateTiles(i, dt);
	//}
}

void GameState::updatePlayer(const float& dt)
{
	this->player->update(dt, this->mousePosView);
	//DEBUG
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L) && getKeytime())
	{
		this->player->loseHP(1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O) && getKeytime())
	{
		this->player->gainHP(1);
	}
}

void GameState::updateEnemies(const float& dt)
{
	//this->activeEnemies.push_back(new Rat(500.f, 200.f, this->textures["RAT1_SHEET"]));
}

void GameState::updatePlayerGUI(const float& dt)
{
	this->playerGUI->update(dt);
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
			this->window->getSize().y - 0.85f*this->player->getGlobalBounds().height
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
		std::cout << "\r\t\t\t\t\t\t\t Currently in Game State";
		this->updateView(dt);

		this->updateTileMap(dt); // tile collision
		this->updatePlayerInput(dt);
		this->updatePlayer(dt);
		this->updateCombat();
		//this->updateCollision(); // updateTileMap(dt) replaced this
		this->playerGUI->update(dt);

	/*	for (auto* i : this->activeEnemies)
		{
			i->update(dt, this->mousePosView);
		}*/

		//this->testEnemy->update(dt,this->mousePosView);
		//this->testEnemy->move(1.f, 0.f, dt);
		
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
	this->player->render(this->renderTexture,false);
}

void GameState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;
	this->renderTexture.clear();

	this->renderTexture.setView(this->view);
	
	
	//target->setView(this->view);
	//this->tileMap->render(this->renderTexture, this->player->getGridPosition(static_cast<int>(this->stateData->gridSize)),false); // render tile under player

	

	this->tileMap->render(this->renderTexture, this->viewGridPos, false); // render tile under player

	//for (auto* i : this->activeEnemies)
	//{
	//	i->render(this->renderTexture, false);
	//}

	this->player->render(this->renderTexture, false); // render player over tile

	//this->testEnemy->render(this->renderTexture, false);

	this->tileMap->queueRender(this->renderTexture);
	

	// Render player GUI
	this->renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGUI->render(this->renderTexture);
	
	if (this->paused) // pause menu render
	{
		//this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->menu->render(this->renderTexture);
	}

	this->renderTexture.display();

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
	//this->renderWorld(); // just the bg
	
}
