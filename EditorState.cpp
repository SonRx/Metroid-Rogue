#include "stdafx.h"
#include "EditorState.h"

// INITIALIZATION

void EditorState::initVariables()
{
	this->textureRect = sf::IntRect(0, 0, static_cast<int>(this->stateData->gridSize), static_cast<int>(this->stateData->gridSize));
	this->collision = false;
	this->type = TileTypes::DEFAULT;
	this->camSpeed = 750.f;
}

void EditorState::initView()
{
	this->view.setCenter(this->window->getSize().x / 2.f, this->window->getSize().y / 2.f);
	this->view.setSize(sf::Vector2f(this->window->getSize().x,this->window->getSize().y));
}

void EditorState::initBackground()
{

}

void EditorState::initFonts()
{
	this->font.loadFromFile("Fonts/Dosis-Light.ttf");
}

void EditorState::initText()
{
	this->cursorText.setFont(this->font);
	this->cursorText.setCharacterSize(12);
	this->cursorText.setFillColor(sf::Color::White);
	this->cursorText.setPosition(this->mousePosView.x + 25.f, this->mousePosView.y - 25.f);
}

void EditorState::initKeybinds()
{
	std::ifstream ifs("Config/EditorStateKeys.ini");
	ifs.clear();
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

void EditorState::initPauseMenu()
{
	this->menu = new PauseMenu(*this->window, this->font);
	this->menu->addbutton("QUIT", 400.f, "QUIT");
	this->menu->addbutton("SAVE", 300.f, "SAVE");
	this->menu->addbutton("LOAD", 200.f, "LOAD");
}

void EditorState::initButtons()
{
}

void EditorState::initTileMap()
{
	//this->tileMap = new TileMap(this->stateData->gridSize, 10, 10, "Textures/tilesheet1.png");
	this->tileMap = new TileMap(this->stateData->gridSize, 400, 100, "Textures/tile_castle.png");
}

void EditorState::initGui()
{
	// Side bar init
	this->sidebar.setSize(sf::Vector2f(60.f, this->window->getSize().y));
	this->sidebar.setFillColor(sf::Color(50, 50, 50, 100));
	this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));
	this->sidebar.setOutlineThickness(1.f);

	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
	this->selectorRect.setFillColor(sf::Color(255,255,255,150)); // ALMOST TRANSPARANT
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::White);
	this->selectorRect.setTexture(this->tileMap->getTileSheet());
	this->selectorRect.setTextureRect(this->textureRect);

	this->textureSelector = new gui::TextureSelector(20.f, 20.f, 500.f, 500.f, this->stateData->gridSize,
		this->tileMap->getTileSheet(), this->font, "Click");
}

// CONSTRUCTOR / DESTRUCTOR

EditorState::EditorState(StateData* state_data)
	:State(state_data)
{
	this->initVariables();
	this->initView();
	this->initBackground();
	this->initFonts();
	this->initText();
	this->initKeybinds();
	this->initPauseMenu();
	this->initButtons();
	this->initTileMap();
	this->initGui();
}

EditorState::~EditorState()
{
	//delete this->gameState_btn;
	auto i = this->buttons.begin();
	for (i = this->buttons.begin(); i != this->buttons.end(); ++i)
	{
		delete i->second;
	}

	delete this->menu;
	delete this->tileMap;
	delete this->textureSelector;

}

// UPDATE

void EditorState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) && this->getKeytime())
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("Close"))) && this->getKeytime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void EditorState::updateEditorInput(const float& dt)
{
	// Move view
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->view.move(0.f, this->camSpeed *dt);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->view.move(0.f, this->camSpeed * dt);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->view.move(this->camSpeed * dt, 0.f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->view.move(this->camSpeed * dt, 0.f);

	// adds tile for every left click
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime())
	{	// editor wont be able to add tile within the side bar
		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
		{
			if (!this->textureSelector->getActive())
			{
				this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect, this->collision, this->type);
			}
			else
			{
				this->textureRect = this->textureSelector->getTextureRect();
			}
		}
	}
		// removes tile for every right click
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeytime())
	{
		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
		{
			if (!this->textureSelector->getActive())
			{
				this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
			}
		}
	}

	// Toggle collision
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C) && this->getKeytime())
	{
		if (this->collision)
			this->collision = false;
		else
			this->collision = true;
	}
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("INC_TYPE"))) && this->getKeytime())
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && this->getKeytime())
	{	
		this->type++;
	}
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("DEC_TYPE"))) && this->getKeytime())
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && this->getKeytime())
	{
		if (this->type > 0)
			this->type--;
	}
}

void EditorState::updateButtons()
{
	//this->gameState_btn->update(this->mousePosView);
	// updates all buttons within the mainmenu state and handles functionality
	for (auto& i : this->buttons)
	{
		i.second->update(this->mousePosWindow);
	}

}

void EditorState::updateGui(const float& dt)
{
	this->textureSelector->update(this->mousePosWindow,dt);

	if (this->textureSelector->getActive())
	{
		this->selectorRect.setTextureRect(this->textureRect);
		this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize, this->mousePosGrid.y * this->stateData->gridSize);
	}

	// updates cursor text
	this->cursorText.setPosition(this->mousePosView.x + 25.f, this->mousePosView.y - 25.f);
	stringstream ss;
	ss << this->mousePosView.x << "  " << this->mousePosView.y << "\n"
		<< this->mousePosGrid.x << "  " << this->mousePosGrid.y << "\n"
		<< this->textureRect.left << " " << this->textureRect.top << "\n"
		<< "Collision: " << this->collision << "\n" << "Type: " << this->type;

	this->cursorText.setString(ss.str());

}

void EditorState::updatePause()
{
	if (this->menu->isButtonPressed("QUIT"))
		this->endState();

	if (this->menu->isButtonPressed("SAVE"))
		this->tileMap->saveFile("text.slmp"); // Save to this file -> located in explorer

	if (this->menu->isButtonPressed("LOAD"))
		this->tileMap->loadFile("text.slmp"); // loads this file into the game
}

void EditorState::update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateKeyTime(dt);
	this->updateInput(dt);

	if (!this->paused)
	{ // unpaused
		this->updateButtons();
		this->updateGui(dt);
		this->updateEditorInput(dt);
	}
	else 
	{ // paused
		this->menu->update(this->mousePosWindow);
		this->updatePause();
	}

	this->updateButtons();
	
	
}

// RENDER

void EditorState::renderButtons(RenderTarget& target)
{
	//this->gameState_btn->render(target);
	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}
}

void EditorState::renderGui(RenderTarget& target)
{
	if (this->textureSelector->getActive())
	{
		target.setView(this->view);
		target.draw(this->selectorRect);
	}

	target.setView(this->window->getDefaultView());
	this->textureSelector->render(target);
	target.draw(this->sidebar);		// left tab of screen

	target.setView(this->view);
	target.draw(this->cursorText);  // dynamic text
}

void EditorState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;

	// Render tile map with this view
	target->setView(this->view); // Game camera
	this->tileMap->render(*target);

	target->setView(this->window->getDefaultView());
	this->renderButtons(*target);
	this->renderGui(*target);

	if (this->paused) // pause menu render
	{
		target->setView(this->window->getDefaultView());
		this->menu->render(*target);
	}
}