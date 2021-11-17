#include "stdafx.h"
#include "Player.h"

void Player::initVariables()
{
	this->animState = PLAYER_ANIMATION_STATES::IDLE;
	this->shootCooldownMax = 25;
	this->shootCooldown = this->shootCooldownMax;
	this->damageCooldownMax = 10;
	this->damageCooldown = this->damageCooldownMax;
}

void Player::initTexture()
{
	if (!this->textureSheet.loadFromFile("Textures/player_sheet.png"))
	{
		std::cout << "ERROR::PLAYER::Could not load the player_sheet.png!" << "\n";
	}
}

void Player::initGUI()
{
	//Init player GUI
	this->playerHpBar.setSize(sf::Vector2f(300, 25));
	this->playerHpBar.setFillColor(sf::Color::Green);
	this->playerHpBar.setPosition(Vector2f(20, 20));

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
}

void Player::initWeapon()
{
	// laser 1 - blaster
	this->laser1Texture["WEAPON"] = new Texture();
	this->laser1Texture["WEAPON"]->loadFromFile("Textures/Lasers/20.png");
}


void Player::initSprite()
{
	this->sprite.setTexture(this->textureSheet);
	this->currentFrame = sf::IntRect(0, 0, 40, 50);

	this->sprite.setTextureRect(currentFrame);
	this->sprite.setScale(3.f, 3.f);

	this->sprite.setPosition(960,540);
}

void Player::initAnimations()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::initPhysics()
{
	this->velocityMax = 12;
	this->velocityMin = 1;
	this->acceleration = 2;
	this->drag = 0.88; // deceleration
	this->gravity = 4;
	this->velocityMaxY = 15;
}

Player::Player()
	:level(1), exp(0), expN(50), hp(10),
	hpMax(10), score(0), damage(1), damageMax(2)  // DEFAULT CONSTRUCTORS
{
	this->initVariables();
	this->initTexture();
	this->initGUI();
	this->initWeapon();
	this->initSprite();
	this->initAnimations();
	this->initPhysics();
}

Player::~Player()
{
	for (auto& i : this->laser1Texture)
	{
		delete i.second;
	}

	/*for (auto& i : this->laser1)
	{
		delete i;
	}*/
}

// Accessors
const bool& Player::getAnimSwitch()
{
	bool anim_switch = this->animationSwitch;

	if (this->animationSwitch)
		this->animationSwitch = false;

	return anim_switch;
}

//const sf::Vector2f Player::getPosition() const
//{
//	return this->sprite.getPosition();
//}

const sf::FloatRect Player::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

//inline vector<Weapon*> Player::getLasers()
//{
//	return this->laser1;
//}




// Modifiers
void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::resetVelocityY()
{
	this->velocity.y = 0;
}

void Player::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::move(const float dir_x, const float dir_y)
{
	// Acceleration
	this->velocity.x += dir_x * this->acceleration;


	//Limit velocity
	if (std::abs(this->velocity.x) > this->velocityMax)
	{
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0) ? -1 : 1);
	}
}

void Player::moveVert (const float dir) {
	this->velocity.y -= dir * this->acceleration;//made subtract so the expected directions is used. dir positive is up, dir negative is down
}

void Player::moveHori (const float dir) {
	this->velocity.x += dir * this->acceleration;

	//Limit velocity
	if (std::abs(this->velocity.x) > this->velocityMax)
	{
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0) ? -1 : 1);
	}
}

void Player::updatePhysics()
{
	//Gravity
	this->velocity.y += 1.0 * this->acceleration;
	if (std::abs(this->velocity.x) > this->velocityMaxY)
	{
		this->velocity.y = this->velocityMaxY * ((this->velocity.y < 0) ? -1 : 1);
	}

	//Deceleration
	this->velocity *= this->drag;

	//Limit deceleration
	if (std::abs(this->velocity.x) < this->velocityMin)
		this->velocity.x = 0;
	if (std::abs(this->velocity.y) < this->velocityMin)
		this->velocity.y = 0;

	this->sprite.move(this->velocity);
}

