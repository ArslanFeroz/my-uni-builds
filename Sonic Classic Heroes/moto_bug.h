#pragma once
#include "Enemies.h"
#include "Player.h"
class moto_bug: public Enemies
{
	int totalFrames;
	int currentFrame;
	int height;
	int width;
	float switch_time;

	std::string address;
	Clock animationClock;
	int health;
	Vector2f moto_scale;

	float speed;


public:
	moto_bug();
	bool rightMotion;


	void setAttributes(float& x, float& y);
	void enemyAnimations();

	void movement(Player& ob, char** lvl);
	int getHealth();
};

