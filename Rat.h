#pragma once
#include "Enemy.h"
class Rat :
	public Enemy
{
private:
	void initVariables();
	void initAnimations();
	//void initAI();
	void initGUI();

	sf::RectangleShape hpBar;

	//AIFollow* follow;

public:
	Rat(float x, float y, sf::Texture& texture_sheet);
	virtual ~Rat();

	//Functions
	void updateAnimation(const float& dt);
	void update(const float& dt, sf::Vector2f& mouse_pos_view);

	void render(sf::RenderTarget& target, const bool show_hitBox);
};
