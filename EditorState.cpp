#include "stdafx.h"
#include "EditorState.h"

void EditorState::initVariables()
{
}

void EditorState::initBackground()
{

}

void EditorState::initFonts()
{
	this->font.loadFromFile("Fonts/Dosis-Light.ttf");
}

void EditorState::initKeybinds()
{
	std::ifstream ifs("Config/EditorStateKeys.ini");
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
	this->menu->addbutton("QUIT", 200.f, "QUIT");
}

void EditorState::initButtons()
{
	
}

void EditorState::initGui()
{
	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
	this->selectorRect.setFillColor(sf::Color::Transparent);
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::White);
}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 10, 10);
}

EditorState::EditorState(StateData* state_data)
	:State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initPauseMenu();
	this->initButtons();
	this->initGui();
	this->initTileMap();
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
}

void EditorState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) && this->getKeytime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void EditorState::updateButtons()
{
	//this->gameState_btn->update(this->mousePosView);
	// updates all buttons within the mainmenu state and handles functionality
	for (auto& i : this->buttons)
	{
		i.second->update(this->mousePosView);
	}

}

void EditorState::updateGui()
{
	stringstream ss;
	ss << this->mousePosView.x << "  " << this->mousePosView.y;
	mouseText.setString(ss.str());
	
	this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize, this->mousePosGrid.y * this->stateData->gridSize);
}

void EditorState::updatePause()
{
	if (this->menu->isButtonPressed("QUIT"))
		this->endState();
}

void EditorState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateKeyTime(dt);
	this->updateInput(dt);

	if (!this->paused)
	{ // unpaused
		this->updateButtons();
		this->updateGui();
	}
	else 
	{ // paused
		this->menu->update(this->mousePosView);
		this->updatePause();
	}

	this->updateButtons();
	
	
}

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
	mouseText.setPosition(this->mousePosView.x + 25, this->mousePosView.y - 25);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	target.draw(mouseText);

	target.draw(this->selectorRect);
}

void EditorState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;

	//this->gameState_btn->render(target);
	this->renderButtons(*target);
	
	
	this->renderGui(*target);

	this->tileMap->render(*target);

	if (this->paused) // pause menu render
	{
		this->menu->render(*target);
	}
}