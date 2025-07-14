#pragma once
#include"Player.h"


class Tails: public Player
{
	std::string leftStill;
	std::string rightStill;
	std::string leftMotion;
	std::string rightMotion;
	std::string leftJump;
	std::string rightJump;

	//Vector2f position;

	Clock flyClock;
	float flyLimit;
	//char** lvl;  // level being player

	//Clock flyAnimation;

	int totalFrames;
	int currentFrame;
	float switch_time;
	std::string flyAddress_left, flyAddress_right;
	Texture flyTexture_left, flyTexture_right;

	int flyWidth, flyHeight;

protected:
	

public:
	bool firstFly;

	//constructor
	Tails();
	void SpecialAbilities(Event& ev, char** l = nullptr, bool motionLeft = false);

	void flyAnimation(string state = "R");

	bool leftWalk;
	bool rightWalk;

	void test();

	//void flyAnimation
	


};

