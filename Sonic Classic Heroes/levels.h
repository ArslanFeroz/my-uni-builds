#pragma once


#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include <string>
#include<fstream>
#include "Bat_Brain.h"
#include"Bee_bot.h"
#include"power_ups.h"
#include"extra_life.h"
#include "rings.h"
#include"collectibles.h"
#include "moto_bug.h"
#include"crabMeat.h"
#include "eggStinger.h"
#include <fstream>
#include "Player.h"

using namespace std;
using namespace sf;

class levels {

	char** lvl;
	int height;
	int width;
	int cell_Size;

	int Total_lives;
	int lifeCounter;

	int Total_powers;
	int powerCounter;


	int Total_rings;
	int ringCounter;
	

	int Total_brain;
	int BrainCounter;

	int Total_bee;
	int BeeCounter;

	int Total_bugs;
	int bugCounter;
	
	int Total_crabs;
	int crabCounter;

	int Total_eggStingers;
	int eggCounter;


	int ringCollectedCount;
	float elapsedTime;

	Vector2f scale;

	std::string address;
	std::string ringAddress;
	std::string lifeAddress;
	std::string powerAddress;
	std::string batBrainAddress;


	Texture wall1_tex;
	Texture wall2_tex;
	Texture wall3_tex;
	Texture spike_tex;
	Texture spring_tex;
	Texture crystal_tex;

	Sprite* wall1;
	Sprite* wall2;
	Sprite* wall3;
	Sprite* spikes;
	Sprite* springs;
	Sprite* crystals;

	Music rngMus;

	
	rings** rng;
	extra_life** life;
	power_ups** powers;
	Bat_Brain** brain;
	Bee_bot** bee;
	moto_bug** bug;
	crabMeat** crab;
	eggStinger** egg;

	float spring_cFrame;
	float spring_tFrame;
	float spring_height;
	float spring_width;

	Clock springClock;


	Music* lvl1;
	Music* lvl2;
	Music* lvl3;
	Music* lvl4;

	
	Player* ob;  // required for collisions

	//Positions of the enemies
	/*Vector2f* brainPositions;
	Vector2f* beePositions;
	Vector2f* bugPositions;
	Vector2f* crabPositions;
	Vector2f* eggPositions;*/


	float* brainPositions_x;
	float* brainPositions_y;

	float* beePositions_x;
	float* beePositions_y;

	float* bugPositions_x;
	float* bugPositions_y;

	float* crabPositions_x;
	float* crabPositions_y;

	float* eggPositions_x;
	float* eggPositions_y;

	Texture* bg_tex;
	Sprite* bg_sprite;


	int* score;

	void springAnimation();

protected:

	void setAttributes(std::string& fileAddress, int height, int width, int totalRings, int totalLives, int totalPowerups, int totalBrains, int totalbeeBot, int totalBugs, int totalCrab, int eggStinger);
	float maxTime;  // It will be used to set a time limit for each level
	Clock timeClock;

public:



	levels();
	virtual ~levels();
	void saveLevel(int& levelIndex);
	void loadEnemyStatuses(string sBrain, string sBee, string sBug, string sCrab, string sRing, int ringCount);

	bool levelUp();
	void builLevel();
	void display_level(RenderWindow& window, float cameraOffset, Sprite& obj, int& levelIndex);
	void setPlayer(Player* o);

	char** getLevel();
	void reset();
	void checkCollision(Sprite& obj, Player& obj2, int &specialAbilityCounter, float cameraOffset, bool& bottomCollision, bool& jumping, bool& onground);

	float& getElapsedTime();
	void setClock();
	int& ringCollectCount();
	void setScore(int* a);

	void removeWall();

	void playMusic(int& levelIndex);
	void stopMusic(int& levelIndex);
	

	/*int & getHeight();
	int& getWidth();*/
};

