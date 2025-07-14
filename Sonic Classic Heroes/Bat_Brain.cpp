#include "Bat_Brain.h"

Bat_Brain::Bat_Brain()
{
	totalFrames = 4;
	width = 52;
	height = 52;
	switch_time = 0.1;
	currentFrame = 0;
	address = "Data/batBrain.png";
	health = 3;


	Pwidth = 52 * 1.8;
	Pheight = 52 * 1.8;

	hit_box_factor_x = (1.0 - 0.8) * 0.5 * Pwidth;
	hit_box_factor_y = (1.0 - 0.9) * 0.5 * Pheight;

}

void Bat_Brain::setAttributes(float& x, float& y)
{
	setData(address, height, width, x, y, health, 1.8, 1.8);
}

void Bat_Brain::enemyAnimations()
{

	if (clock.getElapsedTime().asSeconds() > switch_time) {
		currentFrame++;
		if (currentFrame >= totalFrames) {
			currentFrame = 0;
		}
		clock.restart();

	}

	//Setting the texture rect;
	sprite->setTextureRect(IntRect(currentFrame * width, 0, width, height));
}

void Bat_Brain::movements(Sprite& target, char** lvl)
{
	Vector2f target_pos(target.getPosition().x, target.getPosition().y);

	if (position.x > target_pos.x) {

		if(noCollision(lvl, position.x - 5, position.y))
			position.x -= 5;
		sprite->setPosition(position);
	}

	if (position.x < target_pos.x) {
		if (noCollision(lvl, position.x + 5, position.y))
			position.x += 5;
		sprite->setPosition(position);
	}

	//IF the robot is above the taget than lower down
	/*if (position.x == target_pos.x) {


		if(posi)
	}*/
}

int Bat_Brain::getHealth()
{
	return health;
}

void Bat_Brain::setHealth(int h)
{
	health = h;
}

bool Bat_Brain::getActivation()
{
	return activation;
}

void Bat_Brain::setActivation(bool& b)
{
	activation = b;
}
