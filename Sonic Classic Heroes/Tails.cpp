#include "Tails.h"
#include <iostream>
using namespace std;

Tails::Tails()
{
	rightStill = "Data/tails_right.png";
	leftStill = "Data/tails_left.png";
	leftMotion = "Data/tails_jog_leftnew.png";
	rightMotion = "Data/tails_jog_rightnew.png";
	leftJump = "Data/tails_jump_right.png";
	rightJump = "Data/tails_jump_right.png";
	
	float vx = 10;
	float vy = -20;
	
	setTexture(rightStill, leftStill, leftMotion, rightMotion, leftJump, rightJump);
	setSpeed(vx, vy);
	
	position_x = 150 - getsprite().getTextureRect().width - 5;
	position_y = 100;
	
	setPosition(position_x, position_y);
	flyClock.restart();
	firstFly = true;
	bool state = false;
	flyLimit = 7;
	setStatus(state);

	currentFrame = 0;
	totalFrames = 10;
	switch_time = 0.05;

	acceleration = 15;

	flyAddress_left = "Data/tails_flying_left.png";
	flyAddress_right = "Data/tails_flying_right.png";

	flyTexture_left.loadFromFile(flyAddress_left);
	flyTexture_right.loadFromFile(flyAddress_right);

	flyHeight = 40;
	flyWidth = 40;
	
}

void Tails::SpecialAbilities(Event& ev, char** l, bool motionLeft)
{

	/*if (firstFly) {
		SpecialAbilityCounter--;
	}

	if (SpecialAbilityCounter < 0)
		SpecialAbilityCounter = 0;
	if (SpecialAbilityCounter > 0) {

		if (ev.key.code == Keyboard::Z && !isFlying) {
			isFlying = true;
			flyClock.restart();
		}

	}*/

	if (ev.key.code == Keyboard::Z && ev.type == Event::KeyPressed && !isFlying	&& SpecialAbilityCounter > 0)
	{
		// consume one charge
		--SpecialAbilityCounter;

		// enter flying mode
		isFlying = true;
		flyClock.restart();
		
	}

	

}

void Tails::flyAnimation(string state)
{


	if (flyClock.getElapsedTime().asSeconds() > 0.1) {

		currentFrame++;
		cout << "Changing frames" << endl;

		if (currentFrame >= totalFrames)
			currentFrame = 0;

		flyClock.restart();

	}

	if (state == "L") {
		sprite.setTexture(flyTexture_left);
	}
	else if (state == "R") {
		sprite.setTexture(flyTexture_right);
	}

	sprite.setTextureRect(IntRect(currentFrame * flyWidth, 0, flyWidth, flyHeight));

}



void Tails::test()
{
	return;
}
