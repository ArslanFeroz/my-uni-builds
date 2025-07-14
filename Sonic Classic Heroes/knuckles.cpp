#include "knuckles.h"
#include <iostream>
knuckles::knuckles() : hitCount(0), ispunching(false)
{

	rightStill = "Data/rightStill.png";
	leftStill = "Data/leftStill.png";
	leftMotion = "Data/knuckles_left_jog.png";
	rightMotion = "Data/knuckles_right_jog.png";
	rightJump = "Data/knuckles_jump_right.png";
	leftJump = "Data/knuckles_jump_left.png";

	float vx = 8;
	float vy = -20;

	setTexture(rightStill, leftStill, leftMotion, rightMotion, leftJump, rightJump);
	setSpeed(vx, vy);

	position_x = 300 - getsprite().getTextureRect().width - 5;
	position_y = 100;

	setPosition(position_x, position_y);


	bool state = false;
	setStatus(state);


	//Indexes for the special powers
	index1 = 0;
	index2 = 0;


	acceleration = 20;

	TotalFrames_k = 4;
	currentFrame_k = 0.1;

	K_height = 40;
	K_width = 40;

	rightPunch_address = "Data/knuckles_punch_right.png";
	leftPunch_address = "Data/knuckles_punch_left.png";

	leftPunch.loadFromFile(leftPunch_address);
	rightPunch.loadFromFile(rightPunch_address);



}

void knuckles::SpecialAbilities(Event& ev, char** l, bool motionLeft)

{



	

	if (SpecialAbilityCounter > 0) {
		if (hitCount > 3) hitCount = 0;

		//if (ev.key.code == Keyboard::Z) {
		//	hitCount++;
		//}

		//if (hitCount > 1) {
		//	// only write the left?neighbour if index2-1 is a valid column

		//	if (l[index1][index2] != '0') {
		//		l[index1][index2] = '0';

		//		SpecialAbilityCounter--;
		//		if (l[index1 - 1][index2] != '0')
		//			l[index1 - 1][index2] = '0';
		//	}

		//	hitCount = 0;


		/*if(ev.key.code == Keyboard::Z && l[index1][index2] == 'b'){

			l[index1][index2] = '0';
			SpecialAbilityCounter--;
					if (l[index1 - 1][index2] != '0')
						l[index1 - 1][index2] = '0';
		}*/

		if (ev.key.code == Keyboard::Z) {

			std::cout << "Breaking the wall: " << std::endl;

			ispunching = true;
			punchingClock.restart();
			if (l[index1][index2] != '0') {
				l[index1][index2] = '0';
				l[index1 - 1][index2] = '0';

			}
		}
		else
			ispunching = false;


	}


}

bool& knuckles::getPunchingStatus()
{
	return ispunching;
	// TODO: insert return statement here
}

void knuckles::setPunchingStatus()
{
	ispunching = false;
}

void knuckles::punChing_animation(std::string& state)
{

	if (punchingClock.getElapsedTime().asSeconds() > switch_time_k) {
		currentFrame_k++;
		if (currentFrame_k >= TotalFrames_k)
			currentFrame_k = 0;

		punchingClock.restart();
	}

	if (state == "L") {
		sprite.setTexture(leftPunch);
	}
	else if (state == "R") {
		sprite.setTexture(rightPunch);
	}

	sprite.setTextureRect(IntRect(currentFrame_k * K_width, 0, K_width, K_height));
}

