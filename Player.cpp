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
	this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color::Green);
	this->playerHpBar.setPosition(Vector2f(20.f, 20.f));

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
	this->velocityMax = 12.f;
	this->velocityMin = 1.f;
	this->acceleration = 2.f;
	this->drag = 0.88f; // deceleration
	this->gravity = 4.f;
	this->velocityMaxY = 15.f;
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
	this->velocity.y = 0.f;
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
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0.f) ? -1.0f : 1.f);
	}
}

void Player::updatePhysics()
{
	//Gravity
	this->velocity.y += 1.0 * this->acceleration;
	if (std::abs(this->velocity.x) > this->velocityMaxY)
	{
		this->velocity.y = this->velocityMaxY * ((this->velocity.y < 0.f) ? -1.0f : 1.f);
	}

	//Deceleration
	this->velocity *= this->drag;

	//Limit deceleration
	if (std::abs(this->velocity.x) < this->velocityMin)
		this->velocity.x = 0.f;
	if (std::abs(this->velocity.y) < this->velocityMin)
		this->velocity.y = 0.f;

	this->sprite.move(this->velocity);
}

void Player::updateMovement()
{
	this->animState = PLAYER_ANIMATION_STATES::IDLE;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) // Left
	{
		this->move(-1.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
		cout << "\r\t\t\tA"; // debugging purposes for input
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) // Right
	{
		this->move(1.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
		cout << "\r\t\t\tD";
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) // Jump
	{ // STILL WORKING ON THE JUMPING	
		//this->move(0.f, 10.f);
		this->animState = PLAYER_ANIMATION_STATES::JUMPING;
	}
}

void Player::updatePlayerCenter()
{
	this->playerCenter =
		Vector2f(this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 2.0f,
			this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 3.4f);
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
		Vector2f(1.f, 0.f), // direction
		5,  // velocity
		0.5f // acceleration
		));
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
	this->playerHpBar.setSize(sf::Vector2f(300.f, this->playerHpBar.getSize().y));
}

void Player::updateAnimations()
{
	if (this->animState == PLAYER_ANIMATION_STATES::IDLE)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f || this->getAnimSwitch())
		{
			this->currentFrame.top = 0.f; 
			this->currentFrame.left += 40.f; // increments by 40 PIXELS, look at player sheet in texture folder
			if (this->currentFrame.left >= 160.f) // each sprite is 4 pixels * 40 pixels = 160.
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_RIGHT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f)
		{
			this->currentFrame.top = 50.f;
			this->currentFrame.left += 40.f; 
			if (this->currentFrame.left >= 360.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}

		this->sprite.setScale(3.f, 3.f);
		this->sprite.setOrigin(0.f, 0.f);
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_LEFT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f)
		{
			this->currentFrame.top = 50.f;
			this->currentFrame.left += 40.f;
			if (this->currentFrame.left >= 360.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}

		this->sprite.setScale(-3.f, 3.f);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 3.f, 0.f);

	}
	else if (this->animState == PLAYER_ANIMATION_STATES::JUMPING)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f)
		{
			this->currentFrame.top = 100.f;
			this->currentFrame.left += 40.f;
			if (this->currentFrame.left >= 120.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
			//resetVelocityY();
		}
	}
	else
		this->animationTimer.restart();
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
