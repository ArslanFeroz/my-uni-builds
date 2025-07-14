#pragma once
#include "Enemies.h"
class crabMeat: public Enemies
{
	int totalFrames;
	int currentFrame;
	int height;
	int width;
	float switch_time;

	bool presentStatus;

	std::string address;
	Clock animationClock;
	Clock movementClock;

	float speed;

	int health;

public:

	bool rightMotion;

	crabMeat();
	void setAttributes(float& x, float& y);
	void enemyAnimations();
	void movement(char** lvl);

	void setMotion();

	int getHealth();
};

