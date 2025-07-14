#pragma once

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <fstream>

//#include "levels.h"
using namespace std;

using namespace sf;

class Player
{
	
	//Vector2f velocity;

	float velocity_x;
	float velocity_y;


	float currentVelocity;
	

	Texture rightMotion;
	Texture leftMotion;

	Texture leftJump;
	Texture rightJump;

	int vx = 0;


	// boolean to determine the main character, which obviosly at start will be sonic
	bool main;
	int hp;

	const float invincibleTime = 1.5f;


	Texture rightStill;
	Texture leftStill;  // makign them privaat4e because need access to them outside of the class

	float scale_x, scale_y;
	int raw_img_x, raw_img_y;
	int Pheight, Pwidth;
	int hit_box_factor_x, hit_box_factor_y;
	const int cell_size = 64;




	

protected:
	Sprite sprite;
	/*Vector2f scale;
	Vector2f position;*/

	float position_x;
	float position_y;

	/*float scale_x;
	float scale_y;*/

	// Required for knuckles special ability
	int index1;
	int index2;

	float acceleration;

	Clock flyClock;
	const float maxFlyTime = 7;



public:
	bool noDamage;

	bool isFlying = false;
	Clock healthClock;

	int SpecialAbilityCounter;

	//constructors
	Player();
	Player(Vector2f& pos);

	//States
	void setTexture(std::string& address, std::string& address2, std::string& address3, std::string& address4, std:: string & address5, std:: string& address6);
	void jump(bool& jumping, bool& onground, float gravity, char** lvl, int Pwidth, int hit_box_factor_x, int hit_box_factor_y, int cell_size, bool onSpring = false);
	void movement(Event& ev, float& player_x, bool& leftMovement, float& dt);
	bool noCollision(char** lvl, float player_x, float player_y, int Pwidth, int Pheight, int hit_box_factor_x, int hit_box_factor_y, const int cell_size);
	void Still_State(Event& ev);
	void jogState(std::string& state, Clock& clock);
	void jumpState(std::string& state, Clock& clock);
	void player_gravity(char** lvl, float& offset_y, float& velocityY, bool& onGround, float& gravity, float& terminal_Velocity, int& hit_box_factor_x, int& hit_box_factor_y, float& player_x, float& player_y, const int cell_size, int& Pheight, int& Pwidth, bool& onSpring);
	void draw_player(RenderWindow& window, Sprite& LstillSprite, float player_x, float player_y, float cameraOffset, bool on = false);
	Sprite& getsprite();
	/*Vector2f& getPosition();
	Vector2f getVelocity();*/


	bool& getFlightStatus();

	float& getPosition_x();
	float& getPosition_y();

	float& getVelocity_x();
	float& getVelocity_y();

	void setPosition(float& x, float& y);


	void increaseHealth();
	

	bool getStatus();
	void setSpeed(float& x, float& y);
	//void setPosition(float& x, float & y);

	void deaccelaration(float& dt, float friction, bool& leftMovement, float& player_x);

	float getCurrent_x();
	void setCurrentVelocity();

	void setDamageStatus();
	void setHealthClock();
	virtual void setStatus(bool& s);
	int& getAbilityCounter();

	void setNoDamage();
	bool getDamageStatus();

	bool PositionCheck(float& mainPosition_x, float& mainPosition_y);
	bool moveTowardMain(float& mainPosition_x, float& mainPosition_y, bool& leftMotion);
	//void follow(const Vector2f& targetPos, float speed, float dt);
	void shiftCharacter(Event& ev, int& main_character_index, int& other1, int& other2);
	bool CollisionWithGround(char** lvl);

	//bool canTakeDamage();
	bool breakAblewall(char** lvl, float player_x, float player_y, int Pwidth, int Pheight, int hit_box_factor_x, int hit_box_factor_y, const int cell_size, int& index1, int& index2, bool rightMOtion);


	void reduceHealth();
	int gethealth();
	void setHealth(int x);
	void setIndexes(int x, int y);
	void updateFlight(bool& onGround, char** lvl);

	void saveGame(float& x, float& y, int health);
	void truncateFile();
	void loadFromSave(float x, float y, int hp);

	virtual void SpecialAbilities(Event& ev, char** l = nullptr, bool motionLeft = false) = 0;

	// Render
};

