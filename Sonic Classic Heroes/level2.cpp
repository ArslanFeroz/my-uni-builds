#include "level2.h"

level2::level2()
{
	height = 14;
	width = 250;
	address = "Data/level2.txt";
	totalRings = 50;
	totalLives = 5;
	totalPowerUps = 2;
	totalBrains = 5;
	totalBeeBots = 5;
	totalBugs = 5;
	totalCrabs = 5;

	std::cout << "Constructor of level 2 is called." << std::endl;

	maxTime = 100;


	setAttributes(address, height, width, totalRings, totalLives, totalPowerUps, totalBrains, totalBeeBots, totalBugs, totalCrabs, 0);
}
