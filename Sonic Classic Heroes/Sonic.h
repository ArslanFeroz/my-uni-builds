#pragma once
#include"Player.h"
class Sonic : public Player
{
	std::string leftStill;
	std::string rightStill;
	std::string leftMotion;
	std::string rightMotion;
	std::string leftJump;
	std::string rightJump;

	//Vector2f position;
	bool Boosting;
	Clock boostClock;
	void Acceleration();
	void Deccelerateion();

	float normalSpeed_x;
	float normalSpeed_y;

	float boostSpeed_x;
	float boostSpeed_y;

	/*Vector2f normalSpeed;
	Vector2f boostSpeed;*/

public:

	Sonic();
	// Special events
	void SpecialAbilities(Event& ev, char** l = nullptr, bool motionLeft = false);

};
