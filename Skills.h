#pragma once
class Skills
{
public: // public because player will access these variables easily
	// leveling
	int level, exp, expN, skillPoints;
	// stats
	int vit, str, dex, agility, intel;
	int hp, hpMax, damageMin, damageMax, accuracy, defence, luck;


	// Constructor / Destructor
	Skills(int level);
	virtual ~Skills();

	// mutators
	void gainExp(const int exp);
	//void loseEXP(const int exp);
	void loseHP(const int hp);
	void gainHP(const int hp);

	// update
	void updateStats(const bool reset);
	void updateLevel();
	void update();

	// DEBUG FUNCTIONS
	string debugPrint() const;
};

