#include "crabMeat.h"

crabMeat::crabMeat()
{
	totalFrames = 7;
	currentFrame = 0;
	height = 33;
	width = 45;
	switch_time = 0.1f;
	address = "Data/crabMeat.png";
	speed = 4.f;
	health = 4;

	animationClock.restart();
	movementClock.restart();
	rightMotion = false;
	presentStatus = true;


	//Calculating the hitboxes
	Pwidth = 45 * 1.8;
	Pheight = 33 * 1.8;

	hit_box_factor_x = (1.0 - 0.8) * 0.5 * Pwidth;
	hit_box_factor_y = (1.0 - 0.9) * 0.5 * Pheight;

}

void crabMeat::setAttributes(float& x, float& y)
{
	setData(address, height, width, x, y, health, 1.8, 1.8);
}

void crabMeat::enemyAnimations()
{
	if (animationClock.getElapsedTime().asSeconds() > switch_time) {

		currentFrame++;
		if (currentFrame > totalFrames)
			currentFrame = 0;

		animationClock.restart();
	}

	sprite->setTextureRect(IntRect(currentFrame * width, 0, width, height));
}

void crabMeat::movement(char** lvl)
{
	if (movementClock.getElapsedTime().asSeconds() > 7) {
		rightMotion = !rightMotion;
		movementClock.restart();
	}

	if (!noCollision(lvl, position.x + speed, position.y)) {
		rightMotion = !rightMotion;
		movementClock.restart();
	}
	else if (!noCollision(lvl, position.x - speed, position.y)) {
		rightMotion = !rightMotion;
		movementClock.restart();
	}

	if (rightMotion) {
		position.x += speed;
	}
	else
		position.x -= speed;

	sprite->setPosition(position);
}

void crabMeat::setMotion()
{
	rightMotion = !rightMotion;
}

int crabMeat::getHealth()
{
	return health;
}
