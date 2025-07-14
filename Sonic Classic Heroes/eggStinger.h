#pragma once
#include "Enemies.h"
class eggStinger: public Enemies
{
	std::string left_address;
	std::string right_address;

	std::string projectileAddress;

	Sprite* projectile;
	Texture* texture;

	int health;
	bool rightMotion;

	bool projectileActive;
	bool shoot;
	
	float speed;

	float Proj_height;
	float Proj_width;

	int proj_hit_box_factor_x;
	int proj_hit_box_factor_y;

	float downMovement;

	Clock eggClock;
	bool goDown;

	const float thresHold = 10.f;

public:

	eggStinger();
	~eggStinger();
	
	void setAttributes(float& x, float& y);
	void enemyAnimations();

	void movement(Sprite& target, char** lvl);

	bool projectileMovement(char** lvl, Player* ob);

	void renderProjectile(RenderWindow& window, float& cameraOffset);

	void setClock();

	int getHealth();
};

