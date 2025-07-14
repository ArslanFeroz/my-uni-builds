#pragma once
#include "Enemies.h"
#include"Player.h"
class Bee_bot:public Enemies
{
	//Animation related information
	int totalFrames;
	/*int Height;
	int width;*/

	std::string address1;
	std::string address2;

	Sprite* projectile;
	Texture* projectileSheet;
	std::string proj_addressL;
	std::string proj_addressR;
	bool projectileStatus;
	

	Vector2f scale_bee;

	float switch_time;
	int currentFrame;


	int health;

	Clock movementClock;
	Clock shootClock;

	Vector2f projWorldPos;

	bool activation;


public:

	Bee_bot();
	~Bee_bot();
	bool rightMotion;


	void setAttributes(float& x, float& y);
	void enemyAnimations();
	void movements(Sprite& target);

	void shoot(RenderWindow& window, int cameraOffset);
	bool projectileCollision(Player& obj, float cameraOffset);
	void projectileCollision_world(char** lvl, int mapHeight, int mapWidth);
	void bee_collision(char** lvl);

	void setHealth(int b);
	int getHealth();

	void setActivation(bool& b);
	bool getActivation();
};

