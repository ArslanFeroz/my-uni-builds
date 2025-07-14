#include "level3.h"

level3::level3()
{
	height = 14;
	width = 300;
	address = "Data/level3.txt";
	totalRings = 50;
	totalLives = 5;
	totalPowerUps = 2;
	totalBrains = 5;
	totalBeeBots = 5;
	totalBugs = 5;
	totalCrabs = 5;

	std::cout << "Constructor of level 3 is called." << std::endl;

	maxTime = 150;

	setAttributes(address, height, width, totalRings, totalLives, totalPowerUps, totalBrains, totalBeeBots, totalBugs, totalCrabs, 0);

}
