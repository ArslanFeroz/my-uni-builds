#include "moto_bug.h"

moto_bug::moto_bug()
{
	height = 25;
	width = 31;
	speed = 2.f;

	totalFrames = 5;
	currentFrame = 0;
	address = "Data/motoBug.png";
	switch_time = 0.2f;

	rightMotion = false;
	health = 2;
	animationClock.restart();


	Pwidth = 31 * 1.8;
	Pheight = 25 * 1.8;

	hit_box_factor_x = (1.0 - 0.8) * 0.5 * Pwidth;
	hit_box_factor_y = (1.0 - 0.9) * 0.5 * Pheight;
}

void moto_bug::setAttributes(float& x, float& y)
{
	setData(address, height, width, x, y, health, 1.8, 1.8);
}

void moto_bug::enemyAnimations()
{
	if (rightMotion) {
		spriteSheet->loadFromFile(address);
		sprite->setTexture(*spriteSheet);
	}
	else {

		spriteSheet->loadFromFile(address);
		sprite->setTexture(*spriteSheet);
	}

	if (animationClock.getElapsedTime().asSeconds() > switch_time) {

		currentFrame++;
		if (currentFrame >= totalFrames)
			currentFrame = 0;


		animationClock.restart();
	}

	sprite->setTextureRect(IntRect(currentFrame * width, 0, width, height));
}



void moto_bug::movement(Player& ob, char** lvl)
{
	if (ob.getsprite().getPosition().x > position.x)
		rightMotion = true;
	else
		rightMotion = false;


	if (rightMotion) {
		if(noCollision(lvl, position.x + speed, position.y))
			position.x += speed;
	}
	else {
		if(noCollision(lvl, position.x - speed, position.y))
			position.x -= speed;

	}

	sprite->setPosition(position);
}

int moto_bug::getHealth()
{
	return health;
}


