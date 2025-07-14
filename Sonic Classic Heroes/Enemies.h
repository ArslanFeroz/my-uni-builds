#pragma once

#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"

#include "Player.h"

using namespace sf;

class Enemies
{

	bool presentStatus;
	std::string address;
	float scale_x = 1.8;
	float scale_y = 1.8;

	int hp;


protected:

	int hit;
	Sprite* sprite;
	Texture* spriteSheet;
	int width;
	int height;
	Vector2f position;
	//Animation clock
	Clock clock;
	void setData(std::string& ad, int h, int w, float& x, float& y, int hp, float scale_x, float scale_y);

	float Pwidth;
	float Pheight;
	int hit_box_factor_x;
	int hit_box_factor_y;
	const int cell_size = 64;


public:

	Enemies();
	~Enemies();

	virtual void enemyAnimations() = 0;
	

	//Setter and getters
	void setStatus(bool& b);
	void setPosition(Vector2f& pos);
	void setPosition(float& x, float& y);

	Vector2f getPosition();
	bool getStatus();
	void setScale(float& x, float& y);


	//bool collision(Sprite& obj, bool& bottomCollision);

	//bool collision(const Vector2f& playerWorldPos, const Vector2f& playerSize, float playerVelY, bool& bottomCollision);

	//bool playerCollision(Sprite& ob);

	bool handlePlayerCollision(Player* player, bool& jumping, bool & inFlight, int* score, const string str);

	bool noCollision(char** lvl, float player_x, float player_y);
	

	void setHp(int h);
	int getHp();

	void render(RenderWindow& window, float offsetX);
};

