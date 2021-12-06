#include "stdafx.h"
#include "Player.h"

void Player::initVariables()
{
	this->animState = PLAYER_ANIMATION_STATES::IDLE;
	this->shootCooldownMax = 25;
	this->shootCooldown = this->shootCooldownMax;
	this->damageCooldownMax = 10;
	this->damageCooldown = this->damageCooldownMax;


	// firerate
	this->keytime = 0.f;
	this->keytimeMax = 15.f; // SERVES AS THE PLAYER FIRERATE

	// jumprate
	this->jumptime = 0.f;
	this->jumptimeMax = 60.f;
}

void Player::initTexture()
{
	if (!this->textureSheet.loadFromFile("Textures/player_sheet.png"))
	{
		std::cout << "ERROR::PLAYER::Could not load the player_sheet.png!" << "\n";
	}
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

	//this->sprite.setPosition(960,540);
	this->sprite.setPosition(400, 1000);
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
	this->drag = 0.88f; // deceleration
	this->gravity = 4;
	this->velocityMaxY = 15;
}

Player::Player()
{
	//this->createHitbox(this->sprite, 25.f, 25.f, 75.f, 115.f);
	this->createHitbox(this->sprite, 25.f, 25.f, 70.f, 125.f);
	this->createSkills(1);
	this->initVariables();
	this->initTexture();
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
}

// Accessors -> Most of the accessors are already implemented in the header class
const bool& Player::getAnimSwitch()
{
	bool anim_switch = this->animationSwitch;

	if (this->animationSwitch)
		this->animationSwitch = false;

	return anim_switch;
}


Skills* Player::getSkills()
{
	return this->skills;
}

const bool Player::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}
	return false;
}

const bool Player::getJumpTime()
{
	if (this->jumptime >= this->jumptimeMax)
	{
		this->jumptime = 0.f;
		return true;
	}
	return false;
}

void Player::updateKeyTime(const float& dt)
{
	if (this->keytime < this->keytimeMax)
		this->keytime += 100.f * dt;

	if (this->jumptime < this->jumptimeMax)
		this->jumptime += 100.f * dt;
}

// Modifiers
void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::resetVelocity() // stops both directions
{
	this->velocity.x = 0;
	this->velocity.y = 0;
}

void Player::resetVelocityX() // stops velocity x
{
	this->velocity.x = 0;
}

void Player::resetVelocityY() // stops velocity y
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

// HP implementation
void Player::loseHP(const int hp)
{
	this->skills->loseHP(hp);
}

//void Player::loseEXP(const int exp)
//{
//	this->skills->exp -= exp;
//
//	if (this->skills->exp < 0)
//		this->skills->exp = 0;
//}

void Player::gainHP(const int hp)
{
	this->skills->gainHP(hp);
}

//void Player::gainEXP(const int exp)
//{
//	this->skills->gainExp(exp);
//}

void Player::updatePhysics()
{
	//Gravity
	/*this->velocity.y += 1.0 * this->acceleration;
	if (this->velocity.y = 2) {
		if (std::abs(this->velocity.x) >= this->velocityMaxY)
		{
			this->velocity.y = this->velocityMaxY * ((this->velocity.y < 0) ? -1 : 1);
		}
	}*/
	//system("cls");
	//cout << velocity.y << " " << velocityMaxY << " " << direction << "\n";

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

	if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) // Left
		{
			this->direction = PLAYER_DIRECTION::LEFT;//-1

			this->moveHori(this->direction);
			this->moveVert(-1.f);

			if (this->animState != PLAYER_ANIMATION_STATES::JUMPING)
				this->animState = PLAYER_ANIMATION_STATES::RUNNING;

			cout << "A"; // debugging purposes for input
		} 
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) // Right
		{
			this->direction = PLAYER_DIRECTION::RIGHT;//1

			this->moveHori(this->direction);
			this->moveVert(-1.f);

			if (this->animState != PLAYER_ANIMATION_STATES::JUMPING)
				this->animState = PLAYER_ANIMATION_STATES::RUNNING;

			cout << "D";
		}
	}
	else {
		cout << "AD";
	}
	if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)))
	{
		this->moveVert(-1.f);

		if (this->animState != PLAYER_ANIMATION_STATES::JUMPING)
			this->animState = PLAYER_ANIMATION_STATES::IDLE;
	}

	if (this->isOnGround) {
		this->jumps = this->resetJumps;
	}

		//static bool canJump;//basically a trigger disconnect, if this wasnt here the player could fly forever

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && getJumpTime()) // Jump
		{ // STILL WORKING ON THE JUMPING
			if ((this->jumps <= 2) && canJump) {//decrements the jumps but treats as bool, when zero the player cant jumps anymore
				this->jumps--;
				this->moveVert(28);
				this->animState = PLAYER_ANIMATION_STATES::JUMPING;
			}
			cout << "#j: " << jumps;
			canJump = 0;
			cout << "s";
		}
		else {
			canJump = 1;
		}
}

void Player::updatePlayerCenter()
{
	this->playerCenter =
		Vector2f(this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 2.0,
			this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 3.4);
}

void Player::updateWeaponv2() //  SHOOOOOT
{
	if (Mouse::isButtonPressed(Mouse::Left) && getKeytime()) // left click to shoot
	{
		this->laser1.push_back(Weapon(this->laser1Texture["WEAPON"], // texture
		this->playerCenter, // position of player
		Vector2f(this->direction, 0), // direction
		10,  // velocity 5
		0.5f, // acceleration
		this->direction));
		cout << "\r\t\t\t\tSHOT";
	}
}

void Player::updateWeaponInput()
{
	updateWeaponv2();
	for (size_t i = 0; i < this->laser1.size(); i++)
	{
		this->laser1[i].update();
	}
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

void Player::update(const float& dt, sf::Vector2f& mouse_pos_view)
{
	//this->skills->update();
	//system("cls"); // clears anything before it
	//cout << this->skills->debugPrint() << "\n";
	this->updateKeyTime(dt);

	this->updateMovement();
	this->updatePlayerCenter();
	this->updateAnimations();
	this->updatePhysics();
	this->updateWeaponInput();

	this->hitbox->update();
}

void Player::render(sf::RenderTarget& target, const bool show_hitBox)
{
	// render laser
	for (size_t i = 0; i < this->laser1.size(); i++)
	{
		this->laser1[i].render(&target);
	}

	// render player -> called in game class
	target.draw(this->sprite);

	// RenderGUI
	//target.draw(this->playerHpBarBack);
	//target.draw(this->playerHpBar);

	// hitbox
	if (show_hitBox)
		this->hitbox->render(target);
}
