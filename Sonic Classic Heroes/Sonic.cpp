#include "Sonic.h"
#include<iostream>

Sonic::Sonic()
{
	rightStill = "Data/0right_still.png";
	leftStill = "Data/0left_still.png";
	leftMotion = "Data/0jog_left.png";
	rightMotion = "Data/0jog_right.png";
	leftJump = "Data/0upL.png";
	rightJump = "Data/0upR.png";
	
	float vx = 18;
	float vy = -20;
	
	Boosting = false;
	boostClock.restart();
	
	setTexture(rightStill, leftStill, leftMotion, rightMotion, leftJump, rightJump);
	setSpeed(vx, vy);
	
	position_x = 200;
	position_y = 100;

	normalSpeed_x = 18;
	normalSpeed_y = 0;

	boostSpeed_x = 25;
	boostSpeed_y - 0;
	
	setPosition(position_x, position_y);
	
	//Initially setting sonic as the main character
	bool state = true;
	setStatus(state);

	acceleration = 40;
}

void Sonic::SpecialAbilities(Event& ev, char** l, bool motionLeft)
{
	//std::cout << "Time Elapsed : " << boostClock.getElapsedTime().asSeconds() << std::endl;

	

	if (this->SpecialAbilityCounter > 0) {
		if (ev.type == Event::KeyPressed) {

			if (ev.key.code == Keyboard::Z) {
				SpecialAbilityCounter--;
				Acceleration();
			}

		}
	}

	

	if (Boosting)
		Deccelerateion();
}

void Sonic::Acceleration()
{


	if (!Boosting) {
		boostClock.restart();
		Boosting = true;
		setSpeed(boostSpeed_x, boostSpeed_y);
	}

}

void Sonic::Deccelerateion()
{
	if (Boosting && boostClock.getElapsedTime().asSeconds() >= 4) {
		Boosting = false;
		//std::cout << "resetting the speed" << std::endl;
		boostClock.restart();
		setSpeed(normalSpeed_x, normalSpeed_y);
	}
}


