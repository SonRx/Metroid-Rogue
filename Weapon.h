#pragma once

class Weapon
{
private:
	Sprite sprite;

	Vector2f direction;
	Vector2f curVelocity;
	float maxVelocity;
	float accel;

	float movementSpeed; // dont need

public:
	// CONSTRUCTORS
	Weapon();				
	// OVERLOADED CONSTRUCTOR
	Weapon(Texture *texture, float pos_x, float pos_y, float dir_x,float dir_y,	
		float movement_speed, float scalex, float scaley);
	// OVERLOADED CONSTRUCTOR V2
	Weapon(Texture* texture, Vector2f position, Vector2f dir, 
		float maxVel, float accel, float scale);

	virtual ~Weapon(); // DESTRUCTOR

	//Accessors
	const FloatRect getBounds() const;
	const Vector2f getPos() const;
	

	// Functions

	void update();
	void render(RenderTarget* target);
};

