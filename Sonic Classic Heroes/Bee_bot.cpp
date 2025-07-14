#include "Bee_bot.h"
#include <iostream>
Bee_bot::Bee_bot()
{
	totalFrames = 6;
	height = 40;
	width = 50;
	switch_time = 0.1f;
	currentFrame = 0;
	health = 5;
	address1 = "Data/beebot_leftnew.png";
	address2 = "Data/beebot_rightnew.png";
	rightMotion = false;
	clock.restart();
	movementClock.restart();

	activation = false;

	projectileStatus = true;

	projectile = new Sprite;
	projectileSheet = new Texture;

	proj_addressL = "Data/projectileL.png";
	proj_addressR = "Data/projectileR.png";

	scale_bee.x = 1.8;
	scale_bee.y = 1.8;

	projectile->setScale(scale_bee);

	shootClock.restart();


	Pwidth = 50 * 1.8;
	Pheight = 40 * 1.8;

	hit_box_factor_x = (1.0 - 0.8) * 0.5 * Pwidth;
	hit_box_factor_y = (1.0 - 0.9) * 0.5 * Pheight;

}

Bee_bot::~Bee_bot()
{
	delete projectile;
	delete projectileSheet;
}

void Bee_bot::setAttributes(float& x, float& y)
{
	setData(address1, height, width, x, y, health, 1.8, 1.8);
}

void Bee_bot::enemyAnimations()
{
	if (rightMotion)
		spriteSheet->loadFromFile(address2);
	else
		spriteSheet->loadFromFile(address1);


	if (clock.getElapsedTime().asSeconds() > switch_time) {
		currentFrame++;
		if (currentFrame >= totalFrames)
			currentFrame = 0;

		clock.restart();
	}
	sprite->setTextureRect(IntRect(currentFrame * width, 0, width, height));
}

void Bee_bot::movements(Sprite& target)
{
	if (movementClock.getElapsedTime().asSeconds() > 10.f) {
		rightMotion = !rightMotion;
		movementClock.restart();
	}

	

	if (rightMotion) {
		position.x += 5.f;
	}
	else
		position.x -= 5.f;

	sprite->setPosition(position);
}

//void Bee_bot::shoot(RenderWindow& window, int camerOffset)
//{
//
//
//
//	if (shootClock.getElapsedTime().asSeconds() > 2.f) {
//
//		projectileStatus = true;
//		projectile->setPosition(position.x - camerOffset, position.y);
//		shootClock.restart();
//	}
//
//	Vector2f projPos = projectile->getPosition();
//
//	if (rightMotion) {
//		projectileSheet->loadFromFile(proj_addressR);
//
//		projectile->setTexture(*projectileSheet);
//		projPos.x += 10.f;
//		projPos.y += 5.f;
//	}
//	else {
//		projectileSheet->loadFromFile(proj_addressL);
//
//		projectile->setTexture(*projectileSheet);
//		projPos.x -= 10.f;
//		projPos.y += 5.f;
//	}
//
//
//	if (projectileStatus) {
//		
//		projectile->setPosition(projPos);
//		window.draw(*projectile);
//
//	}
//
//
//
//
//}



	void Bee_bot::shoot(RenderWindow& window, int cameraOffset)
	{
		
		if (shootClock.getElapsedTime().asSeconds() > 2.f)
		{
			projectileStatus = true;
			projWorldPos = position;     
			shootClock.restart();

			
			if (rightMotion)
				projectileSheet->loadFromFile(proj_addressR);
			else
				projectileSheet->loadFromFile(proj_addressL);

			projectile->setTexture(*projectileSheet, true);
			projectile->setScale(1.3f, 1.3f);
		}

		
		if (projectileStatus)
		{
			if (rightMotion)
				projWorldPos.x += 10.f, projWorldPos.y += 5.f;
			else
				projWorldPos.x -= 10.f, projWorldPos.y += 5.f;

			// 3) Convert to SCREEN space for drawing:
			projectile->setPosition(
				projWorldPos.x - static_cast<float>(cameraOffset),
				projWorldPos.y
			);
			window.draw(*projectile);
		}
	}


//void Bee_bot::shoot(RenderWindow& window, int cameraOffset)
//{
//	// 1) On a new shot, reset world?space position:
//	if (shootClock.getElapsedTime().asSeconds() > 2.f) {
//		projectileStatus = true;
//		projectile->setPosition(position);
//		projWorldPos = position;     // “position” is your bee’s world?space pos
//		shootClock.restart();
//	}
//
//	// 2) If there’s an active projectile, advance it in WORLD space:
//	if (projectileStatus) {
//		if (rightMotion)
//			projWorldPos.x += 10.f, projWorldPos.y += 5.f;
//		else
//			projWorldPos.x -= 10.f, projWorldPos.y += 5.f;
//
//		// 3) When drawing, convert to SCREEN space by subtracting the camera offset:
//		projectile->setPosition(projWorldPos.x - cameraOffset,
//			projWorldPos.y);
//		window.draw(*projectile);
//	}
//}


