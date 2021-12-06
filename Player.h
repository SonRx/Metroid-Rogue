#pragma once
#include "Entity.h"
#include "Weapon.h"
// used in updateMovement() and updateAnimations()
enum PLAYER_ANIMATION_STATES { IDLE, JUMPING, FALLING, RUNNING};
//leaving MOVING_LEFT and MOVING_RIGHT for code compatability, recomended to use RUNNING now and this->dir to indicate direction

enum PLAYER_DIRECTION { LEFT = -1, RIGHT = 1 };
class Entity;
class Weapon;

class Player :
	public Entity
{
private:
	//Player sprite, texture, hitbox
	sf::Sprite sprite; 
	sf::Texture textureSheet; 
	RectangleShape hitBox;
	Vector2f playerCenter;

	// PLAYER WEAPONS
	map<string, Texture*> laser1Texture;
	vector<Weapon> laser1;

	//Player special timing
	int shootCooldown, shootCooldownMax;; // Fire Rate
	int damageCooldown, damageCooldownMax; // how long until you can take dmg after taking dmg

	//bool moving;
	sf::Clock animationTimer;

	//Animation
	short animState;
	sf::IntRect currentFrame;
	bool animationSwitch;

	float keytime, keytimeMax;
	float jumptime, jumptimeMax; // initialized together with keytime


	// Physics
	sf::Vector2f velocity;
	float velocityMax;
	float velocityMin;
	float acceleration;
	float drag;
	float gravity;		// Gravity may need to be fixed because character is not able to jump properly
	float velocityMaxY;
	

	//player control features
	bool isOnGround = 1;//detects if the player is on ground, set to true for now
	uint8_t resetJumps = 2;
	uint8_t jumps;//how many jumps the player can do, currently defaults to double jumps for testing purposes
	int8_t direction = PLAYER_DIRECTION::RIGHT;//Indicates which way the player is facing, makes playing with code easier
	bool canJump = 0;//basically a trigger disconnect, if this wasnt here the player could fly forever

	// Core CONSTRUCTORS
	void initVariables();
	void initTexture();
	void initWeapon();
	void initSprite();
	void initAnimations();
	void initPhysics(); // these all go in the player constructor in declared in line 35.

public:					
	/* Constructor / destructor */
	Player(); // constructor // go to player.cpp for the implemenations of the init variables.
	virtual ~Player(); // destructor

	/* Accessors */
	const bool& getAnimSwitch();
	const sf::Vector2f& getPosition() const { return this->sprite.getPosition(); }
	const sf::FloatRect getGlobalBounds() const { return this->sprite.getGlobalBounds(); }
	std::vector<Weapon>& getLasers() { return this->laser1; }
	const bool& getCanJump() const { return this->canJump; }
	Skills* getSkills();

	const int& getHpMax() const;

	const bool getKeytime();
	const bool getJumpTime();
	virtual void updateKeyTime(const float& dt);

	/* Modifiers */
	void setPosition(const float x, const float y);

	virtual void resetVelocity();
	virtual void resetVelocityX();
	virtual void resetVelocityY();

	void resetAnimationTimer();
	void move(const float dir_x, const float dir_y);

	void moveVert (const float dir);//seperate movement controls to make life easier
	void moveHori (const float dir);//seperate movement controls to make life easier

	// HP
	void loseHP(const int hp);
	//void loseEXP(const int exp);
	void gainHP(const int hp);
	//void gainEXP(const int exp);

	/* update functions */
	void updatePhysics();
	void updateMovement();
	void updatePlayerCenter();
	void updateWeaponv2();
	void updateWeaponInput();
	void setupPlayerSprite (float incr, float top, float limit, float time);//little function to make things easier
	void updateAnimations();
	void update(const float& dt, sf::Vector2f& mouse_pos_view);

	// Render
	void render(sf::RenderTarget& target, const bool show_hitBox = false);
};



