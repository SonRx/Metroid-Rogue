#include "stdafx.h"
#include "Game.h"

void Game::initWindow()
{
	this->window.create(sf::VideoMode(800, 600), "Metroid vania", sf::Style::Close | sf::Style::Titlebar);
	this->window.setFramerateLimit(60);
	this->window.setVerticalSyncEnabled(false);
}

void Game::initWorld()
{
	if (!this->worldBgTex.loadFromFile("Textures/dung.jpg"))  // LOOK IN TEXTURE FOLDER @ B ..\Metro Rogue\textures
		std::cout << "ERROR::GAME::COULD NOT LOAD BG THEME" << "\n";
	this->worldBg.setTexture(this->worldBgTex); // worldBgTex is the object of class Texture created in game.h
	this->worldBg.scale(.416f, .722f); // .setTexture and .scale is the functions of class texture
}

void Game::initGUI()
{
	this->font.loadFromFile("Fonts/PixellettersFull.ttf");
}

void Game::renderWorld() // called by render()
{
	this->window.draw(this->worldBg);
}

void Game::initPlayer()
{
	this->player = new Player();
}

Game::Game() // constructor
{
	this->initWindow();
	this->initWorld();
	this->initGUI();
	this->initPlayer();
}

Game::~Game() // destructor
{
	delete this->player;
}

void Game::updatePlayer()
{
	this->player->update();
}

void Game::updateCombat()
{
	/////////////////////////////////////////////////////////////// Delete lasers when passes the border of screen -> dont work
	//for (size_t i = 0; i < this->player->getLasers().size(); i++)
	//{
	//	cout << "laser" << endl;
	//	if (this->player->getLasers()[i]->getPos().x > this->window.getSize().x)
	//	{
	//		this->player->getLasers().erase(this->player->getLasers().begin() + i);
	//		break;
	//	}
	//}
}

void Game::updateCollision()
{
	// Collision bottom of screen				// gets dimensions of player		// gets dimensions of window
	if (this->player->getPosition().y + this->player->getGlobalBounds().height > this->window.getSize().y)
	{
		this->player->resetVelocityY();
		this->player->setPosition(
			this->player->getPosition().x,
			this->window.getSize().y - this->player->getGlobalBounds().height
		);
	}
	// collision of any object such as a wall or monster, 
	// if player collides with monster then player takes damage. (future)
}

void Game::updateUI()
{

}

void Game::update()
{
	// Polling window events
	while (this->window.pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed) // exit window upon clicking the red x
			window.close();	
		else if (ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape) // if escape is pressed. window will close
			window.close();

		if (ev.type == sf::Event::KeyReleased && // setting movement butons
			(
				this->ev.key.code == sf::Keyboard::A ||
				this->ev.key.code == sf::Keyboard::D ||
				this->ev.key.code == sf::Keyboard::W ||
				this->ev.key.code == sf::Keyboard::S
				)
			)
		{
			this->player->resetAnimationTimer();
		}
	}
	 // PLACE ALL OBJECT UPDATES HERE ...
	this->updatePlayer();

	this->updateCombat();

	this->updateCollision();

	this->updateUI();
}

void Game::renderPlayer() // called by render()
{
	this->player->render(this->window);
}

void Game::render() // clear then render then display
{
	this->window.clear();

	//Render game
	this->renderWorld();

	this->renderPlayer();

	// this-> renderMonster(); (example)

	this->window.display();
}

// accessor function 
const sf::RenderWindow& Game::getWindow() const
{
	// TODO: insert return statement here
	return this->window;
}