void Player::updateMovement()
{
	cout << "\r\t\t\t          ";
	cout << "\r\t\t\t";

	this->animState = PLAYER_ANIMATION_STATES::IDLE;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) // Left
	{
		this->direction = PLAYER_DIRECTION::LEFT;//-1
		
		this->moveHori(this->direction);

		if(this->animState != PLAYER_ANIMATION_STATES::JUMPING)
			this->animState = PLAYER_ANIMATION_STATES::RUNNING;

		cout << "A"; // debugging purposes for input
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) // Right
	{
		this->direction =  PLAYER_DIRECTION::RIGHT;//1
		
		this->moveHori(this->direction);

		if(this->animState != PLAYER_ANIMATION_STATES::JUMPING)
			this->animState = PLAYER_ANIMATION_STATES::RUNNING;

		cout << "D";
	}

	if (this->isOnGround) {
		this->jumps = this->resetJumps;
	}

	static bool canJump;//basically a trigger disconnect, if this wasnt here the player could fly forever

	if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Space)) // Jump
	{ // STILL WORKING ON THE JUMPING	
		if (--(this->jumps) && canJump){//decrements the jumps but treats as bool, when zero the player cant jumps anymore
			this->moveVert(40);
			this->animState = PLAYER_ANIMATION_STATES::JUMPING;
		}
		canJump = 0;
		cout << "s";
	} else {
		canJump = 1;
	}
}

void Player::updatePlayerCenter()
{
	this->playerCenter =
		Vector2f(this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 2.0,
			this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 3.4);
}

void Player::updateWeapon(char Dirx, float widthoffset, float scalex)
{
	//if (Mouse::isButtonPressed(Mouse::Left)) // left click to shoot
	//{
	//	this->laser1.push_back(new Weapon(this->laser1Texture["WEAPON"],
	//		this->sprite.getPosition().x + widthoffset,
	//		this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 3.5f,
	//		Dirx, 0, 5, scalex, .4f));
	//	cout << "V";
	//}

	//if (Mouse::isButtonPressed(Mouse::Left)) // left click to shoot
	//{
	//	this->laser1.push_back(new Weapon(this->laser1Texture["WEAPON"],
	//		this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 2.0f,
	//		this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 3.4f,
	//		1.f, 0.f, 5.f, .4f, .4f));
	//	cout << "V";
	//}

	
}

void Player::updateWeaponv2() //  SHOOOOOT
{
	if (Mouse::isButtonPressed(Mouse::Left)) // left click to shoot
	{
		this->laser1.push_back(Weapon(this->laser1Texture["WEAPON"], // texture
		this->playerCenter, // position of player
		Vector2f(this->direction, 0), // direction
		5,  // velocity
		0.5f, // acceleration
		this->direction));
		cout << "\r\t\t\t\tSHOT";
	}
}

void Player::updateWeaponInput()
{
	//char dir = 1;
	//if (Keyboard::isKeyPressed(Keyboard::A)) // while moving left, shoot left, need better algo
	//{
	//	char dir = -1;
	//	updateWeapon(dir, this->sprite.getGlobalBounds().width / 2.0f, -.4f);
	//}
	//else
	//{
	//	updateWeapon(dir, this->sprite.getGlobalBounds().width / 2.0f, .4f);
	//}
	// update laser to move // removing this makes laser still

	updateWeaponv2();
	for (size_t i = 0; i < this->laser1.size(); i++)
	{
		this->laser1[i].update();
	}
}

void Player::updateGUI()
{
	this->playerHpBar.setSize(sf::Vector2f(300, this->playerHpBar.getSize().y));
}


void Player::setupPlayerSprite (float incr, float top, float limit, float time) {

	if (this->animationTimer.getElapsedTime().asSeconds() >= time || this->getAnimSwitch())
	{
		this->currentFrame.top = top; 
		this->currentFrame.left += incr; 
		if (this->currentFrame.left >= limit) {
			this->currentFrame.left = 0;
			this->animState = PLAYER_ANIMATION_STATES::IDLE;
		}

		this->animationTimer.restart();
		this->sprite.setTextureRect(this->currentFrame);
	}
}

void Player::updateAnimations()
{
	if (this->animState == PLAYER_ANIMATION_STATES::IDLE)
	{
		setupPlayerSprite(40, 0, 160, 0.2);

	}
	else if (this->animState == PLAYER_ANIMATION_STATES::RUNNING) {
		setupPlayerSprite(40, 50,  360, 0.1);

		this->sprite.setScale(3*this->direction, 3);

		if(this->direction==PLAYER_DIRECTION::LEFT)
			this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 3, 0);
		else
			this->sprite.setOrigin(0, 0);
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::JUMPING)
	{
		setupPlayerSprite(40, 100,  120, 0.1);
	}
}

void Player::update(const float& dt)
{
	this->updateMovement();
	this->updateGUI();
	this->updatePlayerCenter();
	this->updateAnimations();
	this->updatePhysics();
	this->updateWeaponInput();
}

void Player::render(sf::RenderTarget* target)
{
	// render laser
	for (size_t i = 0; i < this->laser1.size(); i++)
	{
		this->laser1[i].render(target);
	}

	// render player -> called in game class
	target->draw(this->sprite);

	// RenderGUI
	target->draw(this->playerHpBarBack);
	target->draw(this->playerHpBar);
}
