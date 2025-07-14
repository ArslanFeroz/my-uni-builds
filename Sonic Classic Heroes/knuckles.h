#pragma once

#include "Player.h"

class knuckles : public Player
{
	std::string leftStill;
	std::string rightStill;
	std::string leftMotion;
	std::string rightMotion;
	std::string rightJump;
	std::string leftJump;
	//Vector2f position;
	int hitCount;  // If the knuckles will hit the wall more than 3 times the wall will break
	

	int currentFrame_k;
	int TotalFrames_k;
	float switch_time_k;

	int K_height;
	int K_width;

	std::string leftPunch_address;
	std::string rightPunch_address;

	Texture leftPunch;
	Texture rightPunch;

	bool ispunching;

	Clock punchingClock;

public:

	knuckles();
	void SpecialAbilities(Event& ev, char** l = nullptr, bool motionLeft = false);
	bool& getPunchingStatus();
	void setPunchingStatus();
	void punChing_animation(std::string& state);

	
};

