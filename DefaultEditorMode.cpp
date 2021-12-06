#include "stdafx.h"
#include "DefaultEditorMode.h"

void DefaultEditorMode::initVariables()
{
	this->textureRect = sf::IntRect(0, 0, static_cast<int>(this->stateData->gridSize), static_cast<int>(this->stateData->gridSize));
	this->collision = false;
	// mouse text
	this->type = TileTypes::DEFAULT;
	
	this->layer = 0;
	this->tileAddLock = false;
}

void DefaultEditorMode::initGui()
{
	// text
	this->cursorText.setFont(*this->editorStateData->font);
	this->cursorText.setCharacterSize(12);
	this->cursorText.setFillColor(sf::Color::White);
	this->cursorText.setPosition(this->editorStateData->mousePosView->x + 25.f, this->editorStateData->mousePosView->y - 25.f);

	// Side bar init
	this->sidebar.setSize(sf::Vector2f(60.f, this->stateData->window->getSize().y));
	this->sidebar.setFillColor(sf::Color(50, 50, 50, 100));
	this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));
	this->sidebar.setOutlineThickness(1.f);

	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
	this->selectorRect.setFillColor(sf::Color(255, 255, 255, 150)); // ALMOST TRANSPARANT
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::White);
	this->selectorRect.setTexture(this->tileMap->getTileSheet());
	this->selectorRect.setTextureRect(this->textureRect);

	this->textureSelector = new gui::TextureSelector(20.f, 20.f, 500.f, 500.f, this->stateData->gridSize,
		this->tileMap->getTileSheet(), *this->editorStateData->font, "Click");

	// buttons
}

DefaultEditorMode::DefaultEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data)
	: EditorMode(state_data, tile_map, editor_state_data)
{
	this->initVariables();
	this->initGui();
}

DefaultEditorMode::~DefaultEditorMode()
{
	delete this->textureSelector;
}


// UPDATING FUNCTIONS

void DefaultEditorMode::updateInput(const float& dt)
{
	// adds tile for every left click
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))// && this->getKeytime())
	{	// editor wont be able to add tile within the side bar
		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePosWindow)))
		{
			if (!this->textureSelector->getActive())
			{
				if (this->tileAddLock)
				{
					if (this->tileMap->isTileEmpty(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0))
					{
						this->tileMap->addTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0, this->textureRect, this->collision, this->type);
					}
				}
				else
				{
					this->tileMap->addTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0, this->textureRect, this->collision, this->type);
				}
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
		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePosWindow)))
		{
			if (!this->textureSelector->getActive())
			{
				this->tileMap->removeTile(this->editorStateData->mousePosGrid->x,this->editorStateData->mousePosGrid->y, 0);
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
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("INC_TYPE"))) && this->getKeytime())
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && this->getKeytime())
	{
		this->type++;
	}
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("DEC_TYPE"))) && this->getKeytime())
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && this->getKeytime())
	{
		if (this->type > 0)
			this->type--;
	}

	// Set lock on/ off
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L) && getKeytime())
	{
		if (this->tileAddLock)
			this->tileAddLock = false;
		else
			this->tileAddLock = true;
	}
}

void DefaultEditorMode::updateGui(const float& dt)
{
	this->textureSelector->update(*this->editorStateData->mousePosWindow, dt);

	if (this->textureSelector->getActive())
	{
		this->selectorRect.setTextureRect(this->textureRect);
		this->selectorRect.setPosition(this->editorStateData->mousePosGrid->x * this->stateData->gridSize, this->editorStateData->mousePosGrid->y * this->stateData->gridSize);
	}

	// updates cursor text
	this->cursorText.setPosition(this->editorStateData->mousePosView->x + 25.f, this->editorStateData->mousePosView->y - 25.f);
	stringstream ss;
	ss << this->editorStateData->mousePosView->x << "  " << this->editorStateData->mousePosView->y << "\n"
		<< this->editorStateData->mousePosGrid->x << "  " << this->editorStateData->mousePosGrid->y << "\n"
		<< this->textureRect.left << " " << this->textureRect.top << "\n"
		<< "Collision: " << this->collision << "\n" << "Type: " << this->type << "\n"
		<< "Tiles: " << this->tileMap->getLayerSize(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, this->layer) << "\n"
		<< "Tile Lock: " << this->tileAddLock;

	this->cursorText.setString(ss.str());

}

void DefaultEditorMode::update(const float& dt)
{
	this->updateInput(dt);
	this->updateGui(dt);
}

// RENDERING FUNCTIONS

void DefaultEditorMode::renderGui(RenderTarget& target)
{
	if (this->textureSelector->getActive())
	{
		target.setView(*this->editorStateData->view);
		target.draw(this->selectorRect);
	}

	target.setView(this->stateData->window->getDefaultView());
	this->textureSelector->render(target);
	target.draw(this->sidebar);		// left tab of screen

	target.setView(*this->editorStateData->view);
	target.draw(this->cursorText);  // dynamic text
}

void DefaultEditorMode::render(RenderTarget& target)
{
	this->renderGui(target);
}