//bool Bee_bot::projectileCollision(Player& player, float cameraOffset)
//{
//	if (!projectileStatus)
//		return false;
//
//	// 1) Projectile AABB in world space
//	float px = projectile->getPosition().x;
//	float py = projectile->getPosition().y;
//	float pw = float(projectile->getTextureRect().width) * projectile->getScale().x;
//	float ph = float(projectile->getTextureRect().height) * projectile->getScale().y;
//
//	// 2) Player AABB in world space
//	sf::Vector2f wp = player.getsprite().getPosition();  // your Player::position
//	float ux = wp.x;
//	float uy = wp.y;
//	float uw = float(player.getsprite().getTextureRect().width) * player.getsprite().getScale().x;
//	float uh = float(player.getsprite().getTextureRect().height) * player.getsprite().getScale().y;
//
//	// 3) Overlap test
//	bool hit =
//		(px + pw > ux) &&
//		(px < ux + uw) &&
//		(py + ph > uy) &&
//		(py < uy + uh);
//
//	if (hit) {
//		projectileStatus = false;
//		return true;
//	}
//	return false;
//}

bool Bee_bot::projectileCollision(Player& player, float cameraOffset)
{
	if (!projectileStatus)
		return false;

	// Getting the coodinates of the prokectile
	float px = projWorldPos.x;
	float py = projWorldPos.y;
	float pw = projectile->getTextureRect().width * projectile->getScale().x;
	float ph = projectile->getTextureRect().height * projectile->getScale().y;

	//sf::Vector2f wp = player.getPosition();

	float ux = player.getPosition_x();
	float uy = player.getPosition_y();
	float uw = player.getsprite().getTextureRect().width * player.getsprite().getScale().x;
	float uh = player.getsprite().getTextureRect().height * player.getsprite().getScale().y;

	bool hit =
		(px + pw > ux) &&
		(px < ux + uw) &&
		(py + ph > uy) &&
		(py < uy + uh);

	if (hit) {

		projectileStatus = false;
		player.reduceHealth();
		return true;
	}
	return false;
}




