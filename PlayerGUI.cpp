#include "stdafx.h"
#include "PlayerGUI.h"

void PlayerGUI::initFont()
{
	this->font.loadFromFile("Fonts/Dosis-Light.ttf");
}

void PlayerGUI::initHPbar()
{
	float width = 300.f;
	float height = 25.f;
	float x = 20.f;
	float y = 20.f;

	this->hpBar = new gui::ProgressBar(x, y, width, height,this->player->getSkills()->hpMax, sf::Color::Green, 18, &this->font);
//	this->playerHpBarMaxWidth = width;
//
////	Init player GUI
//	this->playerHpBar.setSize(sf::Vector2f(width, height));
//	this->playerHpBar.setFillColor(sf::Color::Green);
//	this->playerHpBar.setPosition(Vector2f(x, y));
//
//	this->playerHpBarBack = this->playerHpBar;
//	this->playerHpBarBack.setFillColor(sf::Color::Red);
//
//	// init texts
//	hpBarText.setFont(this->font);
//	hpBarText.setString("HP: ");
//	hpBarText.setCharacterSize(18);
//	hpBarText.setFillColor(sf::Color::Red);
//	hpBarText.setStyle(sf::Text::Bold);
//	hpBarText.setPosition(Vector2f(22.f, y));
}

PlayerGUI::PlayerGUI(Player* player)
{
	this->player = player;
	this->initFont();
	this->initHPbar();
}

PlayerGUI::~PlayerGUI()
{
	delete this->hpBar;
}

void PlayerGUI::updateHPbar()
{
	// calculates player hp with percentage
	this->hpBar->update(this->player->getSkills()->hp,this->player->getSkills()->hpMax);
	/*float percent = static_cast<float>(this->player->getSkills()->hp) / static_cast<float>(this->player->getSkills()->hpMax);
	this->playerHpBar.setSize(sf::Vector2f(
		static_cast<float>(std::floor(this->playerHpBarMaxWidth * percent)),
		this->playerHpBar.getSize().y));
	
	this->hpBarString = to_string(this->player->getSkills()->hp) + " / " + to_string(this->player->getSkills()->hpMax);
	this->hpBarText.setString("HP: " + this->hpBarString);*/
}

void PlayerGUI::update(const float& dt)
{
	this->updateHPbar();
}

void PlayerGUI::renderHPbar(sf::RenderTarget& target)
{
	this->hpBar->render(target);
}

void PlayerGUI::render(sf::RenderTarget& target)
{
	this->renderHPbar(target);
}
