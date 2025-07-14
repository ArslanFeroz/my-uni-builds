#pragma once
#include "Enemies.h"

class Bat_Brain: public Enemies
{
	//Animation related information
	int totalFrames;
	int Height;
	int width;

	std::string address;
	float switch_time;
	int currentFrame;

	int health;

	bool activation;

public:

	Bat_Brain();

	void setAttributes(float& x, float& y);
	void enemyAnimations();
	void movements(Sprite& target, char** lvl);

	int getHealth();
	void setHealth(int h);

	bool getActivation();
	void setActivation(bool& b);
};