void Bee_bot::projectileCollision_world(char** lvl, int mapHeight, int mapWidth)
{


	// 1) Use your projWorldPos (world?space) for the projectile, not the sprite’s screen position:
	float player_x = projWorldPos.x;
	float player_y = projWorldPos.y;

	// 2) Your existing dimensions:
	int Pheight = height * scale_bee.y;
	int Pwidth = width * scale_bee.x;
	int cell_size = 64;
	int hit_box_factor_x = int(8 * scale_bee.x);
	int hit_box_factor_y = int(5 * scale_bee.y);

	// 3) Compute tile indices for the four check points:
	int col_left = (int)(player_x + hit_box_factor_x) / cell_size;
	int col_right = (int)(player_x + hit_box_factor_x + Pwidth) / cell_size;
	int row_mid = (int)(player_y + hit_box_factor_y + Pheight / 2) / cell_size;
	int row_bottom = (int)(player_y + hit_box_factor_y + Pheight) / cell_size;

	bool hit = false;

	// 4) Four separate bounds-checked lookups:
	if (row_mid >= 0 && row_mid < mapHeight &&
		col_left >= 0 && col_left < mapWidth)
	{
		if (lvl[row_mid][col_left] != '0')
			hit = true;
	}

	if (row_mid >= 0 && row_mid < mapHeight &&
		col_right >= 0 && col_right < mapWidth)
	{
		if (lvl[row_mid][col_right] != '0')
			hit = true;
	}

	if (row_bottom >= 0 && row_bottom < mapHeight &&
		col_left >= 0 && col_left < mapWidth)
	{
		if (lvl[row_bottom][col_left] != '0')
			hit = true;
	}

	if (row_bottom >= 0 && row_bottom < mapHeight &&
		col_right >= 0 && col_right < mapWidth)
	{
		if (lvl[row_bottom][col_right] != '0')
			hit = true;
	}

	if (hit)
		projectileStatus = false;


	/*float player_x = projectile->getPosition().x;
	float player_y = projectile->getPosition().y;

	float offset_y = player_y;
	float offset_x;
	if (rightMotion)
		offset_x = player_x;
	else
		offset_x = player_x;


	int Pheight = height * scale_bee.y;
	int Pwidth = width * scale_bee.x;

	int cell_size = 64;

	int hit_box_factor_x = int(8 * scale_bee.x);
	int hit_box_factor_y = int(5 * scale_bee.y);


	char left_mid = lvl[(int)(player_y + hit_box_factor_y + Pheight / 2) / cell_size][(int)(player_x + hit_box_factor_x) / cell_size];

	char right_mid = lvl[(int)(player_y + hit_box_factor_y + Pheight / 2) / cell_size][(int)(player_x + hit_box_factor_x + Pwidth) / cell_size];


	char bottom_left_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][(int)(player_x + hit_box_factor_x) / cell_size];
	char bottom_right_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][(int)(player_x + hit_box_factor_x + Pwidth) / cell_size];
	char bottom_mid_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][(int)(player_x + hit_box_factor_x + Pwidth / 2) / cell_size];



	bool hit = false;

	if (left_mid != '0' || right_mid != '0' || bottom_left_down != '0' || bottom_right_down != '0' || bottom_mid_down != '0')
		hit = true;

	if (hit) {
		projectileStatus = false;
	}*/


	// -- 1) World?space projectile coords, not projectile->getPosition():
	//float player_x = projWorldPos.x;
	//float player_y = projWorldPos.y;

	//// -- 2) Your existing geometry
	//int Pheight = height * scale_bee.y;
	//int Pwidth = width * scale_bee.x;
	//int cell_size = 64;
	//int hit_box_factor_x = int(8 * scale_bee.x);
	//int hit_box_factor_y = int(5 * scale_bee.y);

	//// -- 3) Compute the four sample points in tiles
	//int col_left = (int)(player_x + hit_box_factor_x) / cell_size;
	//int col_right = (int)(player_x + hit_box_factor_x + Pwidth) / cell_size;
	//int row_mid = (int)(player_y + hit_box_factor_y + Pheight / 2) / cell_size;
	//int row_bottom = (int)(player_y + hit_box_factor_y + Pheight) / cell_size;

	//// -- 4) Helper to check bounds once
	//auto inBounds = [&](int r, int c) {
	//	return (r >= 0 && r < mapHeight && c >= 0 && c < mapWidth);
	//	};

	//bool hit = false;

	//if (inBounds(row_mid, col_left) && lvl[row_mid][col_left] != '0') hit = true;
	//if (inBounds(row_mid, col_right) && lvl[row_mid][col_right] != '0') hit = true;
	//if (inBounds(row_bottom, col_left) && lvl[row_bottom][col_left] != '0') hit = true;
	//if (inBounds(row_bottom, col_right) && lvl[row_bottom][col_right] != '0') hit = true;

	//if (hit)
	//	projectileStatus = false;
}

void Bee_bot::bee_collision(char** lvl)
{
	//float player_x = position.x;
	//float player_y = position.y;


	//int Pheight = this->height * scale_bee.y;
	//int Pwidth = this->width * scale_bee.x;

	int hit_box_factor_x = int(8 * scale_bee.x);
	int hit_box_factor_y = int(5 * scale_bee.y);

	int cell_size = 64;

	//char left_mid = lvl[(int)(player_y + hit_box_factor_y + Pheight / 2) / cell_size][(int)(player_x + hit_box_factor_x) / cell_size];

	//char right_mid = lvl[(int)(player_y + hit_box_factor_y + Pheight / 2) / cell_size][(int)(player_x + hit_box_factor_x + Pwidth) / cell_size];

	//// Changing the direction upon collision
	//if (left_mid != '0' || right_mid != '0') {

	//	std::cout << "Collision with the world detected " << std::endl;

	//	rightMotion = !rightMotion;
	//}



	float ex = position.x;
	float ey = position.y;

	// use Enemies::height, Enemies::width
	int Pheight = 35 * scale_bee.y;
	int Pwidth = 24 * scale_bee.x;

	int hx = int(ex + hit_box_factor_x);
	int hy = int(ey + hit_box_factor_y + Pheight / 2);

	int colL = hx / cell_size;
	int colR = (hx + Pwidth) / cell_size;
	int row = hy / cell_size;

	char left_mid = lvl[row][colL];
	char right_mid = lvl[row][colR];

	if (left_mid != '0' || right_mid != '0') {
		std::cout << "[Bee] world?collision: flipping direction\n";
		rightMotion = !rightMotion;
	}

}


void Bee_bot::setHealth(int b)
{
	health = b;
}

int Bee_bot::getHealth()
{
	return health;
}

void Bee_bot::setActivation(bool& b)
{
	activation = b;
}

bool Bee_bot::getActivation()
{
	return activation;
}
