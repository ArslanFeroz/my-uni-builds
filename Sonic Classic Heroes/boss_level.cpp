#include "boss_level.h"

boss_level::boss_level()
{
	height = 14;
	width = 50;
	address = "Data/bossLevel.txt";
	totalRings = 50;
	totalLives = 5;
	totalPowerUps = 2;
	totalBrains = 5;
	totalBeeBots = 5;
	totalBugs = 5;
	totalCrabs = 5;

	std::cout << "Constructor of boss level is called." << std::endl;

	maxTime = 100;


	setAttributes(address, height, width, totalRings, totalLives, totalPowerUps, totalBrains, totalBeeBots, totalBugs, totalCrabs, 1);
}
