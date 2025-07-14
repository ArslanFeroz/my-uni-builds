#pragma once
#include "levels.h"
class boss_level: public levels
{
	int height;
	int width;
	int totalRings;
	int totalLives;
	int totalPowerUps;
	int totalBrains;
	int totalBeeBots;
	int totalBugs;
	int totalCrabs;

	std::string address;



public:

	boss_level();
};

