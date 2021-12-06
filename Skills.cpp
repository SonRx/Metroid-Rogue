#include "stdafx.h"
#include "Skills.h"

// constructor / destructor
Skills::Skills(int level)
{
	this->level = level;
	this->exp = 0;
	this->expN = static_cast<int>((50/3) * (pow(this->level + 1, 3) - 6 * pow(this->level + 1,2) + ((this->level + 1) * 17) - 12));
	this->skillPoints = 2;

	this->vit = 100;
	this->str = 1;
	this->dex = 1;
	this->agility = 1;
	this->intel = 1;

	this->updateLevel();
	this->updateStats(true);
}

Skills::~Skills()
{

}

void Skills::gainExp(const int exp)
{
	this->exp += exp;
	this->updateLevel();
}

void Skills::loseHP(const int hp)
{
	this->hp -= hp;

	if (this->hp < 0)
		this->hp = 0;
}

void Skills::gainHP(const int hp)
{
	this->hp += hp;

	if (this->hp > this->hpMax)
		this->hp = this->hpMax;
}

void Skills::updateStats(const bool reset)
{
	this->hpMax		 = this->vit * 10 + this->vit + this->str / 2 + this->intel / 5;
	this->damageMin	 = this->str * 2 + this->str / 4;
	this->damageMax	 = this->str * 2 + this->str / 2;
	this->accuracy	 = this->dex * 5 + this->dex / 2;
	this->defence	 = this->agility * 2 + this->agility / 4;
	this->luck		 = this->intel * 2 + this->intel / 5;

	if (reset)
	{
		this->hp = this->hpMax;
	}
}

void Skills::updateLevel()
{
	while (this->exp >= this->expN)
	{
		++this->level;
		this->exp -= this->expN;
		this->expN = static_cast<unsigned>((50 / 3)* (pow(this->level, 3) - 6 * pow(this->level, 2) + (this->level * 17) - 12));
		++this->skillPoints;
	}
}

// update

void Skills::update()
{
	this->updateLevel();
}

string Skills::debugPrint() const
{
	stringstream ss;

	ss << "Level: " << this->level << "\n"
		<< "Exp: " << this->exp << "\n"
		<< "ExpN: " << this->expN << "\n"
		<< "SkillPts: " << this->skillPoints << "\n";

	return ss.str();
}
