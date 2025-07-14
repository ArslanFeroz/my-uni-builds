#include "eggStinger.h"
#include <iostream>
using namespace std;

eggStinger::eggStinger(): goDown(false), downMovement(0)
{
	left_address = "Data/left_egg.png";
	right_address = "Data/right_egg.png";

	projectileAddress = "Data/projectileL.png";
	projectile = new Sprite;
	texture = new Texture;
	texture->loadFromFile(projectileAddress);
	projectile->setTexture(*texture);

	height = 309;
	width = 320;

	float tempx = 0.5;
	float tempy = 0.5;
	setScale(tempx, tempy);
	
	health = 20;
	rightMotion = true;
	speed = 3.f;


	Pwidth = width * tempx;
	Pheight = height * tempy;

	hit_box_factor_x = (1.0 - 0.8) * 0.5 * Pwidth;
	hit_box_factor_y = (1.0 - 0.9) * 0.5 * Pheight;

	Proj_height = 33;
	Proj_width = 31;
	proj_hit_box_factor_x = (1.0 - 0.8) * 0.5 * Proj_width;
	proj_hit_box_factor_y = (1.0 - 0.8) * 0.5 * Proj_height;

	eggClock.restart();
}

eggStinger::~eggStinger()
{
	delete projectile;
	delete texture;
}



void eggStinger::setAttributes(float& x, float& y)
{
	setData(left_address, height, width, x, y, health, 0.7, 0.7);
}

void eggStinger::enemyAnimations()
{
	if (rightMotion) {
		spriteSheet->loadFromFile(right_address);
	}
	else
		spriteSheet->loadFromFile(left_address);

	sprite->setTexture(*spriteSheet);
}

void eggStinger::movement(Sprite& target, char** lvl)
{


	//cout << "In the movement function" << endl;

	float target_x = target.getPosition().x;
	float target_y = target.getPosition().y;

	float enemy_x = position.x;
	float enemy_y = position.y;


	//cout << "Target coordinates : " << target_x << ' ' << target_y << "\tEnemy Coordinates : " << enemy_x << ' ' << enemy_y << endl;
	// Movement of the eggstinger towards the enemy


	if (!goDown) {

		if (downMovement > 0)
		{
			position.y -= speed;
			downMovement -= speed;
		}
		else {
			if (target_x > enemy_x + 5) {
				if (noCollision(lvl, enemy_x + speed, enemy_y)) {

					//cout << "In right Motions" << endl;
					rightMotion = true;
					position.x += speed;
					sprite->setPosition(position);
				}
			}
			else if (target_x < enemy_x - 5) {

				if (noCollision(lvl, enemy_x - speed, enemy_y)) {
					rightMotion = false;
					position.x -= speed;
					sprite->setPosition(position);
				}
			}
			
		}

		
	}
	else {

		if (downMovement < 250) {
			position.y += speed;
			downMovement += speed;
		}
		else {

			if (!shoot) {
				shoot = true;
				projectileActive = true;
				projectile->setPosition(position.x + (sprite->getTextureRect().width) / 2, position.y + sprite->getTextureRect().height - 50);

				goDown = false;
				eggClock.restart();

			}

		}

	}

	

	setClock();
	

	// Shooting the projectile from the egg stinger
	/*if (!shoot) {

		cout << "Launching the projectile" << endl;
		shoot = true;
		projectileActive = true;
		projectile->setPosition(position.x + (sprite->getTextureRect().width) / 2, position.y + sprite->getTextureRect().height);
	}*/

	


}

bool eggStinger::projectileMovement(char** lvl, Player* ob)
{



	if (!shoot)
		return false;

	// If the projectile gets out of bound then return
	if (position.y > 750) {
		shoot = false;
		projectileActive = false;
		return false;
	}
	// Firstly checking if beneath is a tile
	
	//cout << "in the projectile movement" << endl;


	projectile->setPosition(projectile->getPosition().x, projectile->getPosition().y + 10);

	float position_y = projectile->getPosition().y;
	float position_x = projectile->getPosition().x;

	int rowBelow = int((position_y + proj_hit_box_factor_y + Proj_height) / cell_size);
	int colLeft = int((position_x + proj_hit_box_factor_x) / cell_size);
	int colRight = int((position_x + proj_hit_box_factor_x + Proj_width) / cell_size);


	if (rowBelow < 0 || rowBelow >= 14 ||
		colLeft < 0 || colLeft >= 250 ||
		colRight < 0 || colRight >= 250)
	{
		projectileActive = false;
		shoot = false;
		return false;
	}


	if (lvl[rowBelow][colLeft] == 'q' || lvl[rowBelow][colLeft] == 'b' || lvl[rowBelow][colLeft] == 'w'
		|| lvl[rowBelow][colRight] == 'q' || lvl[rowBelow][colRight] == 'b' || lvl[rowBelow][colRight] == 'w') {

		// Dimnishing that tile
		// marking it as '0'
		if (lvl[rowBelow][colLeft] != '0')
			lvl[rowBelow][colLeft] = '0';
		else if (lvl[rowBelow][colRight] != '0')
			lvl[rowBelow][colLeft] = '0';


		projectileActive = false;
		shoot = false;
		return false;

	}

	// If the collision with the block is not found
	// then checking the collision with the player


	float px = position_x;
	float py = position_y;
	float pw = projectile->getTextureRect().width * projectile->getScale().x;
	float ph = projectile->getTextureRect().height * projectile->getScale().y;

	
	float ux = ob->getsprite().getPosition().x;
	float uy = ob->getsprite().getPosition().y;
	float uw = ob->getsprite().getTextureRect().width * ob->getsprite().getScale().x;
	float uh = ob->getsprite().getTextureRect().height * ob->getsprite().getScale().y;


	
	bool hit =
		(px + pw > ux) &&
		(px < ux + uw) &&
		(py + ph > uy) &&
		(py < uy + uh);

	if (hit) {
		projectileActive = false;
		shoot = false;
		return true;
	}
	return false;




}

void eggStinger::renderProjectile(RenderWindow& window, float& cameraOffset)
{
	if (projectileActive) {
		float temp_x = projectile->getPosition().x;
		float temp_y = projectile->getPosition().y;
		projectile->setPosition(temp_x - cameraOffset, temp_y);
		window.draw(*projectile);
		projectile->setPosition(temp_x, temp_y);  
	}
}

void eggStinger::setClock()
{
	if (eggClock.getElapsedTime().asSeconds() > thresHold) {
		goDown = !goDown;
		eggClock.restart();
	}
}

int eggStinger::getHealth()
{
	return health;
}
