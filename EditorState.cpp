#include "stdafx.h"
#include "EditorState.h"

// INITIALIZATION

void EditorState::initVariables()
{
	this->camSpeed = 750;
}

void EditorState::initEditorStateData()
{
	this->editorStateData.view = &this->view;
	this->editorStateData.font = &this->font;
	this->editorStateData.keytime = &this->keytime;
	this->editorStateData.keytimeMax = &this->keytimeMax;
	this->editorStateData.keybinds = &this->keybinds;
	this->editorStateData.mousePosGrid = &this->mousePosGrid;
	this->editorStateData.mousePosScreen = &this->mousePosScreen;
	this->editorStateData.mousePosView = &this->mousePosView;
	this->editorStateData.mousePosWindow = &this->mousePosWindow;

}

void EditorState::initView()
{
	this->view.setCenter(static_cast<float>(this->window->getSize().x) / 2.f, static_cast<float>(this->window->getSize().y) / 2.f);
	this->view.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x),static_cast<float>(this->window->getSize().y)));
}

//void EditorState::initBackground()
//{
//
//}

void EditorState::initFonts()
{
	this->font.loadFromFile("Fonts/Dosis-Light.ttf");
}

//void EditorState::initText()
//{
//	this->cursorText.setFont(this->font);
//	this->cursorText.setCharacterSize(12);
//	this->cursorText.setFillColor(sf::Color::White);
//	this->cursorText.setPosition(this->mousePosView.x + 25.f, this->mousePosView.y - 25.f);
//}

void EditorState::initkeybinds()
{
	std::ifstream ifs("Config/EditorStateKeys.ini");
	ifs.clear();
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
	//this->tileMap = new TileMap(this->stateData->gridSize, 160, 40, "Textures/tile_castle.png");  // text2 is 40 40
	this->tileMap = new TileMap(this->stateData->gridSize, 160, 160, "Textures/Assets.png");
	//this->tileMap = new TileMap(this->stateData->gridSize, 400, 100, "Textures/tile_castle.png");
}

void EditorState::initGui()
{
	//// Side bar init
	//this->sidebar.setSize(sf::Vector2f(60.f, this->window->getSize().y));
	//this->sidebar.setFillColor(sf::Color(50, 50, 50, 100));
	//this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));
	//this->sidebar.setOutlineThickness(1.f);

	//this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
	//this->selectorRect.setFillColor(sf::Color(255,255,255,150)); // ALMOST TRANSPARANT
	//this->selectorRect.setOutlineThickness(1.f);
	//this->selectorRect.setOutlineColor(sf::Color::White);
	//this->selectorRect.setTexture(this->tileMap->getTileSheet());
	//this->selectorRect.setTextureRect(this->textureRect);

	//this->textureSelector = new gui::TextureSelector(20.f, 20.f, 500.f, 500.f, this->stateData->gridSize,
	//	this->tileMap->getTileSheet(), this->font, "Click");
}

void EditorState::initModes()
{
	this->modes.push_back(new DefaultEditorMode(this->stateData, this->tileMap, &this->editorStateData));
	this->modes.push_back(new EnemyEditorMode(this->stateData, this->tileMap, &this->editorStateData));

	this->activeMode = EditorModes::DEFAULT_EDITOR_MODE;
}

// CONSTRUCTOR / DESTRUCTOR

EditorState::EditorState(StateData* state_data)
	:State(state_data)
{
	this->initVariables();
	this->initEditorStateData();
	this->initView();
	//this->initBackground();
	this->initFonts();
	//this->initText();
	this->initkeybinds();
	this->initPauseMenu();
	this->initButtons();
	this->initTileMap();
	this->initGui();
	this->initModes();
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
	//delete this->textureSelector;

	for (size_t i = 0; i < this->modes.size(); i++)
	{
		delete this->modes[i];
	}
}

// UPDATE

void EditorState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) && this->getKeytime())
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Close"))) && this->getKeytime())
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
		this->view.move(0.f,-this->camSpeed *dt);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->view.move(0.f,this->camSpeed * dt);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->view.move(-this->camSpeed * dt, 0.f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->view.move(this->camSpeed * dt, 0.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp))
	{
		if (this->activeMode < this->modes.size() - 1)
			this->activeMode++;
		else
			cout << "CANNOT CHANGE MODE" << endl;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown))
	{
		if (this->activeMode > 0)
			this->activeMode--;
		else
			cout << "CANNOT CHANGE MODE" << endl;
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
	
}

void EditorState::updatePause()
{
	if (this->menu->isButtonPressed("QUIT"))
		this->endState();

	if (this->menu->isButtonPressed("SAVE")) {
		this->tileMap->saveFile("text4.slmp"); // Save to this file -> located in explorer
		//this->tileMap->saveFile("text4.slmp");
	}

	if (this->menu->isButtonPressed("LOAD")) {
		this->tileMap->loadFile("text4.slmp"); // loads this file into the game
		//this->tileMap->loadFile("text4.slmp");
	}
}

void EditorState::updateModes(const float& dt)
{
	this->modes[this->activeMode]->update(dt);
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
		this->updateModes(dt);
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
	
}

void EditorState::renderModes(RenderTarget& target)
{
	this->modes[this->activeMode]->render(target);
}

void EditorState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;

	// Render tile map with this view
	target->setView(this->view); // Game camera
	this->tileMap->render(*target, this->mousePosGrid, true);
	this->tileMap->queueRender(*target); // Tiles that render over the player

	target->setView(this->window->getDefaultView());
	this->renderButtons(*target);
	this->renderGui(*target);
	this->renderModes(*target);

	if (this->paused) // pause menu render
	{
		target->setView(this->window->getDefaultView());
		this->menu->render(*target);
	}
}