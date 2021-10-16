#pragma once
#include "stdafx.h"
#include "Weapon.h"
using namespace std;
// used in updateMovement() and updateAnimations()
enum PLAYER_ANIMATION_STATES { IDLE = 0, MOVING_LEFT, MOVING_RIGHT, JUMPING, FALLING };

class Player
{
private:
	//Player sprite, texture, hitbox
	sf::Sprite sprite; 
	sf::Texture textureSheet; 
	RectangleShape hitBox;
	Vector2f playerCenter;

	// PLAYER WEAPONS
	map<string, Texture*> laser1Texture;
	vector<Weapon*> laser1;

	// Player GUI
	RectangleShape playerHpBar;
	RectangleShape playerHpBarBack;

	//Player special timing
	int shootCooldown, shootCooldownMax;; // Fire Rate
	int damageCooldown, damageCooldownMax; // how long until you can take dmg after taking dmg

	//Player attributes
	int level, exp, expN, hp, hpMax; // expN is exp until next level up
	int score, damage, damageMax; // ALL DEFAULT CONSTRUCTORS

	//bool moving;
	sf::Clock animationTimer;

	//Animation
	short animState;
	sf::IntRect currentFrame;
	bool animationSwitch;

	// Physics
	sf::Vector2f velocity;
	float velocityMax;
	float velocityMin;
	float acceleration;
	float drag;
	float gravity;		// Gravity may need to be fixed because character is not able to jump properly
	float velocityMaxY;

	// Core CONSTRUCTORS
	void initVariables();
	void initTexture();
	void initGUI();
	void initWeapon();
	void initSprite();
	void initAnimations();
	void initPhysics(); // these all go in the player constructor in declared in line 35.

public:					
	Player(); // constructor // go to player.cpp for the implemenations of the init variables.
	virtual ~Player(); // destructor




	//Accessors
	const bool& getAnimSwitch();
	const sf::Vector2f getPosition() const { return this->sprite.getPosition(); }
	const sf::FloatRect getGlobalBounds() const;
	std::vector<Weapon*> getLasers() { return this->laser1; }



	//Modifiers
	void setPosition(const float x, const float y);
	void resetVelocityY();
	void resetAnimationTimer();
	void move(const float dir_x, const float dir_y);


	//update functions
	void updatePhysics();
	void updateMovement();
	void updatePlayerCenter();
	void updateWeapon(char Dirx, float widthoffset, float scalex);
	void updateWeaponv2();
	void updateWeaponInput();
	void updateGUI();
	void updateAnimations();
	void update();

	// Render
	//void renderGUI();
	void render(sf::RenderTarget& target);
};



